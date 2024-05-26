/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/ad_units/promoted_content_ad/promoted_content_ad_handler.h"

#include <utility>

#include "base/check.h"
#include "brave/components/brave_ads/core/internal/account/account.h"
#include "brave/components/brave_ads/core/internal/ad_units/promoted_content_ad/promoted_content_ad_info.h"
#include "brave/components/brave_ads/core/internal/common/logging_util.h"
#include "brave/components/brave_ads/core/internal/history/history_manager.h"
#include "brave/components/brave_ads/core/internal/settings/settings.h"
#include "brave/components/brave_ads/core/internal/user_engagement/site_visit/site_visit.h"
#include "brave/components/brave_ads/core/public/account/confirmations/confirmation_type.h"

namespace brave_ads {

namespace {

void FireEventCallback(TriggerAdEventCallback callback,
                       const bool success,
                       const std::string& /*placement_id*/,
                       const mojom::PromotedContentAdEventType /*event_type*/) {
  std::move(callback).Run(success);
}

}  // namespace

PromotedContentAdHandler::PromotedContentAdHandler(Account& account,
                                                   SiteVisit& site_visit)
    : account_(account), site_visit_(site_visit) {
  event_handler_.SetDelegate(this);
}

PromotedContentAdHandler::~PromotedContentAdHandler() = default;

void PromotedContentAdHandler::TriggerEvent(
    const std::string& placement_id,
    const std::string& creative_instance_id,
    const mojom::PromotedContentAdEventType event_type,
    TriggerAdEventCallback callback) {
  CHECK_NE(mojom::PromotedContentAdEventType::kServedImpression, event_type)
      << "Should not be called with kServedImpression as this event is handled "
         "when calling TriggerEvent with kViewedImpression";

  if (creative_instance_id.empty()) {
    // No-op if `creative_instance_id` is empty. This should only occur for
    // super referrals.
    return std::move(callback).Run(/*success=*/false);
  }

  if (!UserHasOptedInToBraveNewsAds()) {
    return std::move(callback).Run(/*success=*/false);
  }

  if (event_type == mojom::PromotedContentAdEventType::kViewedImpression) {
    return event_handler_.FireEvent(
        placement_id, creative_instance_id,
        mojom::PromotedContentAdEventType::kServedImpression,
        base::BindOnce(&PromotedContentAdHandler::TriggerServedEventCallback,
                       weak_factory_.GetWeakPtr(), creative_instance_id,
                       std::move(callback)));
  }

  event_handler_.FireEvent(
      placement_id, creative_instance_id, event_type,
      base::BindOnce(&FireEventCallback, std::move(callback)));
}

///////////////////////////////////////////////////////////////////////////////

void PromotedContentAdHandler::TriggerServedEventCallback(
    const std::string& creative_instance_id,
    TriggerAdEventCallback callback,
    const bool success,
    const std::string& placement_id,
    const mojom::PromotedContentAdEventType /*event_type*/) {
  if (!success) {
    return std::move(callback).Run(/*success=*/false);
  }

  event_handler_.FireEvent(
      placement_id, creative_instance_id,
      mojom::PromotedContentAdEventType::kViewedImpression,
      base::BindOnce(&FireEventCallback, std::move(callback)));
}

void PromotedContentAdHandler::OnDidFirePromotedContentAdServedEvent(
    const PromotedContentAdInfo& ad) {
  BLOG(3, "Served promoted content ad impression with placement id "
              << ad.placement_id << " and creative instance id "
              << ad.creative_instance_id);
}

void PromotedContentAdHandler::OnDidFirePromotedContentAdViewedEvent(
    const PromotedContentAdInfo& ad) {
  BLOG(3, "Viewed promoted content ad impression with placement id "
              << ad.placement_id << " and creative instance id "
              << ad.creative_instance_id);

  HistoryManager::GetInstance().Add(ad, ConfirmationType::kViewedImpression);

  account_->Deposit(ad.creative_instance_id, ad.segment, ad.type,
                    ConfirmationType::kViewedImpression);
}

void PromotedContentAdHandler::OnDidFirePromotedContentAdClickedEvent(
    const PromotedContentAdInfo& ad) {
  BLOG(3, "Clicked promoted content ad with placement id "
              << ad.placement_id << " and creative instance id "
              << ad.creative_instance_id);

  site_visit_->SetLastClickedAd(ad);

  HistoryManager::GetInstance().Add(ad, ConfirmationType::kClicked);

  account_->Deposit(ad.creative_instance_id, ad.segment, ad.type,
                    ConfirmationType::kClicked);
}

}  // namespace brave_ads

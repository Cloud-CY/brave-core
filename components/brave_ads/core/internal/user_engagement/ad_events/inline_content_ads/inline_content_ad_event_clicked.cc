/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/user_engagement/ad_events/inline_content_ads/inline_content_ad_event_clicked.h"

#include <utility>

#include "brave/components/brave_ads/core/internal/user_engagement/ad_events/ad_events.h"
#include "brave/components/brave_ads/core/public/account/confirmations/confirmation_type.h"
#include "brave/components/brave_ads/core/public/ad_units/inline_content_ad/inline_content_ad_info.h"

namespace brave_ads {

void InlineContentAdEventClicked::FireEvent(const InlineContentAdInfo& ad,
                                            ResultCallback callback) {
  RecordAdEvent(ad, ConfirmationType::kClicked, std::move(callback));
}

}  // namespace brave_ads

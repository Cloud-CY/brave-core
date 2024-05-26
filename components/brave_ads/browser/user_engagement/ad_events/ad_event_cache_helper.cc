/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/browser/user_engagement/ad_events/ad_event_cache_helper.h"

#include "base/no_destructor.h"
#include "base/time/time.h"

namespace brave_ads {

AdEventCacheHelper::AdEventCacheHelper() = default;

AdEventCacheHelper::~AdEventCacheHelper() = default;

AdEventCacheHelper* AdEventCacheHelper::GetInstance() {
  static base::NoDestructor<AdEventCacheHelper> instance;
  return instance.get();
}

void AdEventCacheHelper::CacheAdEventForInstanceId(
    const std::string& id,
    const std::string& ad_type,
    const std::string& confirmation_type,
    const base::Time time) {
  ad_event_cache_.AddEntryForInstanceId(id, ad_type, confirmation_type, time);
}

std::vector<base::Time> AdEventCacheHelper::GetCachedAdEvents(
    const std::string& ad_type,
    const std::string& confirmation_type) const {
  return ad_event_cache_.Get(ad_type, confirmation_type);
}

void AdEventCacheHelper::ResetAdEventCacheForInstanceId(const std::string& id) {
  ad_event_cache_.ResetForInstanceId(id);
}

}  // namespace brave_ads

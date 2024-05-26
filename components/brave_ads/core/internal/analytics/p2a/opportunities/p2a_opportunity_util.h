/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ANALYTICS_P2A_OPPORTUNITIES_P2A_OPPORTUNITY_UTIL_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ANALYTICS_P2A_OPPORTUNITIES_P2A_OPPORTUNITY_UTIL_H_

#include <string>
#include <vector>

#include "brave/components/brave_ads/core/internal/segments/segment_alias.h"
#include "brave/components/brave_ads/core/public/ad_units/ad_type.h"

namespace brave_ads {

std::vector<std::string> BuildP2AAdOpportunityEvents(
    AdType ad_type,
    const SegmentList& segments);

}  // namespace brave_ads

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ANALYTICS_P2A_OPPORTUNITIES_P2A_OPPORTUNITY_UTIL_H_

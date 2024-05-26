/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/common/unittest/unittest_time_util.h"

#include "base/i18n/time_formatting.h"
#include "base/time/time.h"

namespace brave_ads {

base::Time DistantPast() {
  // Just after the myth of the beginning of time.
  return base::Time() + base::Milliseconds(1);
}

std::string DistantPastAsIso8601() {
  return base::TimeFormatAsIso8601(DistantPast());
}

base::Time Now() {
  // The time for action is now. It's never too late to do something.
  return base::Time::Now();
}

std::string NowAsIso8601() {
  return base::TimeFormatAsIso8601(Now());
}

base::Time DistantFuture() {
  // Chrome timestamps are 64-bit and will not overflow at 03:14:08 UTC on 19
  // January 2038. However, I only like to think about so far into the future
  // because it comes soon enough.
  return base::Time::FromSecondsSinceUnixEpoch(
      /*Tuesday, 19 January 2038 03:14:07=*/2147483647);
}

std::string DistantFutureAsIso8601() {
  return base::TimeFormatAsIso8601(DistantFuture());
}

}  // namespace brave_ads

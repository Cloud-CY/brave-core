/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_CORE_PUBLIC_AD_UNITS_INLINE_CONTENT_AD_INLINE_CONTENT_AD_VALUE_UTIL_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_CORE_PUBLIC_AD_UNITS_INLINE_CONTENT_AD_INLINE_CONTENT_AD_VALUE_UTIL_H_

#include "base/values.h"

namespace brave_ads {

struct InlineContentAdInfo;

base::Value::Dict InlineContentAdToValue(const InlineContentAdInfo& ad);
InlineContentAdInfo InlineContentAdFromValue(const base::Value::Dict& dict);

}  // namespace brave_ads

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_CORE_PUBLIC_AD_UNITS_INLINE_CONTENT_AD_INLINE_CONTENT_AD_VALUE_UTIL_H_

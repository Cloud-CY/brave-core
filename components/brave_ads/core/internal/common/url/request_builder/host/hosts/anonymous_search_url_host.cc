/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/common/url/request_builder/host/hosts/anonymous_search_url_host.h"

#include "brave/components/brave_ads/core/internal/global_state/global_state.h"
#include "brave/components/brave_ads/core/mojom/brave_ads.mojom.h"

namespace brave_ads {

namespace {

constexpr char kProductionHost[] = "https://search.anonymous.ads.brave.com";
constexpr char kStagingHost[] =
    "https://search.anonymous.ads.bravesoftware.com";

}  // namespace

std::string AnonymousSearchUrlHost::Get() const {
  const mojom::EnvironmentType environment_type =
      GlobalState::GetInstance()->Flags().environment_type;
  switch (environment_type) {
    case mojom::EnvironmentType::kProduction: {
      return kProductionHost;
    }

    case mojom::EnvironmentType::kStaging: {
      return kStagingHost;
    }
  }
}

}  // namespace brave_ads

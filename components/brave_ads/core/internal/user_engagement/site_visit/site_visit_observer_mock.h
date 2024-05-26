/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_SITE_VISIT_OBSERVER_MOCK_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_SITE_VISIT_OBSERVER_MOCK_H_

#include "brave/components/brave_ads/core/internal/user_engagement/site_visit/site_visit_observer.h"

#include <cstdint>

#include "brave/components/brave_ads/core/internal/tabs/tab_info.h"
#include "testing/gmock/include/gmock/gmock.h"  // IWYU pragma: keep

namespace brave_ads {

class SiteVisitObserverMock : public SiteVisitObserver {
 public:
  SiteVisitObserverMock();

  SiteVisitObserverMock(const SiteVisitObserverMock&) = delete;
  SiteVisitObserverMock& operator=(const SiteVisitObserverMock&) = delete;

  SiteVisitObserverMock(SiteVisitObserverMock&&) noexcept = delete;
  SiteVisitObserverMock& operator=(SiteVisitObserverMock&&) noexcept = delete;

  ~SiteVisitObserverMock() override;

  MOCK_METHOD(void,
              OnMaybeLandOnPage,
              (const AdInfo& ad, const base::TimeDelta after));

  MOCK_METHOD(void,
              OnDidSuspendPageLand,
              (const TabInfo& tab, const base::TimeDelta remaining_time));

  MOCK_METHOD(void,
              OnDidResumePageLand,
              (const TabInfo& tab, const base::TimeDelta remaining_time));

  MOCK_METHOD(void, OnDidLandOnPage, (const TabInfo& tab, const AdInfo& ad));

  MOCK_METHOD(void, OnDidNotLandOnPage, (const TabInfo& tab, const AdInfo& ad));

  MOCK_METHOD(void,
              OnCanceledPageLand,
              (const int32_t tab_id, const AdInfo& ad));
};

}  // namespace brave_ads

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_USER_ENGAGEMENT_SITE_VISIT_SITE_VISIT_OBSERVER_MOCK_H_

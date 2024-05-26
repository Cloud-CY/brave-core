/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/catalog/catalog_url_request_builder.h"

#include "brave/components/brave_ads/core/internal/common/unittest/unittest_base.h"
#include "url/gurl.h"

// npm run test -- brave_unit_tests --filter=BraveAds*

namespace brave_ads {

class BraveAdsCatalogUrlRequestBuilderTest : public UnitTestBase {};

TEST_F(BraveAdsCatalogUrlRequestBuilderTest, BuildUrl) {
  // Arrange
  CatalogUrlRequestBuilder url_request_builder;

  // Act
  const mojom::UrlRequestInfoPtr url_request = url_request_builder.Build();

  // Assert
  mojom::UrlRequestInfoPtr expected_url_request = mojom::UrlRequestInfo::New();
  expected_url_request->url =
      GURL("https://static.ads.bravesoftware.com/v9/catalog");
  expected_url_request->method = mojom::UrlRequestMethodType::kGet;
  EXPECT_EQ(expected_url_request, url_request);
}

}  // namespace brave_ads

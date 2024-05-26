/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/account/user_data/fixed/summary_user_data_util.h"

#include "brave/components/brave_ads/core/internal/account/tokens/payment_tokens/payment_tokens_unittest_util.h"
#include "brave/components/brave_ads/core/public/account/confirmations/confirmation_type.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- brave_unit_tests --filter=BraveAds*

namespace brave_ads {

TEST(BraveAdsSummaryUserDataUtilTest, BuildBucketsIfNoPaymentTokens) {
  // Act
  const AdTypeBucketMap buckets = BuildAdTypeBuckets(/*payment_tokens=*/{});

  // Assert
  EXPECT_TRUE(buckets.empty());
}

TEST(BraveAdsSummaryUserDataUtilTest, BuildBuckets) {
  // Arrange
  PaymentTokenList payment_tokens;

  const PaymentTokenInfo payment_token_1 = test::BuildPaymentToken(
      ConfirmationType::kViewedImpression, AdType::kNotificationAd);
  payment_tokens.push_back(payment_token_1);

  const PaymentTokenInfo payment_token_2 = test::BuildPaymentToken(
      ConfirmationType::kViewedImpression, AdType::kNotificationAd);
  payment_tokens.push_back(payment_token_2);

  const PaymentTokenInfo payment_token_3 = test::BuildPaymentToken(
      ConfirmationType::kClicked, AdType::kNotificationAd);
  payment_tokens.push_back(payment_token_3);

  const PaymentTokenInfo payment_token_4 = test::BuildPaymentToken(
      ConfirmationType::kViewedImpression, AdType::kInlineContentAd);
  payment_tokens.push_back(payment_token_4);

  // Act & Assert
  const AdTypeBucketMap expected_buckets = {
      {AdType::kNotificationAd,
       {{ConfirmationType::kClicked, 1},
        {ConfirmationType::kViewedImpression, 2}}},
      {AdType::kInlineContentAd, {{ConfirmationType::kViewedImpression, 1}}}};
  EXPECT_EQ(expected_buckets, BuildAdTypeBuckets(payment_tokens));
}

}  // namespace brave_ads

/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ACCOUNT_USER_REWARDS_USER_REWARDS_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ACCOUNT_USER_REWARDS_USER_REWARDS_H_

#include <string>

#include "base/memory/raw_ptr.h"
#include "brave/components/brave_ads/core/internal/account/issuers/issuers_url_request.h"
#include "brave/components/brave_ads/core/internal/account/issuers/issuers_url_request_delegate.h"
#include "brave/components/brave_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "brave/components/brave_ads/core/internal/account/transactions/transactions_database_table.h"
#include "brave/components/brave_ads/core/internal/account/user_rewards/user_rewards_delegate.h"
#include "brave/components/brave_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens.h"
#include "brave/components/brave_ads/core/internal/account/utility/redeem_payment_tokens/redeem_payment_tokens_delegate.h"
#include "brave/components/brave_ads/core/internal/account/utility/refill_confirmation_tokens/refill_confirmation_tokens.h"
#include "brave/components/brave_ads/core/internal/account/utility/refill_confirmation_tokens/refill_confirmation_tokens_delegate.h"
#include "brave/components/brave_ads/core/internal/account/wallet/wallet_info.h"
#include "brave/components/brave_ads/core/public/client/ads_client_notifier_observer.h"

namespace brave_ads {

class TokenGeneratorInterface;
struct IssuersInfo;

class UserRewards final : public AdsClientNotifierObserver,
                          public IssuersUrlRequestDelegate,
                          public RedeemPaymentTokensDelegate,
                          public RefillConfirmationTokensDelegate {
 public:
  explicit UserRewards(TokenGeneratorInterface* token_generator,
                       WalletInfo wallet);

  UserRewards(const UserRewards&) = delete;
  UserRewards& operator=(const UserRewards&) = delete;

  UserRewards(UserRewards&&) noexcept = delete;
  UserRewards& operator=(UserRewards&&) noexcept = delete;

  ~UserRewards() override;

  void SetDelegate(UserRewardsDelegate* delegate) {
    CHECK_EQ(delegate_, nullptr);
    delegate_ = delegate;
  }

  void FetchIssuers();

  void MaybeRefillConfirmationTokens();

  void MaybeRedeemPaymentTokens();

 private:
  void MaybeMigrateVerifiedRewardsUser();

  void NotifyDidMigrateVerifiedRewardsUser() const;

  // AdsClientNotifierObserver:
  void OnNotifyDidSolveAdaptiveCaptcha() override;
  void OnNotifyPrefDidChange(const std::string& path) override;

  // IssuersUrlRequestDelegate:
  void OnDidFetchIssuers(const IssuersInfo& issuers) override;

  // RedeemPaymentTokensDelegate:
  void OnDidRedeemPaymentTokens(
      const PaymentTokenList& payment_tokens) override;

  // RefillConfirmationTokensDelegate:
  void OnWillRefillConfirmationTokens() override;
  void OnDidRefillConfirmationTokens() override;
  void OnFailedToRefillConfirmationTokens() override;
  void OnWillRetryRefillingConfirmationTokens(base::Time retry_at) override;
  void OnDidRetryRefillingConfirmationTokens() override;
  void OnCaptchaRequiredToRefillConfirmationTokens(
      const std::string& captcha_id) override;

  IssuersUrlRequest issuers_url_request_;
  RefillConfirmationTokens refill_confirmation_tokens_;
  RedeemPaymentTokens redeem_payment_tokens_;

  WalletInfo wallet_;

  const database::table::Transactions transactions_database_table_;

  raw_ptr<UserRewardsDelegate> delegate_ = nullptr;
};

}  // namespace brave_ads

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ACCOUNT_USER_REWARDS_USER_REWARDS_H_

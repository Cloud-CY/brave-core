/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_NON_CASH_DEPOSIT_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_NON_CASH_DEPOSIT_H_

#include <string>

#include "brave/components/brave_ads/core/internal/account/deposits/deposit_interface.h"

namespace brave_ads {

class NonCashDeposit final : public DepositInterface {
 public:
  void GetValue(const std::string& creative_instance_id,
                GetDepositCallback callback) override;
};

}  // namespace brave_ads

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_NON_CASH_DEPOSIT_H_

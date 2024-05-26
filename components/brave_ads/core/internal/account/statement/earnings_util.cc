/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/account/statement/earnings_util.h"

#include "base/time/time.h"
#include "brave/components/brave_ads/core/internal/account/transactions/reconciled_transactions_util.h"
#include "brave/components/brave_ads/core/internal/common/time/time_util.h"

namespace brave_ads {

namespace {

double GetUnreconciledEarningsForDateRange(const TransactionList& transactions,
                                           const base::Time from_time,
                                           const base::Time to_time) {
  double earnings = 0.0;

  for (const auto& transaction : transactions) {
    if (!DidReconcileTransactionWithinDateRange(transaction, from_time,
                                                to_time)) {
      earnings += transaction.value;
    }
  }

  return earnings;
}

double GetReconciledEarningsForDateRange(const TransactionList& transactions,
                                         const base::Time from_time,
                                         const base::Time to_time) {
  double earnings = 0.0;

  for (const auto& transaction : transactions) {
    if (DidReconcileTransactionWithinDateRange(transaction, from_time,
                                               to_time)) {
      earnings += transaction.value;
    }
  }

  return earnings;
}

}  // namespace

double GetUnreconciledEarnings(const TransactionList& transactions) {
  const base::Time from_time = GetTimeInDistantPast();
  const base::Time to_time = GetLocalTimeAtEndOfThisMonth();

  return GetUnreconciledEarningsForDateRange(transactions, from_time, to_time);
}

double GetReconciledEarningsForThisMonth(const TransactionList& transactions) {
  const base::Time from_time = GetLocalTimeAtBeginningOfThisMonth();
  const base::Time to_time = GetLocalTimeAtEndOfThisMonth();

  return GetReconciledEarningsForDateRange(transactions, from_time, to_time);
}

double GetReconciledEarningsForLastMonth(const TransactionList& transactions) {
  const base::Time from_time = GetLocalTimeAtBeginningOfLastMonth();
  const base::Time to_time = GetLocalTimeAtEndOfLastMonth();

  return GetReconciledEarningsForDateRange(transactions, from_time, to_time);
}

}  // namespace brave_ads

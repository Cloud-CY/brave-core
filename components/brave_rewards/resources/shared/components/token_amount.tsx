/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'

interface Props {
  amount: number
  minimumIntegerDigits?: number
  minimumFractionDigits?: number
  hideCurrency?: boolean
}

const defaultMinimumFractionDigits = 3

function getFormatter (props: Props) {
  return new Intl.NumberFormat(undefined, {
    minimumIntegerDigits: typeof props.minimumIntegerDigits === 'number'
      ? props.minimumIntegerDigits
      : undefined,
    maximumFractionDigits: 3,
    minimumFractionDigits: typeof props.minimumFractionDigits === 'number'
      ? props.minimumFractionDigits
      : defaultMinimumFractionDigits
  })
}

export function TokenAmount (props: Props) {
  const formatter = getFormatter(props)
  return (
    <>
      <span className='amount'>{formatter.format(props.amount || 0)}</span>
      {!props.hideCurrency && <>{' '}<span className='currency'>BAT</span></>}
    </>
  )
}

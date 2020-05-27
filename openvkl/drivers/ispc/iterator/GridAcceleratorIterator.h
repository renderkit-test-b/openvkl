// Copyright 2019-2020 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Iterator.h"
#include "GridAcceleratorIterator_ispc.h"

namespace openvkl {
  namespace ispc_driver {

    template <int W>
    struct GridAcceleratorIntervalIterator : public IntervalIterator<W>
    {
      using IntervalIterator<W>::IntervalIterator;

      // Varying.

      void initializeIntervalV(
          const vintn<W> &valid,
          const vvec3fn<W> &origin,
          const vvec3fn<W> &direction,
          const vrange1fn<W> &tRange,
          const ValueSelector<W> *valueSelector) override final;

      void iterateIntervalV(const vintn<W> &valid,
                            Interval<W> &interval,
                            vintn<W> &result) override final;

      // Uniform.

      void initializeIntervalU(
          const vvec3fn<1> &origin,
          const vvec3fn<1> &direction,
          const vrange1fn<1> &tRange,
          const ValueSelector<W> *valueSelector) override final;

      void iterateIntervalU(Interval<1> &interval,
                            vintn<1> &result) override final;

     protected:
      using Iterator<W>::volume;
      using IspcIterator = __varying_ispc_type(GridAcceleratorIterator);
      alignas(alignof(IspcIterator)) char ispcStorage[sizeof(IspcIterator)];
    };

    template <int W>
    using GridAcceleratorIntervalIteratorFactory =
        ConcreteIteratorFactory<W, IntervalIterator, GridAcceleratorIntervalIterator>;

    template <int W>
    struct GridAcceleratorHitIterator : public HitIterator<W>
    {
      using HitIterator<W>::HitIterator;

      // Varying.

      void initializeHitV(const vintn<W> &valid,
                          const vvec3fn<W> &origin,
                          const vvec3fn<W> &direction,
                          const vrange1fn<W> &tRange,
                          const ValueSelector<W> *valueSelector) override final;
      void iterateHitV(const vintn<W> &valid,
                       Hit<W> &hit,
                       vintn<W> &result) override final;

      // Uniform.

      void initializeHitU(const vvec3fn<1> &origin,
                          const vvec3fn<1> &direction,
                          const vrange1fn<1> &tRange,
                          const ValueSelector<W> *valueSelector) override final;

      void iterateHitU(Hit<1> &hit, vintn<1> &result) override final;

     protected:
      using Iterator<W>::volume;
      using IspcIterator = __varying_ispc_type(GridAcceleratorIterator);
      alignas(alignof(IspcIterator)) char ispcStorage[sizeof(IspcIterator)];
    };

    template <int W>
    using GridAcceleratorHitIteratorFactory =
        ConcreteIteratorFactory<W, HitIterator, GridAcceleratorHitIterator>;

  }  // namespace ispc_driver
}  // namespace openvkl

// Copyright 2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "../../../api/Device.h"

namespace openvkl {
  namespace cpu_device {

    struct AddDeviceAPIs : public api::Device
    {
      /////////////////////////////////////////////////////////////////////////
      // Sampler //////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////////

#define __define_computeSampleN(WIDTH)                                       \
  virtual void computeSample##WIDTH(const int *valid,                        \
                                    const VKLSampler *sampler,               \
                                    const vvec3fn<WIDTH> &objectCoordinates, \
                                    float *samples,                          \
                                    unsigned int attributeIndex,             \
                                    const float *times) = 0;

      __define_computeSampleN(1);
      __define_computeSampleN(4);
      __define_computeSampleN(8);
      __define_computeSampleN(16);

#undef __define_computeSampleN

      virtual void computeSampleN(const VKLSampler *sampler,
                                  unsigned int N,
                                  const vvec3fn<1> *objectCoordinates,
                                  float *samples,
                                  unsigned int attributeIndex,
                                  const float *times) = 0;

#define __define_computeSampleMN(WIDTH)                                       \
  virtual void computeSampleM##WIDTH(const int *valid,                        \
                                     const VKLSampler *sampler,               \
                                     const vvec3fn<WIDTH> &objectCoordinates, \
                                     float *samples,                          \
                                     unsigned int M,                          \
                                     const unsigned int *attributeIndices,    \
                                     const float *times) = 0;

      __define_computeSampleMN(1);
      __define_computeSampleMN(4);
      __define_computeSampleMN(8);
      __define_computeSampleMN(16);

#undef __define_computeSampleMN

      virtual void computeSampleMN(const VKLSampler *sampler,
                                   unsigned int N,
                                   const vvec3fn<1> *objectCoordinates,
                                   float *samples,
                                   unsigned int M,
                                   const unsigned int *attributeIndices,
                                   const float *times) = 0;

#define __define_computeGradientN(WIDTH)                                       \
  virtual void computeGradient##WIDTH(const int *valid,                        \
                                      const VKLSampler *sampler,               \
                                      const vvec3fn<WIDTH> &objectCoordinates, \
                                      vvec3fn<WIDTH> &gradients,               \
                                      unsigned int attributeIndex,             \
                                      const float *times) = 0;

      __define_computeGradientN(1);
      __define_computeGradientN(4);
      __define_computeGradientN(8);
      __define_computeGradientN(16);

#undef __define_computeGradientN

      virtual void computeGradientN(const VKLSampler *sampler,
                                    unsigned int N,
                                    const vvec3fn<1> *objectCoordinates,
                                    vvec3fn<1> *gradients,
                                    unsigned int attributeIndex,
                                    const float *times) = 0;
    };

  }  // namespace cpu_device
}  // namespace openvkl
// ======================================================================== //
// Copyright 2018 Intel Corporation                                         //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include "../volume/Volume.h"
#include "common/ManagedObject.h"
#include "common/objectFactory.h"
#include "volley/volley.h"

namespace volley {

  namespace scalar_driver {

    struct Integrator : public ManagedObject
    {
      Integrator()                   = default;
      virtual ~Integrator() override = default;

      static Integrator *createInstance(const std::string &type)
      {
        return createInstanceHelper<Integrator, VLY_INTEGRATOR>(type);
      }

      virtual void commit() override
      {
        ManagedObject::commit();

        computeGradients = bool(getParam<int>("computeGradients", 0));
      }

      virtual void integrate(
          const Volume &volume,
          size_t numValues,
          const vly_vec3f *origins,
          const vly_vec3f *directions,
          const vly_range1f *ranges,
          void *rayUserData,
          IntegrationStepFunction integrationStepFunction) = 0;

     protected:
      bool computeGradients;
    };

#define VLY_REGISTER_INTEGRATOR(InternalClass, external_name) \
  VLY_REGISTER_OBJECT(Integrator, integrator, InternalClass, external_name)

  }  // namespace scalar_driver
}  // namespace volley
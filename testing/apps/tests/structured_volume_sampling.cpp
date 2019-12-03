// ======================================================================== //
// Copyright 2019 Intel Corporation                                         //
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

#include "../../external/catch.hpp"
#include "openvkl_testing.h"
#include "ospcommon/utility/multidim_index_sequence.h"
#include "sampling_utility.h"

using namespace ospcommon;
using namespace openvkl::testing;

template <typename PROCEDURAL_VOLUME_TYPE>
void sampling_on_vertices_vs_procedural_values(vec3i dimensions,
                                               vec3i step = vec3i(1))
{
  const vec3f gridOrigin(0.f);
  const vec3f gridSpacing(1.f);

  auto v = ospcommon::make_unique<PROCEDURAL_VOLUME_TYPE>(
      dimensions, gridOrigin, gridSpacing);

  VKLVolume vklVolume = v->getVKLVolume();

  multidim_index_sequence<3> mis(v->getDimensions() / step);

  for (const auto &offset : mis) {
    const auto offsetWithStep = offset * step;

    vec3f objectCoordinates =
        v->transformLocalToObjectCoordinates(offsetWithStep);

    const float proceduralValue = v->computeProceduralValue(objectCoordinates);

    INFO("offset = " << offsetWithStep.x << " " << offsetWithStep.y << " "
                     << offsetWithStep.z);
    INFO("objectCoordinates = " << objectCoordinates.x << " "
                                << objectCoordinates.y << " "
                                << objectCoordinates.z);

    test_scalar_and_vector_sampling(
        vklVolume, objectCoordinates, proceduralValue, 1e-4f);
  }
}

template <template <typename VOXEL_TYPE> class PROCEDURAL_VOLUME_TYPE>
void structured_volume_sampling_test_case_template()
{
  vklLoadModule("ispc_driver");

  VKLDriver driver = vklNewDriver("ispc");
  vklCommitDriver(driver);
  vklSetCurrentDriver(driver);

  SECTION("32-bit addressing")
  {
    SECTION("unsigned char")
    {
      sampling_on_vertices_vs_procedural_values<
          PROCEDURAL_VOLUME_TYPE<unsigned char>>(vec3i(128));
    }

    SECTION("short")
    {
      sampling_on_vertices_vs_procedural_values<PROCEDURAL_VOLUME_TYPE<short>>(
          vec3i(128));
    }

    SECTION("unsigned short")
    {
      sampling_on_vertices_vs_procedural_values<
          PROCEDURAL_VOLUME_TYPE<unsigned short>>(vec3i(128));
    }

    SECTION("float")
    {
      sampling_on_vertices_vs_procedural_values<PROCEDURAL_VOLUME_TYPE<float>>(
          vec3i(128));
    }

    SECTION("double")
    {
      sampling_on_vertices_vs_procedural_values<PROCEDURAL_VOLUME_TYPE<double>>(
          vec3i(128));
    }
  }

  // these are necessarily longer-running tests, so should maybe be split out
  // into a "large" test suite later.
  SECTION("64/32-bit addressing")
  {
    SECTION("unsigned char")
    {
      sampling_on_vertices_vs_procedural_values<
          PROCEDURAL_VOLUME_TYPE<unsigned char>>(vec3i(1025), 16);
    }

    SECTION("short")
    {
      sampling_on_vertices_vs_procedural_values<PROCEDURAL_VOLUME_TYPE<short>>(
          vec3i(813), 16);
    }

    SECTION("unsigned short")
    {
      sampling_on_vertices_vs_procedural_values<
          PROCEDURAL_VOLUME_TYPE<unsigned short>>(vec3i(813), 16);
    }

    SECTION("float")
    {
      sampling_on_vertices_vs_procedural_values<PROCEDURAL_VOLUME_TYPE<float>>(
          vec3i(646), 16);
    }

    SECTION("double")
    {
      sampling_on_vertices_vs_procedural_values<PROCEDURAL_VOLUME_TYPE<double>>(
          vec3i(513), 16);
    }
  }

  // these are necessarily longer-running tests, so should maybe be split out
  // into a "large" test suite later.
  SECTION("64-bit addressing")
  {
    // only do double tests here for now; larger grids incur even more grid
    // accelerator build overhead, which we need to resolve.
    SECTION("double")
    {
      sampling_on_vertices_vs_procedural_values<PROCEDURAL_VOLUME_TYPE<double>>(
          vec3i(11586, 11586, 2), vec3i(16, 16, 1));
    }
  }
}

REGISTER_TEST_CASE(structured_volume_sampling_test_case_template<
                       WaveletStructuredRegularVolume>,
                   "Structured regular volume sampling",
                   "[volume_sampling]");

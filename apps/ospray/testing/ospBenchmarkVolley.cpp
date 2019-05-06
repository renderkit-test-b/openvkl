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

#include <sstream>
#include "OSPRayVolleyTestScene.h"
#include "benchmark/benchmark.h"

static void volume_render_wavelet(benchmark::State &state,
                                  const std::string &rendererType,
                                  const vec2i &windowSize,
                                  int volumeDimension)
{
  initializeOSPRay();
  initializeVolley();

  std::shared_ptr<WaveletProceduralVolume> proceduralVolume(
      new WaveletProceduralVolume(
          vec3i(volumeDimension), vec3f(-1.f), vec3f(2.f / volumeDimension)));

  std::unique_ptr<OSPRayVolleyTestScene> testScene(
      new OSPRayVolleyTestScene(rendererType, proceduralVolume));

  std::unique_ptr<OSPRayWindow> ow = testScene->getOSPRayWindow(windowSize);

  for (auto _ : state) {
    ow->render();
  }

  // enables rates in report output
  state.SetItemsProcessed(state.iterations());

  // save image on completion of benchmark; note we apparently have no way to
  // get the formal benchmark name, so we'll create one here
  static int ppmCounter = 0;
  std::stringstream ss;
  ss << "volume_render_wavelet_" << ppmCounter << ".ppm";
  ow->savePPM(ss.str());
  ppmCounter++;
}

BENCHMARK_CAPTURE(volume_render_wavelet,
                  simple_native / 512,
                  "simple_native",
                  vec2i(1024),
                  512);

BENCHMARK_CAPTURE(volume_render_wavelet,
                  simple_volley / 512,
                  "simple_volley",
                  vec2i(1024),
                  512);

BENCHMARK_CAPTURE(volume_render_wavelet,
                  volley_ray_iterator_volume / 512,
                  "volley_ray_iterator_volume",
                  vec2i(1024),
                  512);

BENCHMARK_CAPTURE(volume_render_wavelet,
                  volley_ray_iterator / 512,
                  "volley_ray_iterator",
                  vec2i(1024),
                  512);

BENCHMARK_MAIN();
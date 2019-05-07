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

struct ManagedObject
{
};

typedef ManagedObject *VLYObject;

typedef struct
{
  float x, y, z;
} vly_vec3f;

typedef struct
{
  float lower, upper;
} vly_range1f;

typedef struct
{
  vly_vec3f lower, upper;
} vly_box3f;

#define __define_wide_types(WIDTH)    \
  typedef struct                      \
  {                                   \
    float x[WIDTH];                   \
    float y[WIDTH];                   \
    float z[WIDTH];                   \
  } vly_vvec3f##WIDTH;                \
                                      \
  typedef struct                      \
  {                                   \
    float lower[WIDTH], upper[WIDTH]; \
  } vly_vrange1f##WIDTH;

__define_wide_types(4);
__define_wide_types(8);
__define_wide_types(16);

#undef __define_wide_types

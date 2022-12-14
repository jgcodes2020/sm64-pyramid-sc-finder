#include "vecutil.hpp"
#include "trig.hpp"
#include "vmath.hpp"

namespace sm64 {
  vec3f get_surface_normal(const tri_verts& v) {
    return vec_cross(v[1] - v[0], v[2] - v[1]);
  }
  
  // equivalent to mtxf_align_terrain_normal
  mat4 align_to_normal(vec3f& up_dir, const vec3f& pos, int16_t yaw) {
    vec3f lat_dir {sins(yaw), 0, coss(yaw)};
    up_dir.normalize();

    vec3f left_dir = vec_cross(up_dir, lat_dir);
    left_dir.normalize();

    vec3f fwd_dir = vec_cross(left_dir, up_dir);
    fwd_dir.normalize();

    // this looks transposed, but that's because
    // SM64 matrices are column-major
    return mat4 {
      vec4f {left_dir[0], left_dir[1], left_dir[2], 0},
      vec4f {up_dir[0],   up_dir[1],   up_dir[2],   0},
      vec4f {fwd_dir[0],  fwd_dir[1],  fwd_dir[2],  0},
      vec4f {pos[0],      pos[1],      pos[2],      1},
    };
  }
}  // namespace sm64
#include "utils.hpp"
#include <cmath>
#include <stdexcept>
#include "trig.hpp"
#include "vmath.hpp"

namespace sm64 {
  vec3f get_surface_normal(const tri_verts& v) {
    vec3f p = (vec3f) v[0], q = (vec3f) v[1], r = (vec3f) v[2];
    return vec_normalize(vec_cross(q - p, r - q));
  }

  // equivalent to mtxf_align_terrain_normal
  mat4 align_to_normal(const vec3f& up_dir, const vec3f& pos, int16_t yaw) {
    vec3f lat_dir {sins(yaw), 0, coss(yaw)};
    vec3f up_dir_n = vec_normalize(up_dir);

    vec3f left_dir = vec_cross(up_dir_n, lat_dir);
    left_dir.normalize();

    vec3f fwd_dir = vec_cross(left_dir, up_dir_n);
    fwd_dir.normalize();

    // this looks transposed, but that's because
    // SM64 matrices are column-major
    return mat4 {
      vec4f {left_dir[0], left_dir[1], left_dir[2], 0},
      vec4f {up_dir_n[0], up_dir_n[1], up_dir_n[2], 0},
      vec4f {fwd_dir[0],  fwd_dir[1],  fwd_dir[2],  0},
      vec4f {pos[0],      pos[1],      pos[2],      1},
    };
  }

  vec3f tform_mult(const mat4& tform, const vec3f& pos) {
    return vec3f {
      tform[0][0] * pos[0] + tform[1][0] * pos[1] + tform[2][0] * pos[2] +
        tform[3][0],
      tform[0][1] * pos[0] + tform[1][1] * pos[1] + tform[2][1] * pos[2] +
        tform[3][1],
      tform[0][2] * pos[0] + tform[1][2] * pos[1] + tform[2][2] * pos[2] +
        tform[3][2]};
  }

  vec3f intersect_hplane(const vec3f& a, const vec3f& b, float y) {
    if ((a.y() < y) == (b.y() < y)) {
      throw std::invalid_argument("Points a and b are on same side of plane");
    }
    // Using a higher precision, for accuracy.
    
    double ratio = ((double) y - a.y()) / ((double) b.y() - a.y());
    double ix = std::lerp((double) a.x(), (double) b.x(), ratio);
    double iz = std::lerp((double) a.z(), (double) b.z(), ratio);
    
    return vec3f {(float) ix, y, (float) iz};
  }
}  // namespace sm64
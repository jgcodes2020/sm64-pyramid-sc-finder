#include "surface.hpp"
#include "utils.hpp"
#include "vmath.hpp"

using namespace sm64;

static tri_verts inv_pyramid_tris[] = {
  {vec3s {307, 307, -306}, vec3s {-306, 307, -306}, vec3s {-306, 307, 307} },
  {vec3s {307, 307, -306}, vec3s {-306, 307, 307},  vec3s {307, 307, 307}  },
  {vec3s {-306, 307, 307}, vec3s {-306, 307, -306}, vec3s {-306, 307, 307} },
  {vec3s {0, 0, 0},        vec3s {307, 307, 307},   vec3s {-306, 307, 307} },
  {vec3s {307, 307, -306}, vec3s {0, 0, 0},         vec3s {-306, 307, -306}},
  {vec3s {0, 0, 0},        vec3s {307, 307, -306},  vec3s {307, 307, 307}  },
};

namespace sm64 {
  void add_inv_pyramid(collision& coll, const vec3s& pos, const vec3f& tilt) {
    mat4 tform = align_to_normal(tilt, (vec3f) pos, 0);
    
    for (const tri_verts& vts : inv_pyramid_tris) {
      vec3f a = (vec3f) vts[0], b = (vec3f) vts[1], c = (vec3f) vts[2];
      a = tform_mult(tform, a);
      b = tform_mult(tform, b);
      c = tform_mult(tform, c);
      
      coll.add(surface((vec3s) a, (vec3s) b, (vec3s) c));
    }
  }
}  // namespace sm64
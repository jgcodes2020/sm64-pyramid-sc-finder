#ifndef SM64_VECUTIL_HPP
#define SM64_VECUTIL_HPP
#include <array>
#include "vmath.hpp"
namespace sm64 {
  using tri_verts = std::array<vec3f, 3>;
  
  vec3f get_surface_normal(const tri_verts& v);
  mat4 align_to_normal(const vec3f& norm, const vec3f& pos, int16_t yaw);
}
#endif
#ifndef SM64_MATH_UTIL_HPP
#define SM64_MATH_UTIL_HPP
#include <array>
#include "vmath.hpp"
namespace sm64 {
  using tri_verts = std::array<vec3s, 3>;
  
  vec3f get_surface_normal(const tri_verts& v);
  mat4 align_to_normal(const vec3f& up_dir, const vec3f& pos, int16_t yaw);
  
  vec3f tform_mult(const mat4& tform, const vec3f& pos);
  
  // Intersects a line and a plane where the plane's equation is (y = n)
  vec3f intersect_hplane(const vec3f& a, const vec3f& b, float n);
}
#endif
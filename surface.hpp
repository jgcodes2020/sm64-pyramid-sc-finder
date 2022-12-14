#ifndef SM64_SURFACE_HPP
#define SM64_SURFACE_HPP
#include <array>
#include "vmath.hpp"
namespace sm64 {
  struct surface {
    std::array<vec3f, 3> vertices;
    vec3f normal;
  }
}
#endif
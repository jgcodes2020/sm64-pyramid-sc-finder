#ifndef PYRA_SOLVER_HPP
#define PYRA_SOLVER_HPP

// Someone decided to call one of those tilting pyramids Pyra,
// so here we are. This functionality isn't related to decomp.
#include <array>
#include "surface.hpp"

namespace pyra {
  std::array<sm64::vec3f, 2> intersect_tri_hplane(const sm64::tri_verts& tri, float y);
}

#endif
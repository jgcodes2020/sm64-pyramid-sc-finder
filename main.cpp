#include "error.hpp"
#include "solver.hpp"
#include "surface.hpp"
#include "trig.hpp"
#include "utils.hpp"
#include "vmath.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

constexpr int16_t lava_y = -3071;
constexpr int16_t sc_y = lava_y + 150;



int main() {
  using namespace sm64;
  
  collision coll;
  sm64::add_inv_pyramid(coll, vec3s {-2866, -3225, -715}, vec3f {0, 1, 0});
  
  for (auto& c : coll.ceils()) {
    // ceiling not steep
    if (c.normal().y() > -0.5)
      continue;
    
    auto [sce1, sce2] = pyra::intersect_tri_hplane(c.verts(), sc_y);
    
    int16_t h_angle = atan2s(c.normal().z(), c.normal().x());
    vec3f back_offset {-sins(h_angle), 0, -coss(h_angle)};
  }
}
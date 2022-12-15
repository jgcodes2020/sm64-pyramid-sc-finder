#include "error.hpp"
#include "surface.hpp"
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
    
    // check if points line on SC y coordinate
    bool p1_i = c[0].y() == sc_y;
    bool p2_i = c[1].y() == sc_y;
    bool p3_i = c[2].y() == sc_y;
    
    // number of intersecting points
    int pcnt = int(p1_i) + int(p2_i) + int(p3_i);
    // edges of squish-cancel haven
    vec3f sce1, sce2;
    
    if (pcnt == 2) {
      // one edge lies along the SC plane
      if (p1_i) {
        sce1 = (vec3f) c[0];
        sce2 = p2_i? (vec3f) c[1] : p3_i? (vec3f) c[2] : throw pyra::abort_error();
      }
      else if (p2_i) {
        sce1 = (vec3f) c[1];
        sce2 = p3_i? (vec3f) c[2] : throw pyra::abort_error();
      }
    }
    else if (pcnt == 1) {
      // one point lies along the SC plane
      // intersect the opposite edge
      if (p1_i) {
        sce1 = (vec3f) c[0];
        sce2 = intersect_hplane((vec3f) c[1], (vec3f) c[2], sc_y);
      }
      else if (p2_i) {
        sce1 = (vec3f) c[0];
        sce2 = intersect_hplane((vec3f) c[1], (vec3f) c[2], sc_y);
      }
      else if (p3_i) {
        sce1 = (vec3f) c[2];
        sce2 = intersect_hplane((vec3f) c[0], (vec3f) c[1], sc_y);
      }
    }
    else if (pcnt == 0) {
      // find edges intersecting the (y = sc_y) plane
      bool e1_i = (c[0].y() < sc_y) ^ (c[1].y() < sc_y);
      bool e2_i = (c[1].y() < sc_y) ^ (c[2].y() < sc_y);
      bool e3_i = (c[0].y() < sc_y) ^ (c[2].y() < sc_y);
      
      if (e1_i) {
        sce1 = intersect_hplane((vec3f) c[0], (vec3f) c[1], sc_y);
        if (e2_i)
          sce2 = intersect_hplane((vec3f) c[1], (vec3f) c[2], sc_y);
        else if (e3_i)
          sce2 = intersect_hplane((vec3f) c[0], (vec3f) c[2], sc_y);
      }
      else if (e2_i && e3_i) {
        sce1 = intersect_hplane((vec3f) c[1], (vec3f) c[2], sc_y);
        sce2 = intersect_hplane((vec3f) c[0], (vec3f) c[2], sc_y);
      }
    }
    else {
      throw pyra::abort_error();
    }
    
    
  }
}
#include "solver.hpp"
#include "error.hpp"
#include <array>
#include "vmath.hpp"
using namespace sm64;

namespace pyra {
  std::array<vec3f, 2> intersect_tri_hplane(const tri_verts &c, float py) {
    // check if points line on SC y coordinate
    bool p1_i = c[0].y() == py;
    bool p2_i = c[1].y() == py;
    bool p3_i = c[2].y() == py;
    
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
        sce2 = intersect_hplane((vec3f) c[1], (vec3f) c[2], py);
      }
      else if (p2_i) {
        sce1 = (vec3f) c[0];
        sce2 = intersect_hplane((vec3f) c[1], (vec3f) c[2], py);
      }
      else if (p3_i) {
        sce1 = (vec3f) c[2];
        sce2 = intersect_hplane((vec3f) c[0], (vec3f) c[1], py);
      }
    }
    else if (pcnt == 0) {
      // find edges intersecting the (y = sc_y) plane
      bool e1_i = (c[0].y() < py) ^ (c[1].y() < py);
      bool e2_i = (c[1].y() < py) ^ (c[2].y() < py);
      bool e3_i = (c[0].y() < py) ^ (c[2].y() < py);
      
      if (e1_i) {
        sce1 = intersect_hplane((vec3f) c[0], (vec3f) c[1], py);
        if (e2_i)
          sce2 = intersect_hplane((vec3f) c[1], (vec3f) c[2], py);
        else if (e3_i)
          sce2 = intersect_hplane((vec3f) c[0], (vec3f) c[2], py);
      }
      else if (e2_i && e3_i) {
        sce1 = intersect_hplane((vec3f) c[1], (vec3f) c[2], py);
        sce2 = intersect_hplane((vec3f) c[0], (vec3f) c[2], py);
      }
    }
    else {
      throw pyra::abort_error();
    }
    
    return {sce1, sce2};
  }
}
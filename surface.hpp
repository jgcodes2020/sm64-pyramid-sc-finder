#ifndef SM64_SURFACE_HPP
#define SM64_SURFACE_HPP
#include <array>
#include <vector>

#include "utils.hpp"
#include "vmath.hpp"


namespace sm64 {
  // Class representing a surface.
  class surface {
  public:
    surface(const vec3s& p1, const vec3s& p2, const vec3s& p3) :
      m_verts {p1, p2, p3}, m_normal(get_surface_normal(m_verts)) {}
    
    surface& operator=(const tri_verts& verts) {
      m_verts[0] = verts[0];
      m_verts[1] = verts[1];
      m_verts[2] = verts[2];
      m_normal = get_surface_normal(m_verts);
    }
    
    const vec3s& operator[](size_t i) const {
      return m_verts[i];
    }
    
    const vec3f& normal() const {
      return m_normal;
    }
    
  private:
    tri_verts m_verts;
    vec3f m_normal;
  };
  
  // Class representing a collection of surfaces.
  class collision {
  public:
    collision() = default;
    
    void clear() {
      m_walls.clear();
      m_floors.clear();
      m_ceils.clear();
    }
    
    void add(const surface& s) {
      if (s.normal().y() > 0.01) {
        m_floors.push_back(s);
      }
      else if (s.normal().y() < -0.01) {
        m_ceils.push_back(s);
      }
      else {
        m_walls.push_back(s);
      }
    }
    
    const std::vector<surface>& walls() const {
      return m_walls;
    }
    const std::vector<surface>& floors() const {
      return m_floors;
    }
    const std::vector<surface>& ceils() const {
      return m_ceils;
    }
    
  private:
    std::vector<surface> m_walls;
    std::vector<surface> m_floors;
    std::vector<surface> m_ceils;
  };
  
  // Adds a tilting inverted pyramid to a collision object.
  void add_inv_pyramid(collision& coll, vec3s& pos, vec3f& tilt);
}  // namespace sm64
#endif
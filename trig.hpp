#ifndef SM64_TRIG_HPP
#define SM64_TRIG_HPP

#include <cstdint>

namespace sm64 {
  extern const float g_sine_table[0x1400];
  extern const int16_t g_atan_table[0x401];
  
  inline float sins(int16_t theta) {
    return g_sine_table[uint16_t(theta) >> 4];
  }
  
  inline float coss(int16_t theta) {
    return (g_sine_table + 0x400)[uint16_t(theta) >> 4];
  }
  
  inline int16_t atan2s(float y, float x);
  
  namespace details {
    struct atan2s_helper {
      inline friend int16_t sm64::atan2s(float y, float x);
    private:
      static inline int16_t atan2_lookup(float y, float x) {
        return (x == 0)? 0 : g_atan_table[(int32_t) (y / x * 1024 + 0.5f)];
      }
    };
  }
  
  inline int16_t atan2s(float y, float x) {
    using h = details::atan2s_helper;
    
    if (x >= 0) {
      if (y >= 0) {
        return (y >= x)? h::atan2_lookup(x, y) : 0x4000 - h::atan2_lookup(y, x);
      }
      else {
        y = -y;
        return (y < x)? 0x4000 + h::atan2_lookup(y, x) : 0x8000 - h::atan2_lookup(x, y);
      }
    }
    else {
      x = -x;
      if (y < 0) {
        y = -y;
        return (y >= x)? 0x8000 + h::atan2_lookup(x, y) : 0xC000 - h::atan2_lookup(y, x);
      }
      else {
        return (y < x)? 0xC000 + h::atan2_lookup(y, x) : -h::atan2_lookup(x, y);
      }
    }
  }
}

#endif
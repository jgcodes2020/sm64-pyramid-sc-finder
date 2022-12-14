#ifndef SM64_VMATH_HPP
#define SM64_VMATH_HPP

#include <utility>
#include <cstdint>
#include <array>
#include <cstddef>
#include <cmath>
#include <type_traits>

#define SM64_VMATH_FOLD_RETURN(N, expr) \
  [&]<size_t... Is>(std::index_sequence<Is...>) {\
    return expr ;\
  }(std::make_index_sequence<N> {})
  
#define SM64_VMATH_FOLD_ITER(N, expr) \
  [&]<size_t... Is>(std::index_sequence<Is...>) {\
    (expr);\
  }(std::make_index_sequence<N> {})

#define SM64_VMATH_VEC_TYPEDEFS(S, T) \
  using vec2##S = vec_t<T, 2>;\
  using vec3##S = vec_t<T, 3>;\
  using vec4##S = vec_t<T, 4>;

namespace sm64 {
  static_assert(std::is_arithmetic_v<bool>, "test");
  
  template <class T, size_t N>
  struct vec_t {
    static_assert((std::is_arithmetic_v<T> && !std::is_same_v<T, bool>), "T must be an integer or floating-point type");
    static_assert((!std::is_const_v<T> && !std::is_volatile_v<T>), "T cannot be const or volatile");
    
  public:
    T& operator[](size_t i) {
      return _m_data[i];
    }
    
    const T& operator[](size_t i) const {
      return _m_data[i];
    }
  
    friend vec_t operator+(const vec_t& a, const vec_t& b) {
      return SM64_VMATH_FOLD_RETURN(N, vec_t {a[Is] + b[Is]...});
    }
    vec_t& operator+=(const vec_t& b) {
      SM64_VMATH_FOLD_ITER(N, (((*this)[Is] += b[Is]), ...));
      return *this;
    }
    
    friend vec_t operator-(const vec_t& a, const vec_t& b) {
      return SM64_VMATH_FOLD_RETURN(N, vec_t {a[Is] - b[Is]...});
    }
    vec_t& operator-=(const vec_t& b) {
      SM64_VMATH_FOLD_ITER(N, (((*this)[Is] -= b[Is]), ...));
      return *this;
    }
    
    friend vec_t operator*(const vec_t& a, T b) {
      return SM64_VMATH_FOLD_RETURN(N, vec_t {a[Is] * b...});
    }
    friend vec_t operator*(T a, const vec_t& b) {
      return SM64_VMATH_FOLD_RETURN(N, vec_t {a * b[Is]...});
    }
    vec_t& operator*=(T b) {
      SM64_VMATH_FOLD_ITER(N, (((*this)[Is] *= b), ...));
      return *this;
    }
    
    friend vec_t operator/(const vec_t& a, T b) {
      return SM64_VMATH_FOLD_RETURN(N, vec_t {a[Is] / b...});
    }
    vec_t& operator/=(T b) {
      SM64_VMATH_FOLD_ITER(N, (((*this)[Is] /= b), ...));
      return *this;
    }
    
    template <class U> requires (std::is_convertible_v<T, U>)
    explicit operator vec_t<U, N>() {
      return SM64_VMATH_FOLD_RETURN(N, (vec_t<U, N> {static_cast<U>((*this)[Is])...}));
    }
    
    // Normalize the current vector by the SM64 algorithm.
    vec_t& normalize() {
      T inv_sqrt = T(1.0) / std::sqrt(vec_dot(*this, *this));
      return *this *= inv_sqrt;
    }
  public:
    T _m_data[N];
  };
  
  template <class T, size_t N>
  inline T vec_dot(const vec_t<T, N>& a, const vec_t<T, N>& b) {
    return SM64_VMATH_FOLD_RETURN(N, (... + (a[Is] * b[Is])));
  }
  
  template <class T>
  inline vec_t<T, 3> vec_cross(const vec_t<T, 3>& a, const vec_t<T, 3>& b) {
    return vec_t<T, 3> {
      a[1] * b[2] - a[2] * b[1],
      a[2] * b[0] - b[0] * a[2],
      a[0] * b[1] - b[0] * a[1]
    };
  }
  
  // Normalize by the SM64 algorithm.
  template <class T, size_t N>
  inline vec_t<T, N> vec_normalize(const vec_t<T, N>& a) {
    static_assert(std::is_floating_point_v<T>, "Normalization only makes sense for floating-point types");
    T inv_sqrt = T(1.0) / std::sqrt(vec_dot(a, a));
    return a * inv_sqrt;
  }
  
  SM64_VMATH_VEC_TYPEDEFS(f, float);
  SM64_VMATH_VEC_TYPEDEFS(d, double);
  SM64_VMATH_VEC_TYPEDEFS(i, int32_t);
  SM64_VMATH_VEC_TYPEDEFS(s, int16_t);
  
  // Generic 4x4 matrix.
  template <class T>
  struct mat4_t {
  public:
    vec_t<T, 4>& operator[](size_t n) {
      return _m_data[n];
    }
    
    const vec_t<T, 4>& operator[](size_t n) const {
      return _m_data[n];
    }
  public:
    vec_t<T, 4> _m_data[4];
  };
  
  using mat4 = mat4_t<float>;
}

#undef SM64_VMATH_FOLD_ITER
#undef SM64_VMATH_FOLD_RETURN
#undef SM64_VMATH_VEC_TYPEDEFS
#endif
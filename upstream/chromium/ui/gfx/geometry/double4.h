// Copyright 2022 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_GEOMETRY_DOUBLE4_H_
#define UI_GFX_GEOMETRY_DOUBLE4_H_

#include <stddef.h>
#include <stdint.h>

#include <type_traits>

#include "base/compiler_specific.h"
#include "base/containers/span.h"

namespace gfx {

// This header defines Double4 type for vectorized SIMD operations used in
// optimized transformation code. The type should be only used for local
// variables, or inline function parameters or return values. Don't use the
// type in other cases (e.g. for class data members) due to constraints
// (e.g. alignment).
//
// Here are some examples of usages:
//
//   double matrix[4][4] = ...;
//   // The scalar value will be applied to all components.
//   Double4 c0 = Load(matrix[0]) + 5;
//   Double4 c1 = Load(matrix[1]) * Double4{1, 2, 3, 4};
//
//   Double4 v = c0 * c1;
//   // s0/s1/s2/s3 are preferred to x/y/z/w for consistency.
//   double a = v.s0 + Sum(c1);
//   // v.s3210 is equivalent to {v.s3, v.s2, v.s1, v.s0}.
//   // Should use this form instead of __builtin_shufflevector() etc.
//   Double4 swapped = {v[3], v[2], v[1], v[0]};
//
//   // Logical operations.
//   bool b1 = AllTrue(swapped == c0);
//   // & is preferred to && to reduce branches.
//   bool b2 = AllTrue((c0 == c1) & (c0 == v) & (c0 >= swapped));
//
//   Store(swapped, matrix_[2]);
//   Store(v, matrix_[3]);
//
// We use the gcc extension (supported by clang) instead of the clang extension
// to make sure the code can compile with either gcc or clang.
//
// For more details, see
//   https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html

#if defined(_MSC_VER) && !defined(__clang__)
struct DoubleBoolean4 {
  int64_t lanes[4];

  int64_t& operator[](size_t i) { return lanes[i]; }
  const int64_t& operator[](size_t i) const { return lanes[i]; }
};

struct FloatBoolean4 {
  int32_t lanes[4];

  int32_t& operator[](size_t i) { return lanes[i]; }
  const int32_t& operator[](size_t i) const { return lanes[i]; }
};

struct Double4 {
  double lanes[4];

  double& operator[](size_t i) { return lanes[i]; }
  const double& operator[](size_t i) const { return lanes[i]; }
};

struct Float4 {
  float lanes[4];

  float& operator[](size_t i) { return lanes[i]; }
  const float& operator[](size_t i) const { return lanes[i]; }
};

ALWAYS_INLINE int64_t DoubleBoolLane(bool value) {
  return value ? ~int64_t{0} : int64_t{0};
}

ALWAYS_INLINE int32_t FloatBoolLane(bool value) {
  return value ? ~int32_t{0} : int32_t{0};
}

ALWAYS_INLINE Double4 operator+(Double4 lhs, Double4 rhs) {
  return {lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2], lhs[3] + rhs[3]};
}

ALWAYS_INLINE Double4 operator+(Double4 lhs, double rhs) {
  return {lhs[0] + rhs, lhs[1] + rhs, lhs[2] + rhs, lhs[3] + rhs};
}

ALWAYS_INLINE Double4 operator+(double lhs, Double4 rhs) {
  return rhs + lhs;
}

ALWAYS_INLINE Double4& operator+=(Double4& lhs, Double4 rhs) {
  lhs = lhs + rhs;
  return lhs;
}

ALWAYS_INLINE Double4& operator+=(Double4& lhs, double rhs) {
  lhs = lhs + rhs;
  return lhs;
}

ALWAYS_INLINE Double4 operator-(Double4 lhs, Double4 rhs) {
  return {lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3]};
}

ALWAYS_INLINE Double4 operator-(Double4 lhs, double rhs) {
  return {lhs[0] - rhs, lhs[1] - rhs, lhs[2] - rhs, lhs[3] - rhs};
}

ALWAYS_INLINE Double4 operator-(double lhs, Double4 rhs) {
  return {lhs - rhs[0], lhs - rhs[1], lhs - rhs[2], lhs - rhs[3]};
}

ALWAYS_INLINE Double4& operator-=(Double4& lhs, Double4 rhs) {
  lhs = lhs - rhs;
  return lhs;
}

ALWAYS_INLINE Double4& operator-=(Double4& lhs, double rhs) {
  lhs = lhs - rhs;
  return lhs;
}

ALWAYS_INLINE Double4 operator*(Double4 lhs, Double4 rhs) {
  return {lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2], lhs[3] * rhs[3]};
}

ALWAYS_INLINE Double4 operator*(Double4 lhs, double rhs) {
  return {lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs, lhs[3] * rhs};
}

ALWAYS_INLINE Double4 operator*(double lhs, Double4 rhs) {
  return rhs * lhs;
}

ALWAYS_INLINE Double4& operator*=(Double4& lhs, Double4 rhs) {
  lhs = lhs * rhs;
  return lhs;
}

ALWAYS_INLINE Double4& operator*=(Double4& lhs, double rhs) {
  lhs = lhs * rhs;
  return lhs;
}

ALWAYS_INLINE Double4 operator/(Double4 lhs, Double4 rhs) {
  return {lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2], lhs[3] / rhs[3]};
}

ALWAYS_INLINE Double4& operator/=(Double4& lhs, Double4 rhs) {
  lhs = lhs / rhs;
  return lhs;
}

ALWAYS_INLINE DoubleBoolean4 operator==(Double4 lhs, Double4 rhs) {
  return {DoubleBoolLane(lhs[0] == rhs[0]), DoubleBoolLane(lhs[1] == rhs[1]),
          DoubleBoolLane(lhs[2] == rhs[2]), DoubleBoolLane(lhs[3] == rhs[3])};
}

ALWAYS_INLINE DoubleBoolean4 operator!=(Double4 lhs, Double4 rhs) {
  return {DoubleBoolLane(lhs[0] != rhs[0]), DoubleBoolLane(lhs[1] != rhs[1]),
          DoubleBoolLane(lhs[2] != rhs[2]), DoubleBoolLane(lhs[3] != rhs[3])};
}

ALWAYS_INLINE DoubleBoolean4 operator<(Double4 lhs, Double4 rhs) {
  return {DoubleBoolLane(lhs[0] < rhs[0]), DoubleBoolLane(lhs[1] < rhs[1]),
          DoubleBoolLane(lhs[2] < rhs[2]), DoubleBoolLane(lhs[3] < rhs[3])};
}

ALWAYS_INLINE DoubleBoolean4 operator<=(Double4 lhs, Double4 rhs) {
  return {DoubleBoolLane(lhs[0] <= rhs[0]), DoubleBoolLane(lhs[1] <= rhs[1]),
          DoubleBoolLane(lhs[2] <= rhs[2]), DoubleBoolLane(lhs[3] <= rhs[3])};
}

ALWAYS_INLINE DoubleBoolean4 operator>(Double4 lhs, Double4 rhs) {
  return {DoubleBoolLane(lhs[0] > rhs[0]), DoubleBoolLane(lhs[1] > rhs[1]),
          DoubleBoolLane(lhs[2] > rhs[2]), DoubleBoolLane(lhs[3] > rhs[3])};
}

ALWAYS_INLINE DoubleBoolean4 operator>=(Double4 lhs, Double4 rhs) {
  return {DoubleBoolLane(lhs[0] >= rhs[0]), DoubleBoolLane(lhs[1] >= rhs[1]),
          DoubleBoolLane(lhs[2] >= rhs[2]), DoubleBoolLane(lhs[3] >= rhs[3])};
}

ALWAYS_INLINE DoubleBoolean4 operator&(DoubleBoolean4 lhs, DoubleBoolean4 rhs) {
  return {lhs[0] & rhs[0], lhs[1] & rhs[1], lhs[2] & rhs[2],
          lhs[3] & rhs[3]};
}

ALWAYS_INLINE Float4 operator+(Float4 lhs, Float4 rhs) {
  return {lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2], lhs[3] + rhs[3]};
}

ALWAYS_INLINE Float4& operator+=(Float4& lhs, Float4 rhs) {
  lhs = lhs + rhs;
  return lhs;
}

ALWAYS_INLINE Float4 operator-(Float4 lhs, Float4 rhs) {
  return {lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3]};
}

ALWAYS_INLINE Float4& operator-=(Float4& lhs, Float4 rhs) {
  lhs = lhs - rhs;
  return lhs;
}

ALWAYS_INLINE Float4 operator*(Float4 lhs, Float4 rhs) {
  return {lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2], lhs[3] * rhs[3]};
}

ALWAYS_INLINE Float4& operator*=(Float4& lhs, Float4 rhs) {
  lhs = lhs * rhs;
  return lhs;
}

ALWAYS_INLINE FloatBoolean4 operator==(Float4 lhs, Float4 rhs) {
  return {FloatBoolLane(lhs[0] == rhs[0]), FloatBoolLane(lhs[1] == rhs[1]),
          FloatBoolLane(lhs[2] == rhs[2]), FloatBoolLane(lhs[3] == rhs[3])};
}

ALWAYS_INLINE FloatBoolean4 operator&(FloatBoolean4 lhs, FloatBoolean4 rhs) {
  return {lhs[0] & rhs[0], lhs[1] & rhs[1], lhs[2] & rhs[2],
          lhs[3] & rhs[3]};
}
#else
#if !defined(__GNUC__) && !defined(__clang__)
#error Unsupported compiler.
#endif
typedef double __attribute__((vector_size(4 * sizeof(double)))) Double4;
typedef float __attribute__((vector_size(4 * sizeof(float)))) Float4;
typedef int64_t __attribute__((vector_size(4 * sizeof(int64_t))))
DoubleBoolean4;
typedef int32_t __attribute__((vector_size(4 * sizeof(int32_t)))) FloatBoolean4;
#endif

ALWAYS_INLINE double Sum(Double4 v) {
  return v[0] + v[1] + v[2] + v[3];
}

ALWAYS_INLINE Double4 LoadDouble4(base::span<const double, 4> s) {
  return Double4{s[0], s[1], s[2], s[3]};
}

ALWAYS_INLINE void StoreDouble4(Double4 v, base::span<double, 4> d) {
  d[0] = v[0];
  d[1] = v[1];
  d[2] = v[2];
  d[3] = v[3];
}

// The parameter should be the result of Double4/Float4 operations that would
// produce bool results if they were original scalar operators, e.g.
//   auto b4 = double4_a == double4_b;
// A zero value of a component of |b4| means false, otherwise true.
// This function checks whether all 4 components in |b4| are true.
// |&| instead of |&&| is used to avoid branches, which results shorter and
// faster code in most cases. It's used like:
//   if (AllTrue(double4_a == double4_b))
//     ...
//   if (AllTrue((double4_a1 == double4_b1) & (double4_a2 == double4_b2)))
//     ...
ALWAYS_INLINE int64_t AllTrue(DoubleBoolean4 b4) {
  return b4[0] & b4[1] & b4[2] & b4[3];
}

ALWAYS_INLINE int32_t AllTrue(FloatBoolean4 b4) {
  return b4[0] & b4[1] & b4[2] & b4[3];
}

}  // namespace gfx

#endif  // UI_GFX_GEOMETRY_DOUBLE4_H_

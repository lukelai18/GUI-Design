//  Copyright (c) 2022 Daniel Moreno. All rights reserved.
//

#pragma once

#include <cmath>
#include <cfloat>

namespace course
{
  template <typename Scalar>
  class Vector2
  {
    Scalar m_[2];
  public:
    Vector2(Scalar x = 0, Scalar y = 0) : m_{ x, y }
    {
    }

    const Scalar& x() const { return m_[0]; }
    const Scalar& y() const { return m_[1]; }

    Scalar& x() { return m_[0]; }
    Scalar& y() { return m_[1]; }

    Scalar squaredNorm() const
    {
      return m_[0] * m_[0] + m_[1] * m_[1];
    }

    Scalar norm() const
    {
      return std::sqrt(squaredNorm());
    }

    Vector2 normalized() const
    {
      const double s{ squaredNorm() };
      if (std::abs(s - 1.0) > DBL_EPSILON)
      {
        return (*this) / std::sqrt(s);
      }
      return *this;
    }

    Vector2 operator-() const
    {
      return Vector2{ -m_[0], -m_[1] };
    }

    Vector2 operator*(const Scalar& s) const
    {
      return Vector2{ m_[0] * s, m_[1] * s };
    }

    Vector2 operator/(const Scalar& s) const
    {
      return Vector2{ m_[0] / s, m_[1] / s };
    }

    Vector2 operator+(const Vector2& v) const
    {
      return Vector2{ m_[0] + v.m_[0], m_[1] + v.m_[1] };
    }

    Vector2 operator-(const Vector2& v) const
    {
      return Vector2{ m_[0] - v.m_[0], m_[1] - v.m_[1] };
    }

    Scalar dot(const Vector2& v) const
    {
      return m_[0] * v.m_[0] + m_[1] * v.m_[1];
    }

    Vector2 reflect(const Vector2& v) const
    {
      //R = I - 2(I*N) N
      //R: reflected vector
      //N: normal vector of reflection surface
      //I: incident vector (pointing towards surface)
      const Scalar s{ v.norm() };
      const Vector2 i{ v / s };
      const Vector2 n{ normalized() };
      const Vector2 r{ i - 2 * i.dot(n) * n };
      return r * s;
    }

  };

  template <typename Scalar>
  Vector2<Scalar> operator*(const Scalar& s, const Vector2<Scalar>& m)
  {
    return m * s;
  }

  using Vector2d = Vector2<double>;
}
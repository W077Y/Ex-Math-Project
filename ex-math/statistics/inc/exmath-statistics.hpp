#pragma once
#ifndef EXMATH_STATISTICS_HPP_INCLUDED
#define EXMATH_STATISTICS_HPP_INCLUDED

#include <cmath>
#include <cstdint>
#include <limits>
#include <span>

namespace exmath::statistics
{

  class max_min_mean_value_calculator_t
  {
  public:
    using value_type = double;

    max_min_mean_value_calculator_t() = default;

    max_min_mean_value_calculator_t(std::span<value_type> const values) { this->operator()(values); }

    template <typename functor>
    max_min_mean_value_calculator_t(functor const& ftor, uint32_t max_idx)
        : m_count(max_idx)
    {
      for (std::size_t i = 0; i < max_idx; i++)
      {
        value_type const val = ftor(i);

        if (this->m_max < val)
          this->m_max = val;
        if (this->m_min > val)
          this->m_min = val;

        this->m_mean += val;
        this->m_x_sqr += val * val;
      }

      this->m_mean /= this->m_count;
      this->m_x_sqr /= this->m_count;
    }

    auto operator()(value_type const& value) noexcept -> max_min_mean_value_calculator_t&
    {
      if (std::isnan(value))
        return *this;

      if (this->m_max < value)
        this->m_max = value;
      if (this->m_min > value)
        this->m_min = value;

      this->m_count++;
      value_type const scale = 1.0 / static_cast<value_type>(this->m_count);
      this->m_mean += (value - this->m_mean) * scale;
      this->m_x_sqr += (value * value - this->m_x_sqr) * scale;

      return *this;
    }

    auto operator()(std::span<value_type> const values) noexcept -> max_min_mean_value_calculator_t&
    {
      for (value_type const val : values)
      {
        this->operator()(val);
      }
      return *this;
    }

    auto operator()(max_min_mean_value_calculator_t const& value) noexcept -> max_min_mean_value_calculator_t&
    {
      if (this->m_max < value.m_max)
        this->m_max = value.m_max;
      if (this->m_min > value.m_min)
        this->m_min = value.m_min;

      this->m_count += value.m_count;
      value_type const scale = static_cast<value_type>(value.m_count) / static_cast<value_type>(this->m_count);
      this->m_mean += (value.m_mean - this->m_mean) * scale;
      this->m_x_sqr += (value.m_x_sqr - this->m_x_sqr) * scale;
      return *this;
    }

    value_type get_mean() const noexcept { return this->m_mean; }

    value_type get_max() const noexcept { return this->m_max; }

    value_type get_min() const noexcept { return this->m_min; }

    value_type get_var() const noexcept
    {
      value_type const scale = static_cast<value_type>(this->m_count) / static_cast<value_type>(this->m_count - 1);
      return (this->m_x_sqr - this->m_mean * this->m_mean) * scale;
    }

  private:
    uint32_t   m_count = 0;
    value_type m_max   = -std::numeric_limits<value_type>::infinity();
    value_type m_min   = std::numeric_limits<value_type>::infinity();
    value_type m_mean  = 0.0f;
    value_type m_x_sqr = 0.0f;
  };

}    // namespace exmath::statistics

#endif

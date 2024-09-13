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
    using count_type = std::size_t;
    using value_type = double;

    max_min_mean_value_calculator_t() = default;

    max_min_mean_value_calculator_t(value_type const & value) { this->operator()(value); }

    max_min_mean_value_calculator_t(std::span<value_type const> const& values)
    {
      for (value_type const value : values)
      {
        if (std::isnan(value))
          continue;

        if (this->m_max < value)
          this->m_max = value;
        if (this->m_min > value)
          this->m_min = value;

        this->m_mean += value;
        this->m_x_sqr += value * value;
      }

      this->m_count          = values.size();
      value_type const scale = 1.0 / static_cast<value_type>(this->m_count);
      this->m_mean *= scale;
      this->m_x_sqr *= scale;
    }

    template <typename functor> max_min_mean_value_calculator_t(functor const& ftor, count_type max_idx)
    {
      for (count_type i = 0; i < max_idx; i++)
      {
        value_type const value = ftor(i);
        if (std::isnan(value))
          continue;

        if (this->m_max < value)
          this->m_max = value;
        if (this->m_min > value)
          this->m_min = value;

        this->m_mean += value;
        this->m_x_sqr += value * value;
      }

      this->m_count          = max_idx;
      value_type const scale = 1.0 / static_cast<value_type>(this->m_count);
      this->m_mean *= scale;
      this->m_x_sqr *= scale;
    }

    auto operator()(value_type const& value) noexcept -> max_min_mean_value_calculator_t&
    {
      if (std::isnan(value))
        return *this;

      if (this->m_max < value)
        this->m_max = value;
      if (this->m_min > value)
        this->m_min = value;

      if (this->m_count < std::numeric_limits<count_type>::max())
        this->m_count++;

      value_type const scale = 1.0 / static_cast<value_type>(this->m_count);
      this->m_mean += (value - this->m_mean) * scale;
      this->m_x_sqr += (value * value - this->m_x_sqr) * scale;

      return *this;
    }

    template <typename functor> auto operator()(functor const& ftor, count_type max_idx) noexcept -> max_min_mean_value_calculator_t&
    {
      return this->operator()(max_min_mean_value_calculator_t{ ftor, max_idx });
    }
    auto operator()(std::span<value_type const> const& values) noexcept -> max_min_mean_value_calculator_t&
    {
      return this->operator()(max_min_mean_value_calculator_t{ values });
    }

    auto operator()(max_min_mean_value_calculator_t const& value) noexcept -> max_min_mean_value_calculator_t&
    {
      if (this->m_max < value.m_max)
        this->m_max = value.m_max;
      if (this->m_min > value.m_min)
        this->m_min = value.m_min;

      if ((std::numeric_limits<count_type>::max() - this->m_count) > value.m_count)
        this->m_count += value.m_count;
      else
        this->m_count = std::numeric_limits<count_type>::max();

      value_type const scale = static_cast<value_type>(value.m_count) / static_cast<value_type>(this->m_count);
      this->m_mean += (value.m_mean - this->m_mean) * scale;
      this->m_x_sqr += (value.m_x_sqr - this->m_x_sqr) * scale;
      return *this;
    }

    count_type get_number_of_values() const noexcept { return this->m_count; }
    value_type get_max() const noexcept { return this->m_max; }
    value_type get_min() const noexcept { return this->m_min; }
    value_type get_mean() const noexcept
    {
      if (this->m_count == 0)
        return std::numeric_limits<value_type>::quiet_NaN();
      return this->m_mean;
    }
    value_type get_variance() const noexcept
    {
      if (this->m_count < 2)
        return std::numeric_limits<value_type>::quiet_NaN();
      value_type const scale = static_cast<value_type>(this->m_count) / static_cast<value_type>(this->m_count - 1);
      return std::abs(this->m_x_sqr - this->m_mean * this->m_mean) * scale;
    }
    value_type get_standard_deviation() const noexcept { return std::sqrt(this->get_variance()); }

  private:
    count_type m_count = 0;
    value_type m_max   = -std::numeric_limits<value_type>::infinity();
    value_type m_min   = std::numeric_limits<value_type>::infinity();
    value_type m_mean  = 0.0f;
    value_type m_x_sqr = 0.0f;
  };

  max_min_mean_value_calculator_t operator+(max_min_mean_value_calculator_t const& lhs, max_min_mean_value_calculator_t const& rhs) noexcept
  {
    max_min_mean_value_calculator_t ret{ lhs };
    return ret(rhs);
  }
  max_min_mean_value_calculator_t& operator+=(max_min_mean_value_calculator_t& lhs, max_min_mean_value_calculator_t const& rhs) noexcept { return lhs(rhs); }
}    // namespace exmath::statistics

#endif

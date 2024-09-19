#include <array>
#include <atomic>
#include <exmath.hpp>
#include <iostream>
#include <ut_catch.hpp>

TEST_CASE()
{
  exmath::intervals::Interval_open<float> const inter = { -1.0f, 1.0f };

  REQUIRE(inter.get_left_value() == -1.0f);
  REQUIRE(inter.get_right_value() == 1.0f);
  REQUIRE(inter.get_type() == exmath::intervals::Interval_Types::open);

  REQUIRE(inter.includes(0.0f));
  REQUIRE_FALSE(inter.includes(-1.0f));
  REQUIRE_FALSE(inter.includes(1.0f));
  REQUIRE_FALSE(inter.includes(-2.0f));
  REQUIRE_FALSE(inter.includes(2.0f));
  REQUIRE_FALSE(inter.includes(std::numeric_limits<float>::quiet_NaN()));
  REQUIRE_FALSE(inter.includes(-std::numeric_limits<float>::infinity()));
  REQUIRE_FALSE(inter.includes(std::numeric_limits<float>::infinity()));

  REQUIRE(inter.saturate(0.0f) == 0.0f);
  REQUIRE(inter.saturate(-1.0f) == -1.0f);
  REQUIRE(inter.saturate(1.0f) == 1.0f);
  REQUIRE(inter.saturate(-2.0f) == -1.0f);
  REQUIRE(inter.saturate(2.0f) == 1.0f);
  REQUIRE(std::isnan(inter.saturate(std::numeric_limits<float>::quiet_NaN())));
  REQUIRE(inter.saturate(-std::numeric_limits<float>::infinity()) == -1.0f);
  REQUIRE(inter.saturate(std::numeric_limits<float>::infinity()) == 1.0f);
}

TEST_CASE()
{
  exmath::intervals::Interval_left_open<float> const inter = { -1.0f, 1.0f };

  REQUIRE(inter.get_left_value() == -1.0f);
  REQUIRE(inter.get_right_value() == 1.0f);
  REQUIRE(inter.get_type() == exmath::intervals::Interval_Types::left_open);

  REQUIRE(inter.includes(0.0f));
  REQUIRE_FALSE(inter.includes(-1.0f));
  REQUIRE(inter.includes(1.0f));
  REQUIRE_FALSE(inter.includes(-2.0f));
  REQUIRE_FALSE(inter.includes(2.0f));
  REQUIRE_FALSE(inter.includes(std::numeric_limits<float>::quiet_NaN()));
  REQUIRE_FALSE(inter.includes(-std::numeric_limits<float>::infinity()));
  REQUIRE_FALSE(inter.includes(std::numeric_limits<float>::infinity()));

  REQUIRE(inter.saturate(0.0f) == 0.0f);
  REQUIRE(inter.saturate(-1.0f) == -1.0f);
  REQUIRE(inter.saturate(1.0f) == 1.0f);
  REQUIRE(inter.saturate(-2.0f) == -1.0f);
  REQUIRE(inter.saturate(2.0f) == 1.0f);
  REQUIRE(std::isnan(inter.saturate(std::numeric_limits<float>::quiet_NaN())));
  REQUIRE(inter.saturate(-std::numeric_limits<float>::infinity()) == -1.0f);
  REQUIRE(inter.saturate(std::numeric_limits<float>::infinity()) == 1.0f);
}

TEST_CASE()
{
  exmath::intervals::Interval_right_open<float> const inter = { -1.0f, 1.0f };

  REQUIRE(inter.get_left_value() == -1.0f);
  REQUIRE(inter.get_right_value() == 1.0f);
  REQUIRE(inter.get_type() == exmath::intervals::Interval_Types::right_open);

  REQUIRE(inter.includes(0.0f));
  REQUIRE(inter.includes(-1.0f));
  REQUIRE_FALSE(inter.includes(1.0f));
  REQUIRE_FALSE(inter.includes(-2.0f));
  REQUIRE_FALSE(inter.includes(2.0f));
  REQUIRE_FALSE(inter.includes(std::numeric_limits<float>::quiet_NaN()));
  REQUIRE_FALSE(inter.includes(-std::numeric_limits<float>::infinity()));
  REQUIRE_FALSE(inter.includes(std::numeric_limits<float>::infinity()));

  REQUIRE(inter.saturate(0.0f) == 0.0f);
  REQUIRE(inter.saturate(-1.0f) == -1.0f);
  REQUIRE(inter.saturate(1.0f) == 1.0f);
  REQUIRE(inter.saturate(-2.0f) == -1.0f);
  REQUIRE(inter.saturate(2.0f) == 1.0f);
  REQUIRE(std::isnan(inter.saturate(std::numeric_limits<float>::quiet_NaN())));
  REQUIRE(inter.saturate(-std::numeric_limits<float>::infinity()) == -1.0f);
  REQUIRE(inter.saturate(std::numeric_limits<float>::infinity()) == 1.0f);
}

TEST_CASE()
{
  exmath::intervals::Interval_closed<float> const inter = { -1.0f, 1.0f };

  REQUIRE(inter.get_left_value() == -1.0f);
  REQUIRE(inter.get_right_value() == 1.0f);
  REQUIRE(inter.get_type() == exmath::intervals::Interval_Types::closed);

  REQUIRE(inter.includes(0.0f));
  REQUIRE(inter.includes(-1.0f));
  REQUIRE(inter.includes(1.0f));
  REQUIRE_FALSE(inter.includes(-2.0f));
  REQUIRE_FALSE(inter.includes(2.0f));
  REQUIRE_FALSE(inter.includes(std::numeric_limits<float>::quiet_NaN()));
  REQUIRE_FALSE(inter.includes(-std::numeric_limits<float>::infinity()));
  REQUIRE_FALSE(inter.includes(std::numeric_limits<float>::infinity()));

  REQUIRE(inter.saturate(0.0f) == 0.0f);
  REQUIRE(inter.saturate(-1.0f) == -1.0f);
  REQUIRE(inter.saturate(1.0f) == 1.0f);
  REQUIRE(inter.saturate(-2.0f) == -1.0f);
  REQUIRE(inter.saturate(2.0f) == 1.0f);
  REQUIRE(std::isnan(inter.saturate(std::numeric_limits<float>::quiet_NaN())));
  REQUIRE(inter.saturate(-std::numeric_limits<float>::infinity()) == -1.0f);
  REQUIRE(inter.saturate(std::numeric_limits<float>::infinity()) == 1.0f);
}

#include <array>
#include <atomic>
#include <exmath.hpp>
#include <iostream>
#include <ut_catch.hpp>

TEST_CASE()
{
  using T = exmath::statistics::max_min_mean_value_calculator_t;

  double values[10] = {
    0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
  };
  std::span<double> sp_1{ &values[0], 3 };
  std::span<double> sp_2{ &values[3], 3 };
  std::span<double> sp_3{ &values[6], 3 };


  T blk_1{};

  blk_1(values[0]);
  REQUIRE(blk_1.get_max() == Approx(0));
  REQUIRE(blk_1.get_min() == Approx(0));
  REQUIRE(blk_1.get_mean() == Approx(0));
  REQUIRE(std::isnan(blk_1.get_var()));

  blk_1(values[1]);
  REQUIRE(blk_1.get_max() == Approx(1));
  REQUIRE(blk_1.get_min() == Approx(0));
  REQUIRE(blk_1.get_mean() == Approx(0.5));
  REQUIRE(blk_1.get_var() == Approx(0.5));

  blk_1(values[2]);
  REQUIRE(blk_1.get_max() == Approx(2));
  REQUIRE(blk_1.get_min() == Approx(0));
  REQUIRE(blk_1.get_mean() == Approx(1));
  REQUIRE(blk_1.get_var() == Approx(1));

  blk_1(values[3]);
  REQUIRE(blk_1.get_max() == Approx(3));
  REQUIRE(blk_1.get_min() == Approx(0));
  REQUIRE(blk_1.get_mean() == Approx(1.5));
  REQUIRE(blk_1.get_var() == Approx(5.0 / 3.0));

  blk_1(values[4]);
  REQUIRE(blk_1.get_max() == Approx(4));
  REQUIRE(blk_1.get_min() == Approx(0));
  REQUIRE(blk_1.get_mean() == Approx(2));
  REQUIRE(blk_1.get_var() == Approx(2.5));

  T blk_2{};
  blk_2(std::span<double>{ &values[5], 5 });

  REQUIRE(blk_2.get_max() == Approx(9));
  REQUIRE(blk_2.get_min() == Approx(5));
  REQUIRE(blk_2.get_mean() == Approx(7));
  REQUIRE(blk_2.get_var() == Approx(2.5));

  blk_1(blk_2);
  REQUIRE(blk_1.get_max() == Approx(9));
  REQUIRE(blk_1.get_min() == Approx(0));
  REQUIRE(blk_1.get_mean() == Approx(4.5));
  REQUIRE(blk_1.get_var() == Approx(9.0+5.0/30.0));

  T blk_3{ sp_1 };
  REQUIRE(blk_3.get_max() == Approx(2));
  REQUIRE(blk_3.get_min() == Approx(0));
  REQUIRE(blk_3.get_mean() == Approx(1));
  REQUIRE(blk_3.get_var() == Approx(1));

  blk_1 + blk_2 blk_1(blk_2)

}

#include "testdata_max_min_mean_var_std.hpp"

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
  REQUIRE(std::isnan(blk_1.get_variance()));

  blk_1(values[1]);
  REQUIRE(blk_1.get_max() == Approx(1));
  REQUIRE(blk_1.get_min() == Approx(0));
  REQUIRE(blk_1.get_mean() == Approx(0.5));
  REQUIRE(blk_1.get_variance() == Approx(0.5));

  blk_1(values[2]);
  REQUIRE(blk_1.get_max() == Approx(2));
  REQUIRE(blk_1.get_min() == Approx(0));
  REQUIRE(blk_1.get_mean() == Approx(1));
  REQUIRE(blk_1.get_variance() == Approx(1));

  blk_1(values[3]);
  REQUIRE(blk_1.get_max() == Approx(3));
  REQUIRE(blk_1.get_min() == Approx(0));
  REQUIRE(blk_1.get_mean() == Approx(1.5));
  REQUIRE(blk_1.get_variance() == Approx(5.0 / 3.0));

  blk_1(values[4]);
  REQUIRE(blk_1.get_max() == Approx(4));
  REQUIRE(blk_1.get_min() == Approx(0));
  REQUIRE(blk_1.get_mean() == Approx(2));
  REQUIRE(blk_1.get_variance() == Approx(2.5));

  T blk_2{};
  blk_2(std::span<double>{ &values[5], 5 });

  REQUIRE(blk_2.get_max() == Approx(9));
  REQUIRE(blk_2.get_min() == Approx(5));
  REQUIRE(blk_2.get_mean() == Approx(7));
  REQUIRE(blk_2.get_variance() == Approx(2.5));

  blk_1(blk_2);
  REQUIRE(blk_1.get_max() == Approx(9));
  REQUIRE(blk_1.get_min() == Approx(0));
  REQUIRE(blk_1.get_mean() == Approx(4.5));
  REQUIRE(blk_1.get_variance() == Approx(9.0 + 5.0 / 30.0));

  T blk_3{ sp_1 };
  REQUIRE(blk_3.get_max() == Approx(2));
  REQUIRE(blk_3.get_min() == Approx(0));
  REQUIRE(blk_3.get_mean() == Approx(1));
  REQUIRE(blk_3.get_variance() == Approx(1));
}

TEST_CASE()
{
  using T = exmath::statistics::max_min_mean_value_calculator_t;

  double values[10] = {
    0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
  };
  std::span<double> sp_1{ &values[0], 3 };
  std::span<double> sp_2{ &values[3], 4 };
  std::span<double> sp_3{ &values[7], 3 };

  auto ftor = [&](std::size_t i) { return values[i]; };
  {
    T blk{};
    REQUIRE(blk.get_number_of_values() == 0);
    REQUIRE(!std::isfinite(blk.get_max()));
    REQUIRE(!std::isfinite(blk.get_min()));
    REQUIRE(std::isnan(blk.get_mean()));
    REQUIRE(std::isnan(blk.get_variance()));
    REQUIRE(std::isnan(blk.get_standard_deviation()));
  }
  {
    T blk{ values[0] };
    REQUIRE(blk.get_number_of_values() == 1);
    REQUIRE(blk.get_max() == Approx(0.0));
    REQUIRE(blk.get_min() == Approx(0.0));
    REQUIRE(blk.get_mean() == Approx(0.0));
    REQUIRE(std::isnan(blk.get_variance()));
    REQUIRE(std::isnan(blk.get_standard_deviation()));
  }
  {
    T blk{ sp_1 };
    REQUIRE(blk.get_number_of_values() == 3);
    REQUIRE(blk.get_max() == Approx(2.0));
    REQUIRE(blk.get_min() == Approx(0.0));
    REQUIRE(blk.get_mean() == Approx(1.0));
    REQUIRE(blk.get_variance() == Approx(1.0));
    REQUIRE(blk.get_standard_deviation() == Approx(1.0));
  }
  {
    T blk{ ftor, 3 };
    REQUIRE(blk.get_number_of_values() == 3);
    REQUIRE(blk.get_max() == Approx(2.0));
    REQUIRE(blk.get_min() == Approx(0.0));
    REQUIRE(blk.get_mean() == Approx(1.0));
    REQUIRE(blk.get_variance() == Approx(1.0));
    REQUIRE(blk.get_standard_deviation() == Approx(1.0));
  }
  {
    T blk{ values };
    REQUIRE(blk.get_number_of_values() == 10);
    REQUIRE(blk.get_max() == Approx(9.0));
    REQUIRE(blk.get_min() == Approx(0.0));
    REQUIRE(blk.get_mean() == Approx(4.5));
    REQUIRE(blk.get_variance() == Approx(9.0 + 5.0 / 30.0));
    REQUIRE(blk.get_standard_deviation() == Approx(std::sqrt(9.0 + 5.0 / 30.0)));
  }
}

TEST_CASE()
{
  using T = exmath::statistics::max_min_mean_value_calculator_t;

  double values[10] = {
    0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
  };
  std::span<double> sp_1{ &values[0], 3 };
  std::span<double> sp_2{ &values[3], 4 };
  std::span<double> sp_3{ &values[7], 3 };

  auto ftor = [&](std::size_t i) { return values[i]; };
  {
    T blk{};

    for (std::size_t i = 0; i < 3; i++)
      blk(values[i]);

    REQUIRE(blk.get_number_of_values() == 3);
    REQUIRE(blk.get_max() == Approx(2.0));
    REQUIRE(blk.get_min() == Approx(0.0));
    REQUIRE(blk.get_mean() == Approx(1.0));
    REQUIRE(blk.get_variance() == Approx(1.0));
    REQUIRE(blk.get_standard_deviation() == Approx(1.0));
  }
  {
    T blk{};

    blk(sp_1);
    REQUIRE(blk.get_number_of_values() == 3);
    REQUIRE(blk.get_max() == Approx(2.0));
    REQUIRE(blk.get_min() == Approx(0.0));
    REQUIRE(blk.get_mean() == Approx(1.0));
    REQUIRE(blk.get_variance() == Approx(1.0));
    REQUIRE(blk.get_standard_deviation() == Approx(1.0));
  }
  {
    T blk{};

    blk(ftor, 3);
    REQUIRE(blk.get_number_of_values() == 3);
    REQUIRE(blk.get_max() == Approx(2.0));
    REQUIRE(blk.get_min() == Approx(0.0));
    REQUIRE(blk.get_mean() == Approx(1.0));
    REQUIRE(blk.get_variance() == Approx(1.0));
    REQUIRE(blk.get_standard_deviation() == Approx(1.0));
  }
  {
    T blk;
    blk(sp_1);
    blk(sp_2);
    blk(sp_3);
    REQUIRE(blk.get_number_of_values() == 10);
    REQUIRE(blk.get_max() == Approx(9.0));
    REQUIRE(blk.get_min() == Approx(0.0));
    REQUIRE(blk.get_mean() == Approx(4.5));
    REQUIRE(blk.get_variance() == Approx(9.0 + 5.0 / 30.0));
    REQUIRE(blk.get_standard_deviation() == Approx(std::sqrt(9.0 + 5.0 / 30.0)));
  }
  {
    T       blk;
    T const blk_1(sp_1);
    T const blk_2(sp_2);
    T const blk_3(sp_3);

    blk(blk_1);
    blk(blk_2);
    blk(blk_3);
    REQUIRE(blk.get_number_of_values() == 10);
    REQUIRE(blk.get_max() == Approx(9.0));
    REQUIRE(blk.get_min() == Approx(0.0));
    REQUIRE(blk.get_mean() == Approx(4.5));
    REQUIRE(blk.get_variance() == Approx(9.0 + 5.0 / 30.0));
    REQUIRE(blk.get_standard_deviation() == Approx(std::sqrt(9.0 + 5.0 / 30.0)));
  }
  {
    T const blk_1(sp_1);
    T const blk_2(sp_2);
    T const blk_3(sp_3);

    T blk;
    blk += blk_1;
    blk += blk_2;
    blk += blk_3;
    REQUIRE(blk.get_number_of_values() == 10);
    REQUIRE(blk.get_max() == Approx(9.0));
    REQUIRE(blk.get_min() == Approx(0.0));
    REQUIRE(blk.get_mean() == Approx(4.5));
    REQUIRE(blk.get_variance() == Approx(9.0 + 5.0 / 30.0));
    REQUIRE(blk.get_standard_deviation() == Approx(std::sqrt(9.0 + 5.0 / 30.0)));
  }
  {
    T const blk_1(sp_1);
    T const blk_2(sp_2);
    T const blk_3(sp_3);

    T blk = blk_1 + blk_2 + blk_3;
    REQUIRE(blk.get_number_of_values() == 10);
    REQUIRE(blk.get_max() == Approx(9.0));
    REQUIRE(blk.get_min() == Approx(0.0));
    REQUIRE(blk.get_mean() == Approx(4.5));
    REQUIRE(blk.get_variance() == Approx(9.0 + 5.0 / 30.0));
    REQUIRE(blk.get_standard_deviation() == Approx(std::sqrt(9.0 + 5.0 / 30.0)));
  }
}

TEST_CASE()
{
  using T = exmath::statistics::max_min_mean_value_calculator_t;

  T sig_a{ test_data::signal_a::values };
  REQUIRE(sig_a.get_max() == Approx(test_data::signal_a::max));
  REQUIRE(sig_a.get_min() == Approx(test_data::signal_a::min));
  REQUIRE(sig_a.get_mean() == Approx(test_data::signal_a::mean));
  REQUIRE(sig_a.get_variance() == Approx(test_data::signal_a::var));
  REQUIRE(sig_a.get_standard_deviation() == Approx(test_data::signal_a::std));


  T sig_b;
  sig_b(test_data::signal_b::values);
  REQUIRE(sig_b.get_max() == Approx(test_data::signal_b::max));
  REQUIRE(sig_b.get_min() == Approx(test_data::signal_b::min));
  REQUIRE(sig_b.get_mean() == Approx(test_data::signal_b::mean));
  REQUIRE(sig_b.get_variance() == Approx(test_data::signal_b::var));
  REQUIRE(sig_b.get_standard_deviation() == Approx(test_data::signal_b::std));

  auto sig_full = sig_a + sig_b;
  REQUIRE(sig_full.get_max() == Approx(test_data::max));
  REQUIRE(sig_full.get_min() == Approx(test_data::min));
  REQUIRE(sig_full.get_mean() == Approx(test_data::mean));
  REQUIRE(sig_full.get_variance() == Approx(test_data::var));
  REQUIRE(sig_full.get_standard_deviation() == Approx(test_data::std));
}

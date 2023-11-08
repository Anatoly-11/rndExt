/* Модуль тестов для проверки работы модуля rnd с использованием модуля uuid(см описани и тесты к нему)
Проверяется создание и освобождение объекта генерации а так же выдача чисел в заданном диапазоне.
Для типов int, int8, uint64_t, float и double.
*/
//include test headers modules 
//#define MANUAL_RUN
#ifndef MANUAL_RUN
#include <gtest/gtest.h>
//#include <gmock/gmock.h>
//#else 
//#include <boost/io/quoted.hpp>
#endif
#include <iostream>
#include <string>
#include <RndExt.h>
#include <vector>
#include <algorithm>
#include <cstdint>
//---------------------------------------------------------------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------------------------------------------------------------
#ifndef MANUAL_RUN
//---------------------------------------------------------------------------------------------------------------------------------
template <typename T> 
bool isUnique(const T arr[], const size_t sz) {
  for(size_t i = 0; i < sz; ++i) {
    for(size_t j = 0; j < sz; ++j) {
      if(i == j) continue;
      if(arr[i] == arr[j]) return false;
      break;
    }
  }
  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestFillArrayUnique, tstInt8) { 
  int8_t vmin = -50, vmax = 110;
  constexpr size_t SIZE = 100;
  int8_t arr[SIZE];
  MyRand::FillArray(vmin, vmax, arr, SIZE, true);
  auto [v1, v2] = minmax_element(begin(arr), end(arr));
  ASSERT_TRUE(isUnique(arr, SIZE));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestFillArrayUnique, tstDbl) { 
  real64_t vmin = -50.0, vmax = 130.7;
  constexpr size_t SIZE = 100;
  real64_t arr[SIZE];
  MyRand::FillArray(vmin, vmax, arr, SIZE, true);
  auto [v1, v2] = minmax_element(begin(arr), end(arr));
  ASSERT_TRUE(isUnique(arr, SIZE));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestFillArrayRange, tstDbl) { 
  real64_t vmin = -50.0, vmax = 130.7;
  constexpr size_t SIZE = 100;
  real64_t arr[SIZE];
  MyRand::Rng r(vmin, vmax) ;
  ASSERT_TRUE(MyRand::FillArray(MyRand::EValType::Real64, r, SIZE, (void*)arr, true));
  auto [v1, v2] = minmax_element(begin(arr), end(arr));
  ASSERT_TRUE(isUnique(arr, SIZE));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateRange, tstInt) { 
  int vmin = 0, vmax = 100;
  auto rnd = MyRand::GetRnd(vmin, vmax);
  vector<int> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateRange, tstULL) { 
  uint64_t vmin = 0, vmax = 2300;
  auto rnd = MyRand::GetRnd(vmin, vmax);
  vector<uint64_t> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateRange, tstFlt) { 
  float vmin = -5.920f, vmax = 23.45f;
  auto rnd = MyRand::GetRnd(vmin, vmax);
  vector<float> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateRange, tstDbl) { 
  double vmin = -528.828, vmax = 2339.929;
  auto rnd = MyRand::GetRnd(vmin, vmax);
  vector<double> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
}
//---------------------------------------------------------------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  int res = 0;
  #ifdef MANUAL_RUN
  //some manual code
  #else
  testing::InitGoogleTest(&argc, argv);
  //testing::InitGoogleMock(&argc, argv);
  res = RUN_ALL_TESTS();
  #endif
  system("pause>nul");
  return res;
}
//---------------------------------------------------------------------------------------------------------------------------------
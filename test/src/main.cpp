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
#include <UUID.h>
#include <Rnd.h>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <tuple>
//---------------------------------------------------------------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------------------------------------------------------------
#ifndef MANUAL_RUN
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateReleaseRange, tstInt8) { 
  int8_t vmin = -50, vmax = 110;
  auto[rnd, uid] = MyRand::GetRnd(vmin, vmax);
  vector<int8_t> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
  ASSERT_TRUE(MyRand::ReleaseRnd(uid));
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateReleaseRange, tstInt) { 
  int vmin = 0, vmax = 100;
  auto[rnd, uid] = MyRand::GetRnd(vmin, vmax);
  vector<int> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
  ASSERT_TRUE(MyRand::ReleaseRnd(uid));
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateReleaseRange, tstULL) { 
  uint64_t vmin = 0, vmax = 2300;
  auto[rnd, uid] = MyRand::GetRnd(vmin, vmax);
  vector<uint64_t> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
  ASSERT_TRUE(MyRand::ReleaseRnd(uid));
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateReleaseRange, tstFlt) { 
  float vmin = -5.920f, vmax = 23.45f;
  auto[rnd, uid] = MyRand::GetRnd(vmin, vmax);
  vector<float> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
  ASSERT_TRUE(MyRand::ReleaseRnd(uid));
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestCreateReleaseRange, tstDbl) { 
  double vmin = -528.828, vmax = 2339.929;
  auto[rnd, uid] = MyRand::GetRnd(vmin, vmax);
  vector<double> vv;
  vv.reserve(100);
  for(size_t i = 0; i < 100; i++) {
    vv.push_back(rnd->get());
  }
  auto [v1, v2] = minmax_element(begin(vv), end(vv));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
  ASSERT_TRUE(MyRand::ReleaseRnd(uid));
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
// Модуль тестов для проверки работы модуля rndExt
//include test headers modules 
#include <pch.h>
#include <RndExt.h>
//---------------------------------------------------------------------------------------------------------------------------------
using namespace std;
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
template <typename It> 
bool isUnique(const It &beg, const It &end) {
  for(auto iti = beg; iti != end; ++iti) {
    for(auto itj = beg; itj != end; ++itj) {
      if(iti == itj) continue;
      if(*iti == *itj) return false;
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
  ASSERT_TRUE(MyRand::FillArray({vmin, vmax}, SIZE, arr, true));
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
TEST(TestFillVectorUnique, tstInt8) { 
  int8_t vmin = -50, vmax = 110;
  constexpr size_t SIZE = 100;
  auto r = MyRand::FillVector(vmin, vmax, SIZE, true);
  ASSERT_TRUE(r); // Заполнилось!!!
  auto v = r.value();
  auto [v1, v2] = minmax_element(begin(v), end(v));
  ASSERT_TRUE(isUnique(begin(v), end(v)));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestFillVectorUnique, tstInt32) { 
  int32_t vmin = -50, vmax = 200;
  constexpr size_t SIZE = 100;
  auto r = MyRand::FillVector(vmin, vmax, SIZE, true);
  ASSERT_TRUE(r); // Заполнилось!!!
  auto v = r.value();
  auto [v1, v2] = minmax_element(begin(v), end(v));
  ASSERT_TRUE(isUnique(begin(v), end(v)));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestFillVectorUnique, tstFlt) {
  real32_t vmin = -50, vmax = 200;
  constexpr size_t SIZE = 100;
  auto r = MyRand::FillVector(vmin, vmax, SIZE, true);
  ASSERT_TRUE(r); // Заполнилось!!!
  auto v = r.value();
  auto [v1, v2] = minmax_element(begin(v), end(v));
  ASSERT_TRUE(isUnique(begin(v), end(v)));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestFillVectorUnique, tstDbl) {
  real64_t vmin = -50.849, vmax = 200.449;
  constexpr size_t SIZE = 100;
  auto r = MyRand::FillVector(vmin, vmax, SIZE, true);
  ASSERT_TRUE(r); // Заполнилось!!!
  auto v = r.value();
  auto [v1, v2] = minmax_element(begin(v), end(v));
  ASSERT_TRUE(isUnique(begin(v), end(v)));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
}
//---------------------------------------------------------------------------------------------------------------------------------
TEST(TestFillStringUnique, tstStr) {
  char vmin = ' ', vmax = 'f';
  constexpr size_t SIZE = 30;
  auto r = MyRand::FillStr(vmin, vmax, SIZE, true);
  ASSERT_TRUE(r); // Заполнилось!!!
  auto v = r.value();
  auto [v1, v2] = minmax_element(begin(v), end(v));
  ASSERT_TRUE(isUnique(begin(v), end(v)));
  ASSERT_LE(vmin, *v1);
  ASSERT_GE(vmax, *v2);
  //sort(begin(v), end(v));
  //cout << v << endl;
}
//---------------------------------------------------------------------------------------------------------------------------------
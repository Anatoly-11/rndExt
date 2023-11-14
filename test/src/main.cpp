// Модуль тестов для проверки работы модуля rndExt
#include "pch.h"
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
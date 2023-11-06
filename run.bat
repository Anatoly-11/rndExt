@echo off
copy headers\rnd.h     ..\matrix\headers
copy x64\Debug\rnd.lib ..\matrix\lib
copy x64\Debug\rnd.dll ..\matrix\x64\Debug

copy headers\rnd.h     test\headers
copy x64\Debug\rnd.lib test\lib
copy x64\Debug\rnd.dll test\x64\Debug

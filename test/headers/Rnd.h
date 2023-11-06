#pragma once
#ifndef _RND_H_
#define _RND_H_ 1.0
//---------------------------------------------------------------------------------------------------------------------------------
/* 
Определяет ряд объектов для основных типов чисел целых и с плавающей точкой. Объекты генерят случайные числа в равномерном
распределении в заданом диапазоне или по умолчанию. Для целых это от 0 до 100 независимо от типа а для чисел с плавающей точкой
от 0 до 1 включительно. Периодически происходит ресид геренратора чисел. Кроме того для каждого объекта создаётся свой
UUID(см описание этого модуля). Этот функционал подключается через динеамическую библиотеку. Все функции многопоточны
которую можно отключить при необходимости или посмотреть с помощью функций SetMultithread и getMultithread соответсвенно.
Типы (u)int128 и float128 а так же long double не поддерживаются так как их не поддерживает компилятор msbuild.
Attention! После использования обязательно вызывать функцию очистки ReleaseRnd. Это предотвратит утечку памяти.
*/
//---------------------------------------------------------------------------------------------------------------------------------
#include <cstdint>
#include <string>
#include <tuple>
#include <UUID.h>
#ifndef RND_EXPORT
#define RND_DLL_API __declspec(dllimport)
#else
#define RND_DLL_API __declspec(dllexport)
#endif
using real32_t = float;
using real64_t = double;
using real80_t = long double;
//using real128_t = float128;
//---------------------------------------------------------------------------------------------------------------------------------
namespace MyRand{
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndInt8 { 
  public:
    virtual int8_t get() noexcept = 0;
    virtual int8_t get(const int8_t min, const int8_t max) noexcept = 0 ;
    virtual int8_t getRep(const int8_t min, const int8_t max) noexcept = 0 ;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndUint8 { 
  public:
    virtual uint8_t get() noexcept = 0;
    virtual uint8_t get(const uint8_t min, const uint8_t max) noexcept = 0 ;
    virtual uint8_t getRep(const uint8_t min, const uint8_t max) noexcept = 0 ;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndInt16 { 
  public:
    virtual int16_t get() noexcept = 0;
    virtual int16_t get(const int16_t min, const int16_t max) noexcept = 0 ;
    virtual int16_t getRep(const int16_t min, const int16_t max) noexcept = 0 ;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndUint16 { 
  public:
    virtual uint16_t get() noexcept = 0;
    virtual uint16_t get(const uint16_t min, const uint16_t max) noexcept = 0 ;
    virtual uint16_t getRep(const uint16_t min, const uint16_t max) noexcept = 0 ;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndInt { 
  public:
    virtual int32_t get() noexcept = 0;
    virtual int32_t get(const int32_t min, const int32_t max) noexcept = 0 ;
    virtual int32_t getRep(const int32_t min, const int32_t max) noexcept = 0 ;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndUint{ 
  public:
    virtual uint32_t get() noexcept = 0;
    virtual uint32_t get(const uint32_t min, const uint32_t max) noexcept = 0;
    virtual uint32_t getRep(const uint32_t min, const uint32_t max) noexcept = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndLong { 
  public:
    virtual int64_t get() noexcept = 0;
    virtual int64_t get(const int64_t min, const int64_t max) noexcept = 0;
    virtual int64_t getRep(const int64_t min, const int64_t max) noexcept = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndUlong { 
  public:
    virtual uint64_t get() noexcept = 0;
    virtual uint64_t get(const uint64_t min, const uint64_t max) noexcept = 0;
    virtual uint64_t getRep(const uint64_t min, const uint64_t max) noexcept = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndFlt { 
  public:
    virtual real32_t get() noexcept = 0;
    virtual real32_t get(const real32_t min, const real32_t max) noexcept = 0;
    virtual real32_t getRep(const real32_t min, const real32_t max) noexcept = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndDbl { 
  public:
    virtual real64_t get() noexcept = 0;
    virtual real64_t get(const real64_t min, const real64_t max) noexcept = 0;
    virtual real64_t getRep(const real64_t min, const real64_t max) noexcept = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  enum class EValType : uint8_t { Int8, Uint8, Int16, Uint16, Int, Uint, Long, Ulong, Flt, Dbl };
  //---------------------------------------------------------------------------------------------------------------------------------
  template<typename T>
  T *convertTo(void *ptr) {
    return reinterpret_cast<T*>(ptr);
  }
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API void SetMultithread(const bool _Is) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool getMultithread() noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API std::tuple<void*, MyUuid::UUID> GetRnd(const EValType tp) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API std::tuple<IRndInt8*, MyUuid::UUID> GetRnd(const int8_t min, const int8_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API std::tuple<IRndUint8*, MyUuid::UUID> GetRnd(const uint8_t min, const uint8_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API std::tuple<IRndInt16*, MyUuid::UUID> GetRnd(const int16_t min, const int16_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API std::tuple<IRndUint16*, MyUuid::UUID> GetRnd(const uint16_t min, const uint16_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API std::tuple<IRndInt*, MyUuid::UUID> GetRnd(const int32_t min, const int32_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API std::tuple<IRndUint*, MyUuid::UUID> GetRnd(const uint32_t min, const uint32_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API std::tuple<IRndLong*, MyUuid::UUID> GetRnd(const int64_t min, const int64_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API std::tuple<IRndUlong*, MyUuid::UUID> GetRnd(const uint64_t min, const uint64_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API std::tuple<IRndFlt*, MyUuid::UUID> GetRnd(const  real32_t min, const real32_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API std::tuple<IRndDbl*, MyUuid::UUID> GetRnd(const real64_t  min, const real64_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool ReleaseRnd(const MyUuid::UUID &_gid) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
} // !namespace MyRand
#endif // !_RND_H_
//---------------------------------------------------------------------------------------------------------------------------------
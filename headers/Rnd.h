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
#include <variant>
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
    virtual ~IRndInt8() = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndUint8 { 
  public:
    virtual uint8_t get() noexcept = 0;
    virtual uint8_t get(const uint8_t min, const uint8_t max) noexcept = 0 ;
    virtual uint8_t getRep(const uint8_t min, const uint8_t max) noexcept = 0 ;
    virtual ~IRndUint8() = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndInt16 { 
  public:
    virtual int16_t get() noexcept = 0;
    virtual int16_t get(const int16_t min, const int16_t max) noexcept = 0 ;
    virtual int16_t getRep(const int16_t min, const int16_t max) noexcept = 0 ;
    virtual ~IRndInt16() = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndUint16 { 
  public:
    virtual uint16_t get() noexcept = 0;
    virtual uint16_t get(const uint16_t min, const uint16_t max) noexcept = 0 ;
    virtual uint16_t getRep(const uint16_t min, const uint16_t max) noexcept = 0 ;
    virtual ~IRndUint16() = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndInt32 { 
  public:
    virtual int32_t get() noexcept = 0;
    virtual int32_t get(const int32_t min, const int32_t max) noexcept = 0 ;
    virtual int32_t getRep(const int32_t min, const int32_t max) noexcept = 0 ;
    virtual ~IRndInt32() = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndUint32{ 
  public:
    virtual uint32_t get() noexcept = 0;
    virtual uint32_t get(const uint32_t min, const uint32_t max) noexcept = 0;
    virtual uint32_t getRep(const uint32_t min, const uint32_t max) noexcept = 0;
    virtual ~IRndUint32() = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndInt64 { 
  public:
    virtual int64_t get() noexcept = 0;
    virtual int64_t get(const int64_t min, const int64_t max) noexcept = 0;
    virtual int64_t getRep(const int64_t min, const int64_t max) noexcept = 0;
    virtual ~IRndInt64() = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndUint64 { 
  public:
    virtual uint64_t get() noexcept = 0;
    virtual uint64_t get(const uint64_t min, const uint64_t max) noexcept = 0;
    virtual uint64_t getRep(const uint64_t min, const uint64_t max) noexcept = 0;
    virtual ~IRndUint64() = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndReal32 { 
  public:
    virtual real32_t get() noexcept = 0;
    virtual real32_t get(const real32_t min, const real32_t max) noexcept = 0;
    virtual real32_t getRep(const real32_t min, const real32_t max) noexcept = 0;
    virtual ~IRndReal32() = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  class IRndReal64 { 
  public:
    virtual real64_t get() noexcept = 0;
    virtual real64_t get(const real64_t min, const real64_t max) noexcept = 0;
    virtual real64_t getRep(const real64_t min, const real64_t max) noexcept = 0;
    virtual ~IRndReal64() = 0;
  };
  //-------------------------------------------------------------------------------------------------------------------------------
  enum class EValType : uint8_t { Int8, Uint8, Int16, Uint16, Int32, Uint32, Int64, Uint64, Real32, Real64 };
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
  RND_DLL_API void *GetRnd(const EValType tp) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndInt8 *GetRnd(const int8_t min, const int8_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndUint8 *GetRnd(const uint8_t min, const uint8_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndInt16 *GetRnd(const int16_t min, const int16_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndUint16 *GetRnd(const uint16_t min, const uint16_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndInt32 *GetRnd(const int32_t min, const int32_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndUint32 *GetRnd(const uint32_t min, const uint32_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndInt64 *GetRnd(const int64_t min, const int64_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndUint64 *GetRnd(const uint64_t min, const uint64_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndReal32 *GetRnd(const  real32_t min, const real32_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API IRndReal64 *GetRnd(const real64_t  min, const real64_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool FillArray(const int8_t  min, const int8_t max, int8_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool FillArray(const uint8_t  min, const uint8_t max, uint8_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool FillArray(const int16_t  min, const int16_t max, int16_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool FillArray(const uint16_t  min, const uint16_t max, uint16_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool FillArray(const int32_t  min, const int32_t max, int32_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool FillArray(const uint32_t  min, const uint32_t max, uint32_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool FillArray(const int64_t  min, const int64_t max, int64_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool FillArray(const uint64_t  min, const uint64_t max, uint64_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool FillArray(const real32_t  min, const real32_t max, real32_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RND_DLL_API bool FillArray(const real64_t  min, const real64_t max, real64_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
} // !namespace MyRand
#endif // !_RND_H_
//---------------------------------------------------------------------------------------------------------------------------------
#pragma once
#ifndef _RNDEXT_H_
#define _RNDEXT_H_ 1.0
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
#include <vector>
#include <variant>
#include <optional>
#ifdef RNDEXT_EXPORT
#define RNDEXT_DLL __declspec(dllexport)
#else
#define RNDEXT_DLL __declspec(dllimport)
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
  RNDEXT_DLL void SetMultithread(const bool _Is) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL bool getMultithread() noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL void *GetRnd(const EValType tp) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL IRndInt8 *GetRnd(const int8_t min, const int8_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL IRndUint8 *GetRnd(const uint8_t min, const uint8_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL IRndInt16 *GetRnd(const int16_t min, const int16_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL IRndUint16 *GetRnd(const uint16_t min, const uint16_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL IRndInt32 *GetRnd(const int32_t min, const int32_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL IRndUint32 *GetRnd(const uint32_t min, const uint32_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL IRndInt64 *GetRnd(const int64_t min, const int64_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL IRndUint64 *GetRnd(const uint64_t min, const uint64_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL IRndReal32 *GetRnd(const  real32_t min, const real32_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL IRndReal64 *GetRnd(const real64_t  min, const real64_t max) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL bool FillArray(const int8_t  min, const int8_t max, int8_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL bool FillArray(const uint8_t  min, const uint8_t max, uint8_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL bool FillArray(const int16_t  min, const int16_t max, int16_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL bool FillArray(const uint16_t  min, const uint16_t max, uint16_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL bool FillArray(const int32_t  min, const int32_t max, int32_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL bool FillArray(const uint32_t  min, const uint32_t max, uint32_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL bool FillArray(const int64_t  min, const int64_t max, int64_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL bool FillArray(const uint64_t  min, const uint64_t max, uint64_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL bool FillArray(const real32_t  min, const real32_t max, real32_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL bool FillArray(const real64_t  min, const real64_t max, real64_t *arr, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  using VarDat = std::variant<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, real32_t, real64_t>;
  //-------------------------------------------------------------------------------------------------------------------------------
  struct Rng { VarDat min, max; };
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL bool FillArray(const Rng &r, const size_t _n, void *arr, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL std::optional<std::vector<int8_t>> FillVector(const int8_t  min, const int8_t max, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL std::optional<std::vector<uint8_t>> FillVector(const uint8_t  min, const uint8_t max, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL std::optional<std::vector<int16_t>> FillVector(const int16_t  min, const int16_t max, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL std::optional<std::vector<uint16_t>> FillVector(const uint16_t  min, const uint16_t max, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL std::optional<std::vector<int32_t>> FillVector(const int32_t  min, const int32_t max, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL std::optional<std::vector<uint32_t>> FillVector(const uint32_t  min, const uint32_t max, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL std::optional<std::vector<int64_t>> FillVector(const int64_t  min, const int64_t max, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL std::optional<std::vector<uint64_t>> FillVector(const uint64_t  min, const uint64_t max, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL std::optional<std::vector<real32_t>> FillVector(const real32_t min, const real32_t max, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL std::optional<std::vector<real64_t>> FillVector(const real64_t  min, const real64_t max, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
  RNDEXT_DLL std::optional<std::string> FillStr(const char min, const char max, const size_t _n, bool isUnique) noexcept;
  //-------------------------------------------------------------------------------------------------------------------------------
} // !namespace MyRand
#endif // !_RNDEXT_H_
//---------------------------------------------------------------------------------------------------------------------------------
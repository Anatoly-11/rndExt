#include <RndExt.h>
#include <random>
#include <map>
#include <chrono>
#include <type_traits>
//---------------------------------------------------------------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------------------------------------------------------------
mutex mtx;
//-------------------------------------------------------------------------------------------------------------------------------
static bool isMultiThread = true;
//-------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL void MyRand::SetMultithread(const bool _Is) noexcept {
  isMultiThread = _Is;
}
//-------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL bool MyRand::getMultithread() noexcept {
  return isMultiThread;
}
//---------------------------------------------------------------------------------------------------------------------------------
template <typename T> requires is_integral_v<T>
class RndIntImpl {
  RndIntImpl(const RndIntImpl &) = delete;
  RndIntImpl(RndIntImpl &&) = delete;
  RndIntImpl &operator=(const RndIntImpl &) = delete;
  RndIntImpl &&operator=(RndIntImpl &&) = delete;
private:
  mt19937_64 engine;
  uniform_int_distribution<T> distr;
  int count;

  void inc() {
    if(isMultiThread) {
      lock_guard<mutex> grd(mtx);
    }
    count++;
    if(count > 32) {
      count %= 32;
      engine.seed(chrono::system_clock::now().time_since_epoch().count() / 100ull);
    }
  }

protected:

  RndIntImpl(): engine{mt19937_64{random_device{}()}}, distr{1, 100}, count{0} {}
  RndIntImpl(const T _min, const T _max): engine{mt19937_64{random_device{}()}}, distr{_min, _max}, count{0} {}

  T get() noexcept {
    return distr(engine);
  }

  T get(const T _min, const T _max) noexcept {
    inc();
    uniform_int_distribution<T> dd{_min, _max};
    return dd(engine);
  }

  T getRep(const T _min, const T _max) noexcept {
    if(isMultiThread) {
      unique_lock<mutex> grd(mtx);
      count = 0;
      distr = uniform_int_distribution<T>(_min, _max);
      grd.unlock();
    } else {
      count = 0;
      distr = uniform_int_distribution<T>(_min, _max);
    }
    return distr(engine);
  }

  ~RndIntImpl(){
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
template <typename T> requires is_floating_point_v<T>
class RndRealImpl {
  RndRealImpl(const RndRealImpl &) = delete;
  RndRealImpl(RndRealImpl &&) = delete;
  RndRealImpl &operator=(const RndRealImpl &) = delete;
  RndRealImpl &&operator=(RndRealImpl &&) = delete;
private:
  mt19937_64 engine;
  uniform_real_distribution<T> distr;
  int count;
  
  void inc() {
    if(isMultiThread) {
      lock_guard<mutex> grd(mtx);
    }
    count++;
    if(count > 32) {
      count %= 32;
      engine.seed(chrono::system_clock::now().time_since_epoch().count() / 100ull);
    }
  }

protected:
  RndRealImpl(): engine{mt19937_64{random_device{}()}}, distr{0.0, 1.0}, count{0} {}

  RndRealImpl(const T _min, const T _max): engine{mt19937_64{random_device{}()}}, distr{_min, _max}, count{0} {}

  T get() noexcept {
    inc();
    return distr(engine);
  }

  T get(const T _min, const T _max) noexcept {
    inc();
    uniform_real_distribution<T> dd{_min, _max};
    return dd(engine);
  }

  T getRep(const T _min, const T _max) noexcept {
    if(isMultiThread) {
      unique_lock<mutex> grd(mtx);
      count = 0;
      distr = uniform_real_distribution<T>(_min, _max);
      grd.unlock();
    } else {
      count = 0;
      distr = uniform_real_distribution<T>(_min, _max);
    }
    return distr(engine);
  }

  ~RndRealImpl(){
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class IRnd {
public:
  virtual void fill(void *) noexcept = 0;
  virtual ~IRnd() = 0;
};
//---------------------------------------------------------------------------------------------------------------------------------
IRnd :: ~IRnd() {};
//---------------------------------------------------------------------------------------------------------------------------------
namespace MyRand {
  IRndInt8 :: ~IRndInt8() {};
  
  IRndUint8 :: ~IRndUint8() {};
  
  IRndInt16 :: ~IRndInt16() {};
  
  IRndUint16 :: ~IRndUint16() {};
  
  IRndInt32 :: ~IRndInt32() {};
  
  IRndUint32 :: ~IRndUint32() {};
  
  IRndInt64 :: ~IRndInt64() {};
  
  IRndUint64 :: ~IRndUint64() {};
  
  IRndReal32 :: ~IRndReal32() {};
  
  IRndReal64 :: ~IRndReal64() {};
}
//---------------------------------------------------------------------------------------------------------------------------------
class RndInt8 : public MyRand :: IRndInt8, public RndIntImpl<int16_t>, public IRnd {
public:
  RndInt8() : RndIntImpl<int16_t>() {}

  RndInt8(const int8_t min, const int8_t max) : RndIntImpl<int16_t>(min, max) {}

  virtual int8_t get() noexcept  override {
    return static_cast<int8_t>(RndIntImpl<int16_t>::get());
  }

  virtual int8_t get(const int8_t min, const int8_t max) noexcept  override {
    return static_cast<int8_t>(RndIntImpl<int16_t>::get(min, max));
  }

  virtual int8_t getRep(const int8_t min, const int8_t max) noexcept  override {
    return static_cast<int8_t>(RndIntImpl<int16_t>::getRep(min, max));
  }

  virtual void fill(void *v) noexcept  override {
    *reinterpret_cast<int8_t*>(v) = static_cast<int8_t>(RndIntImpl<int16_t>::get());
  }

  virtual ~RndInt8() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndUint8 : public MyRand ::IRndUint8, public RndIntImpl<uint16_t>, public IRnd {
public:
  RndUint8() : RndIntImpl<uint16_t>() {}

  RndUint8(const uint8_t min, const uint8_t max) : RndIntImpl<uint16_t>(min, max) {}

  virtual uint8_t get() noexcept  override {
    return static_cast<uint8_t>(RndIntImpl<uint16_t>::get());
  }

  virtual uint8_t get(const uint8_t min, const uint8_t max) noexcept  override {
    return static_cast<uint8_t>(RndIntImpl<uint16_t>::get(min, max));
  }

  virtual uint8_t getRep(const uint8_t min, const uint8_t max) noexcept  override {
    return static_cast<uint8_t>(RndIntImpl<uint16_t>::getRep(min, max));
  }

  virtual void fill(void *v) noexcept  override {
    *reinterpret_cast<uint8_t*>(v) = static_cast<uint8_t>(RndIntImpl<uint16_t>::get());
  }

  virtual ~RndUint8() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndInt16 : public MyRand :: IRndInt16, public RndIntImpl<int16_t>, public IRnd {
public:
  RndInt16() : RndIntImpl<int16_t>() {}

  RndInt16(const int16_t min, const int16_t max) : RndIntImpl<int16_t>(min, max) {}

  virtual int16_t get() noexcept  override {
    return RndIntImpl<int16_t>::get();
  }

  virtual int16_t get(const int16_t min, const int16_t max) noexcept  override {
    return RndIntImpl<int16_t>::get(min, max);
  }

  virtual int16_t getRep(const int16_t min, const int16_t max) noexcept  override {
    return RndIntImpl<int16_t>::getRep(min, max);
  }

  virtual void fill(void *v) noexcept  override {
    *reinterpret_cast<int16_t*>(v) = RndIntImpl<int16_t>::get();
  }

  virtual ~RndInt16() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndUint16 : public MyRand::IRndUint16, public RndIntImpl<uint16_t>, public IRnd {
public:
  RndUint16() : RndIntImpl<uint16_t>() {}

  RndUint16(const uint16_t min, const uint16_t max) : RndIntImpl<uint16_t>(min, max) {}

  virtual uint16_t get() noexcept  override {
    return RndIntImpl<uint16_t>::get();
  }

  virtual uint16_t get(const uint16_t min, const uint16_t max) noexcept  override {
    return RndIntImpl<uint16_t>::get(min, max);
  }

  virtual uint16_t getRep(const uint16_t min, const uint16_t max) noexcept  override {
    return RndIntImpl<uint16_t>::getRep(min, max);
  }

  virtual void fill(void *v) noexcept  override {
    *reinterpret_cast<uint16_t*>(v) = RndIntImpl<uint16_t>::get();
  }

  virtual ~RndUint16() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndInt32 : public MyRand :: IRndInt32, public RndIntImpl<int32_t>, public IRnd {
public:
  RndInt32() : RndIntImpl<int32_t>() {}

  RndInt32(const int32_t min, const int32_t max) : RndIntImpl<int32_t>(min, max) {}

  virtual int32_t get() noexcept  override {
    return RndIntImpl<int32_t>::get();
  }

  virtual int32_t get(const int32_t min, const int32_t max) noexcept  override {
    return RndIntImpl<int32_t>::get(min, max);
  }

  virtual int32_t getRep(const int32_t min, const int32_t max) noexcept  override {
    return RndIntImpl<int32_t>::getRep(min, max);
  }

  virtual void fill(void *v) noexcept  override {
    *reinterpret_cast<int32_t*>(v) = RndIntImpl<int32_t>::get();
  }

  virtual ~RndInt32() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndUint32 : public MyRand :: IRndUint32, public RndIntImpl<uint32_t>, public IRnd {
public:
  RndUint32() : RndIntImpl<uint32_t>() {}

  RndUint32(const uint32_t min, const uint32_t max) : RndIntImpl<uint32_t>(min, max) {}

  virtual uint32_t get() noexcept  override {
    return RndIntImpl<uint32_t>::get();
  }

  virtual uint32_t get(const uint32_t min, const uint32_t max) noexcept  override {
    return RndIntImpl<uint32_t>::get(min, max);
  }

  virtual uint32_t getRep(const uint32_t min, const uint32_t max) noexcept  override {
    return RndIntImpl<uint32_t>::getRep(min, max);
  }

  virtual void fill(void *v) noexcept  override {
    *reinterpret_cast<uint32_t*>(v) = RndIntImpl<uint32_t>::get();
  }

  virtual ~RndUint32() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndInt64 : public MyRand :: IRndInt64, public RndIntImpl<int64_t>, public IRnd {
public:
  RndInt64() : RndIntImpl<int64_t>() {}

  RndInt64(const int64_t min, const int64_t max) : RndIntImpl<int64_t>(min, max) {}

  virtual int64_t get() noexcept  override {
    return RndIntImpl<int64_t>::get();
  }

  virtual int64_t get(const int64_t min, const int64_t max) noexcept  override {
    return RndIntImpl<int64_t>::get(min, max);
  }

  virtual int64_t getRep(const int64_t min, const int64_t max) noexcept  override {
    return RndIntImpl<int64_t>::getRep(min, max);
  }

  virtual void fill(void *v) noexcept  override {
    *reinterpret_cast<int64_t*>(v) = RndIntImpl<int64_t>::get();
  }

  virtual ~RndInt64() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndUint64 : public MyRand :: IRndUint64, public RndIntImpl<uint64_t>, public IRnd {
public:
  RndUint64() : RndIntImpl<uint64_t>() {}

  RndUint64(const uint64_t min, const uint64_t max) : RndIntImpl<uint64_t>(min, max) {}

  virtual uint64_t get() noexcept  override {
    return RndIntImpl<uint64_t>::get();
  }

  virtual uint64_t get(const uint64_t min, const uint64_t max) noexcept  override {
    return RndIntImpl<uint64_t>::get(min, max);
  }

  virtual uint64_t getRep(const uint64_t min, const uint64_t max) noexcept  override {
    return RndIntImpl<uint64_t>::getRep(min, max);
  }

  virtual void fill(void *v) noexcept  override {
    *reinterpret_cast<uint64_t*>(v) = RndIntImpl<uint64_t>::get();
  }

  virtual ~RndUint64() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndReal32 : public MyRand :: IRndReal32, public  RndRealImpl<real32_t>, public IRnd {
public:
  RndReal32() : RndRealImpl<real32_t>() {}

  RndReal32(const real32_t min, const real32_t max) : RndRealImpl<real32_t>(min, max) {}

  virtual real32_t get() noexcept  override {
    return RndRealImpl<real32_t>::get();
  }

  virtual real32_t get(const real32_t min, const real32_t max) noexcept  override {
    return RndRealImpl<real32_t>::get(min, max);
  }

  virtual real32_t getRep(const real32_t min, const real32_t max) noexcept  override {
    return RndRealImpl<real32_t>::getRep(min, max);
  }

  virtual void fill(void *v) noexcept  override {
    *reinterpret_cast<real32_t*>(v) = RndRealImpl<real32_t>::get();
  }

  virtual ~RndReal32() {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndReal64 : public MyRand :: IRndReal64, public  RndRealImpl<real64_t>, public IRnd {
public:
  RndReal64() : RndRealImpl<real64_t>() {}
  RndReal64(const real64_t min, const real64_t max) : RndRealImpl<real64_t>(min, max) {}

  virtual real64_t get() noexcept  override {
    return RndRealImpl<real64_t>::get();
  }

  virtual real64_t get(const real64_t min, const real64_t max) noexcept  override {
    return RndRealImpl<real64_t>::get(min, max);
  }

  virtual real64_t getRep(const real64_t min, const real64_t max) noexcept  override {
    return RndRealImpl<real64_t>::getRep(min, max);
  }

  virtual void fill(void *v) noexcept  override {
    *reinterpret_cast<real64_t*>(v) = RndRealImpl<real64_t>::get();
  }

  virtual ~RndReal64() {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL void* MyRand::GetRnd(const EValType tp) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  if(isMultiThread) {
    grd.lock();
  }
  void *rnd = (tp == MyRand::EValType::Int8) ? (void*)(new RndInt8) :
    (tp == MyRand::EValType::Uint8)  ? (void*)(new RndUint8)  :
    (tp == MyRand::EValType::Int16)  ? (void*)(new RndUint16) :
    (tp == MyRand::EValType::Uint16) ? (void*)(new RndUint16) :
    (tp == MyRand::EValType::Int32)  ? (void*)(new RndInt32)  :
    (tp == MyRand::EValType::Uint32) ? (void*)(new RndUint32) :
    (tp == MyRand::EValType::Int64)  ? (void*)(new RndInt64)  :
    (tp == MyRand::EValType::Uint64) ? (void*)(new RndUint64) :
    (tp == MyRand::EValType::Real32) ? (void*)(new RndReal32) :
    (tp == MyRand::EValType::Real64) ? (void*)(new RndReal64) :
    nullptr;
  if(isMultiThread) {
    grd.unlock();
  }
  return rnd;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL MyRand::IRndInt8 *MyRand::GetRnd(const int8_t min, const int8_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndInt8 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndInt8(min, max);
    grd.unlock();
  } else 
    rnd = new RndInt8(min, max);
  return rnd;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL MyRand::IRndUint8 *MyRand::GetRnd(const uint8_t min, const uint8_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndUint8 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndUint8(min, max);
    grd.unlock();
  } else
    rnd = new RndUint8(min, max);
  return rnd;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL MyRand::IRndInt16 *MyRand::GetRnd(const int16_t min, const int16_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndInt16 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndInt16(min, max);
    grd.unlock();
  } else
    rnd = new RndInt16(min, max);
  return rnd;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL  MyRand::IRndUint16 *MyRand::GetRnd(const uint16_t min, const uint16_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndUint16 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndUint16(min, max);
    grd.unlock();
  } else 
    rnd = new RndUint16(min, max);
  return rnd;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL MyRand::IRndInt32 *MyRand::GetRnd(const int32_t min, const int32_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndInt32 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndInt32(min, max);
    grd.unlock();
  } else 
    rnd = new RndInt32(min, max);
  return rnd;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL MyRand::IRndUint32 *MyRand::GetRnd(const uint32_t min, const uint32_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndUint32 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndUint32(min, max);
    grd.unlock();
  } else 
    rnd = new RndUint32(min, max);
  return rnd;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL MyRand::IRndInt64 *MyRand::GetRnd(const int64_t min, const int64_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  IRndInt64 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndInt64(min, max);
    grd.unlock();
  } else 
    rnd = new RndInt64(min, max);
  return rnd;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL MyRand::IRndUint64 *MyRand::GetRnd(const uint64_t min, const uint64_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndUint64 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndUint64(min, max);
    grd.unlock();
  } else
    rnd = new RndUint64(min, max);
  return rnd;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL MyRand::IRndReal32 *MyRand::GetRnd(const real32_t min, const real32_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndReal32 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndReal32(min, max);
    grd.unlock();
  } else
    rnd = new RndReal32(min, max);
  return rnd;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL MyRand::IRndReal64 *MyRand::GetRnd(const real64_t min, const real64_t max) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  RndReal64 *rnd = nullptr;
  if(isMultiThread) {
    grd.lock();
    rnd = new RndReal64(min, max);
    grd.unlock();
  } else
    rnd = new RndReal64(min, max);
  return rnd;
}
//---------------------------------------------------------------------------------------------------------------------------------
template <typename T>
void FillArrayImpl(MyRand::EValType tp, const T  min, const T max, T *arr, const size_t _n, bool isUnique) noexcept {
  IRnd *rnd = ((tp == MyRand::EValType::Int8) ? (IRnd*)(new RndInt8(min, max)) :
    (tp == MyRand::EValType::Uint8)  ? (IRnd*)(new RndUint8(min, max))  :
    (tp == MyRand::EValType::Int16)  ? (IRnd*)(new RndUint16(min, max)) :
    (tp == MyRand::EValType::Uint16) ? (IRnd*)(new RndUint16(min, max)) :
    (tp == MyRand::EValType::Int32)  ? (IRnd*)(new RndInt32(min, max))  :
    (tp == MyRand::EValType::Uint32) ? (IRnd*)(new RndUint32(min, max)) :
    (tp == MyRand::EValType::Int64)  ? (IRnd*)(new RndInt64(min, max))  :
    (tp == MyRand::EValType::Uint64) ? (IRnd*)(new RndUint64(min, max)) :
    (tp == MyRand::EValType::Real32) ? (IRnd*)(new RndReal32(min, max)) :
    (tp == MyRand::EValType::Real64) ? (IRnd*)(new RndReal64(min, max)) :
    (IRnd*)nullptr);
  if(rnd != nullptr) {
    for(size_t i = 0; i < _n; i++) {
      T newValue{};
      for(;;) {
        rnd->fill(&newValue);
        if(!isUnique) {
          break; 
        }
        size_t j = 0; // надо посмотреть есть ли такое число в уже сгенерированных
        while(j < i) {
          if(arr[j] == newValue) {
            break; // да нашли, выход из проверки, дальше проверять не надо 
          }
          j++;
        }
        if(j == i) {
          break; // перебрали все уже сгенерированые, числа нет(если есть то j на выходе бедет меньше i, но оно ему равно)
        }
      }
      arr[i] = newValue;
    }
    delete rnd;
  }
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL bool MyRand::FillArray(const int8_t  min, const int8_t max, int8_t *arr, const size_t _n, bool isUnique) noexcept {
  if(isUnique && static_cast<size_t>(max - min + 1) <= _n) return false;  // Провека на зацикливание
  // если целочисленный диапазон меньше числа элементов, то ясно что сгенерить уникальные значения невозможно ибо их не хватит
  FillArrayImpl<int8_t>(MyRand::EValType::Int8, min, max, arr, _n, isUnique);
  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL bool MyRand::FillArray(const uint8_t  min, const uint8_t max, uint8_t *arr, const size_t _n, bool isUnique) noexcept {
  if(isUnique && static_cast<size_t>(max - min + 1) <= _n) return false;  // Провека на зацикливание
  // если целочисленный диапазон меньше числа элементов, то ясно что сгенерить уникальные значения невозможно ибо их не хватит
  FillArrayImpl<uint8_t>(MyRand::EValType::Uint8, min, max, arr, _n, isUnique);
  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL bool MyRand::FillArray(const int16_t  min, const int16_t max, int16_t *arr, const size_t _n, bool isUnique) noexcept {
  if(isUnique && static_cast<size_t>(max - min + 1) <= _n) return false;  // Провека на зацикливание
  // если целочисленный диапазон меньше числа элементов, то ясно что сгенерить уникальные значения невозможно ибо их не хватит
  FillArrayImpl<int16_t>(MyRand::EValType::Int16, min, max, arr, _n, isUnique);
  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL bool MyRand::FillArray(const uint16_t  min, const uint16_t max, uint16_t *arr, const size_t _n, bool isUnique) noexcept {
  if(isUnique && static_cast<size_t>(max - min + 1) <= _n) return false;  // Провека на зацикливание
  // если целочисленный диапазон меньше числа элементов, то ясно что сгенерить уникальные значения невозможно ибо их не хватит
  FillArrayImpl<uint16_t>(MyRand::EValType::Uint16, min, max, arr, _n, isUnique);
  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL bool MyRand::FillArray(const int32_t  min, const int32_t max, int32_t *arr, const size_t _n, bool isUnique) noexcept {
  if(isUnique && static_cast<size_t>(max - min + 1) <= _n) return false;  // Провека на зацикливание
  // если целочисленный диапазон меньше числа элементов, то ясно что сгенерить уникальные значения невозможно ибо их не хватит
  FillArrayImpl<int32_t>(MyRand::EValType::Int32, min, max, arr, _n, isUnique);
  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL bool MyRand::FillArray(const uint32_t  min, const uint32_t max, uint32_t *arr, const size_t _n, bool isUnique) noexcept {
  if(isUnique && static_cast<size_t>(max - min + 1) <= _n) return false;  // Провека на зацикливание
  // если целочисленный диапазон меньше числа элементов, то ясно что сгенерить уникальные значения невозможно ибо их не хватит
  FillArrayImpl<uint32_t>(MyRand::EValType::Uint32, min, max, arr, _n, isUnique);
  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL bool MyRand::FillArray(const int64_t  min, const int64_t max, int64_t *arr, const size_t _n, bool isUnique) noexcept {
  if(isUnique && static_cast<size_t>(max - min + 1) <= _n) return false;  // Провека на зацикливание
  // если целочисленный диапазон меньше числа элементов, то ясно что сгенерить уникальные значения невозможно ибо их не хватит
  FillArrayImpl<int64_t>(MyRand::EValType::Int64, min, max, arr, _n, isUnique);
  return true;
}
//-------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL bool MyRand::FillArray(const uint64_t  min, const uint64_t max, uint64_t *arr, const size_t _n, bool isUnique) noexcept {
  if(isUnique && static_cast<size_t>(max - min + 1) <= _n) return false;  // Провека на зацикливание
  // если целочисленный диапазон меньше числа элементов, то ясно что сгенерить уникальные значения невозможно ибо их не хватит
  FillArrayImpl<uint64_t>(MyRand::EValType::Uint64, min, max, arr, _n, isUnique);
  return true;
}
//-------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL bool MyRand::FillArray(const real32_t  min, const real32_t max, real32_t *arr, const size_t _n, bool isUnique) noexcept {
  if(isUnique && static_cast<size_t>(max - min + 1) <= _n) return false;  // Провека на зацикливание
  // если целочисленный диапазон меньше числа элементов, то ясно что сгенерить уникальные значения невозможно ибо их не хватит
  FillArrayImpl<real32_t>(MyRand::EValType::Real32, min, max, arr, _n, isUnique);
  return true;
}
//-------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL bool MyRand::FillArray(const real64_t  min, const real64_t max, real64_t *arr, const size_t _n, bool isUnique) noexcept {
  FillArrayImpl<real64_t>(MyRand::EValType::Real64, min, max, arr, _n, isUnique);
  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------
RNDEXT_DLL bool MyRand::FillArray(const MyRand::Rng &r, const size_t _n, void *arr, bool isUnique) noexcept {
  if(r.min.index() == 0 && r.max.index() == 0) {
    int8_t min = get<int8_t>(r.min), max = get<int8_t>(r.max); int8_t *marr = reinterpret_cast<int8_t*>(arr);
    FillArrayImpl<int8_t>(MyRand::EValType::Int8, min, max, marr, _n, isUnique);
  } else if(r.min.index() == 1 && r.max.index() == 1){
    int8_t min = get<uint8_t>(r.min), max = get<uint8_t>(r.max); uint8_t *marr = reinterpret_cast<uint8_t*>(arr);
    FillArrayImpl<uint8_t>(MyRand::EValType::Uint8, min, max, marr, _n, isUnique);
  } else if(r.min.index() == 2 && r.max.index() == 2) {
    int16_t min = get<int16_t>(r.min), max = get<int16_t>(r.max); int16_t *marr = reinterpret_cast<int16_t*>(arr);
    FillArrayImpl<int16_t>(MyRand::EValType::Int16, min, max, marr, _n, isUnique);
  } else if(r.min.index() == 3 && r.max.index() == 3) {
    uint16_t min = get<uint16_t>(r.min), max = get<uint16_t>(r.max); uint16_t *marr = reinterpret_cast<uint16_t*>(arr);
    FillArrayImpl<uint16_t>(MyRand::EValType::Uint16, min, max, marr, _n, isUnique);
  } else if(r.min.index() == 4 && r.max.index() == 4) {
    int32_t min = get<int32_t>(r.min), max = get<int32_t>(r.max); int32_t *marr = reinterpret_cast<int32_t*>(arr);
    FillArrayImpl<int32_t>(MyRand::EValType::Int32, min, max, marr, _n, isUnique);
  } else if(r.min.index() == 5 && r.max.index() == 5) {
    uint32_t min = get<uint32_t>(r.min), max = get<uint32_t>(r.max); uint32_t *marr = reinterpret_cast<uint32_t*>(arr);
    FillArrayImpl<uint32_t>(MyRand::EValType::Uint32, min, max, marr, _n, isUnique);
  } else if(r.min.index() == 6 && r.max.index() == 6) {
    int64_t min = get<int64_t>(r.min), max = get<int64_t>(r.max); int64_t *marr = reinterpret_cast<int64_t*>(arr);
    FillArrayImpl<int64_t>(MyRand::EValType::Int64, min, max, marr, _n, isUnique);
  } else if(r.min.index() == 7 && r.max.index() == 7) {
    uint64_t min = get<uint64_t>(r.min), max = get<uint64_t>(r.max); uint64_t *marr = reinterpret_cast<uint64_t*>(arr);
    FillArrayImpl<uint64_t>(MyRand::EValType::Uint64, min, max, marr, _n, isUnique);
  } else if(r.min.index() == 8 && r.max.index() == 8) {
    real32_t min = get<real32_t>(r.min), max = get<real32_t>(r.max); real32_t *marr = reinterpret_cast<real32_t*>(arr);
    FillArrayImpl<real32_t>(MyRand::EValType::Real32, min, max, marr, _n, isUnique);
  } else if(r.min.index() == 9 && r.max.index() == 9) {
    real64_t min = get<real64_t>(r.min), max = get<real64_t>(r.max); real64_t *marr = reinterpret_cast<real64_t*>(arr);
    FillArrayImpl<real64_t>(MyRand::EValType::Real64, min, max, marr, _n, isUnique);
  } else {
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------
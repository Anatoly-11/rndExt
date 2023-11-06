#include <Rnd.h>
#include <random>
#include <map>
#include <chrono>
//---------------------------------------------------------------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------------------------------------------------------------
mutex mtx;
//-------------------------------------------------------------------------------------------------------------------------------
static bool isMultiThread = true;
//-------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API void MyRand::SetMultithread(const bool _Is) noexcept {
  isMultiThread = _Is;
}
//-------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API bool MyRand::getMultithread() noexcept {
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
MyRand :: IRndInt8 :: ~IRndInt8() {};
//---------------------------------------------------------------------------------------------------------------------------------
MyRand :: IRndInt16 :: ~IRndInt16() {};
//---------------------------------------------------------------------------------------------------------------------------------
MyRand :: IRndInt32 :: ~IRndInt32() {};
//---------------------------------------------------------------------------------------------------------------------------------
MyRand :: IRndInt64 :: ~IRndInt64() {};
//---------------------------------------------------------------------------------------------------------------------------------
MyRand :: IRndUint8 :: ~IRndUint8() {};
//---------------------------------------------------------------------------------------------------------------------------------
MyRand :: IRndUint16 :: ~IRndUint16() {};
//---------------------------------------------------------------------------------------------------------------------------------
MyRand :: IRndUint32 :: ~IRndUint32() {};
//---------------------------------------------------------------------------------------------------------------------------------
MyRand :: IRndUint64 :: ~IRndUint64() {};
//---------------------------------------------------------------------------------------------------------------------------------
MyRand :: IRndReal32 :: ~IRndReal32() {};
//---------------------------------------------------------------------------------------------------------------------------------
MyRand :: IRndReal64 :: ~IRndReal64() {};
//---------------------------------------------------------------------------------------------------------------------------------
class RndInt8 : public MyRand :: IRndInt8, public RndIntImpl<int16_t> {
public:
  RndInt8() : RndIntImpl<int16_t>() {}

  RndInt8(const int8_t min, const int8_t max) : RndIntImpl<int16_t>(min, max) {}

  virtual int8_t get() noexcept  override {
    return RndIntImpl<int16_t>::get();
  }

  virtual int8_t get(const int8_t min, const int8_t max) noexcept  override {
    return RndIntImpl<int16_t>::get(min, max);
  }

  virtual int8_t getRep(const int8_t min, const int8_t max) noexcept  override {
    return RndIntImpl<int16_t>::getRep(min, max);
  }
  virtual ~RndInt8() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndUint8 : public MyRand ::IRndUint8, public RndIntImpl<uint16_t> {
public:
  RndUint8() : RndIntImpl<uint16_t>() {}

  RndUint8(const uint8_t min, const uint8_t max) : RndIntImpl<uint16_t>(min, max) {}

  virtual uint8_t get() noexcept  override {
    return RndIntImpl<uint16_t>::get();
  }

  virtual uint8_t get(const uint8_t min, const uint8_t max) noexcept  override {
    return RndIntImpl<uint16_t>::get(min, max);
  }

  virtual uint8_t getRep(const uint8_t min, const uint8_t max) noexcept  override {
    return RndIntImpl<uint16_t>::getRep(min, max);
  }

  virtual ~RndUint8() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndInt16 : public MyRand :: IRndInt16, public RndIntImpl<int16_t> {
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

  virtual ~RndInt16() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndUint16 : public MyRand::IRndUint16, public RndIntImpl<uint16_t> {
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

  virtual ~RndUint16() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndInt32 : public MyRand :: IRndInt32, public RndIntImpl<int32_t> {
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

  virtual ~RndInt32() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndUint32 : public MyRand :: IRndUint32, public RndIntImpl<uint32_t> {
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

  virtual ~RndUint32() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndInt64 : public MyRand :: IRndInt64, public RndIntImpl<int64_t> {
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

  virtual ~RndInt64() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndUint64 : public MyRand :: IRndUint64, public RndIntImpl<uint64_t> {
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

  virtual ~RndUint64() override {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndReal32 : public MyRand :: IRndReal32, public  RndRealImpl<real32_t> {
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

  virtual ~RndReal32() {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
class RndReal64 : public MyRand :: IRndReal64, public  RndRealImpl<real64_t> {
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

  virtual ~RndReal64() {
  }
};
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API void* MyRand::GetRnd(const EValType tp) noexcept {
  unique_lock<mutex> grd(mtx, defer_lock);
  if(isMultiThread) {
    grd.lock();
  }
  void *rnd = (tp == EValType::Int8 ? (void*)(new RndInt8) :
    tp == EValType::Uint8 ? (void*)(new RndUint8) :
    tp == EValType::Int16 ? (void*)(new RndUint16) :
    tp == EValType::Uint16 ? (void*)(new RndUint16) :
    tp == EValType::Int ? (void*)(new RndInt32) :
    tp == EValType::Uint ? (void*)(new RndUint32) :
    tp == EValType::Long ? (void*)(new RndInt64) :
    tp == EValType::Ulong ? (void*)(new RndUint64) :
    tp == EValType::Flt ? (void*)(new RndReal32) :
    tp == EValType::Dbl ? (void*)(new RndReal64) : nullptr);
  if(isMultiThread) {
    grd.unlock();
  }
  return rnd;
}
//---------------------------------------------------------------------------------------------------------------------------------
RND_DLL_API MyRand::IRndInt8 *MyRand::GetRnd(const int8_t min, const int8_t max) noexcept {
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
RND_DLL_API MyRand::IRndUint8 *MyRand::GetRnd(const uint8_t min, const uint8_t max) noexcept {
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
RND_DLL_API MyRand::IRndInt16 *MyRand::GetRnd(const int16_t min, const int16_t max) noexcept {
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
RND_DLL_API  MyRand::IRndUint16 *MyRand::GetRnd(const uint16_t min, const uint16_t max) noexcept {
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
RND_DLL_API MyRand::IRndInt32 *MyRand::GetRnd(const int32_t min, const int32_t max) noexcept {
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
RND_DLL_API MyRand::IRndUint32 *MyRand::GetRnd(const uint32_t min, const uint32_t max) noexcept {
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
RND_DLL_API MyRand::IRndInt64 *MyRand::GetRnd(const int64_t min, const int64_t max) noexcept {
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
RND_DLL_API MyRand::IRndUint64 *MyRand::GetRnd(const uint64_t min, const uint64_t max) noexcept {
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
RND_DLL_API MyRand::IRndReal32 *MyRand::GetRnd(const real32_t min, const real32_t max) noexcept {
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
RND_DLL_API MyRand::IRndReal64 *MyRand::GetRnd(const real64_t min, const real64_t max) noexcept {
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
RND_DLL_API bool MyRand::FillArray(const int8_t  min, const int8_t max, int8_t *arr, const size_t _n, bool isUnique) noexcept {

}
//---------------------------------------------------------------------------------------------------------------------------------
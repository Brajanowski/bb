// basic containers library with basic features for C++ language
#ifndef BB_CONTAINER_H_
#define BB_CONTAINER_H_

#include <stdlib.h>

// array
template<typename T, unsigned int BEGIN_CAPACITY = 4>
class bb_array {
public:
  bb_array() :
      __data(0),
      __size(0),
      __capacity(BEGIN_CAPACITY) {
  }

  virtual ~bb_array() {
    clear();
  }

  void add(T value) {
    if (__data == 0) {
      __size = 1;
      __capacity = BEGIN_CAPACITY;
      __data = (T*)malloc(sizeof(T) * __capacity);
      __data[0] = value;
    } else if (__size == __capacity) {
      __capacity *= 2;
      __data = (T*)realloc(__data, __capacity * sizeof(T));
      __data[__size] = value;
      ++__size;
    } else {
      __data[__size] = value;
      ++__size;
    }
  }

  void remove(unsigned int index, unsigned int num = 1) {
    if (index + num > __size) {
      return;
    }

    for (unsigned int i = index + num; i < __size; i++) {
      __data[i - num] = __data[i];
    }

    __size -= num;
  }

  T pop_first() {
    T ret = __data[0];
    remove(0, 1);
    return ret;
  }

  T pop_last() {
    return __data[--__size];
  }

  void clear() {
    if (__data) {
      free(__data);
      __data = 0;
      __size = 0;
      __capacity = BEGIN_CAPACITY;
    }
  }

  void reserve(unsigned int capacity) {
    if (capacity > __capacity) {
      __capacity = capacity;
      __data = (T*)realloc(__data, __capacity * sizeof(T));
    }
  }

  inline unsigned int size() const { return __size; }
  inline unsigned int capacity() const { return __capacity; }
  inline T get(unsigned int index) { return __data[index]; }
  
  T& operator[](unsigned int index) { return __data[index]; }

private:
  T* __data;
  unsigned int __size;
  unsigned int __capacity;
};

#endif


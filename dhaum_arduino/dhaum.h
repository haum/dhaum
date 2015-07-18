#ifndef DHAUM_H
#define DHAUM_H

#include <Arduino.h>

struct DhaumObject {
  uint32_t bits;
  DhaumObject(int pad_nr) : bits(1 << (pad_nr-1)) {}
  DhaumObject operator | (DhaumObject &other) {
    DhaumObject res(other);
    res.bits |= bits;
    return res;
  }
};

typedef enum {
  UNTOUCHED, // Not touched at all
  TOUCHED, // Touched this loop
  LASTTOUCHED, // Touched last loop (if needed)
} touchstatus_e;

struct DhaumBinder {
  uint32_t bits;
  uint32_t mask;

  touchstatus_e touched;
  char debounce;
  touchstatus_e touched_filtered;

  DhaumBinder(DhaumObject obj, uint32_t param_mask = 0xffffffff) : bits(obj.bits), mask(param_mask) {}
};

extern DhaumBinder * binders;
extern int binders_size;

#endif

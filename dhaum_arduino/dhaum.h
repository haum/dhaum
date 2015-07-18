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

struct DhaumMidi {
  enum MidiNote note;
  enum MidiOctave octave;
  enum MidiChannel channel;
  unsigned char velocity;

  DhaumMidi(enum MidiNote param_note, enum MidiOctave param_octave = MidiOctave_3, MidiChannel param_channel = MidiChannel_1, unsigned char param_velocity = 64) :
    note(param_note), octave(param_octave), channel(param_channel), velocity(param_velocity) {}
};

typedef enum {
  UNTOUCHED, // Not touched at all
  TOUCHED, // Touched this loop
  LASTTOUCHED, // Touched last loop (if needed)
} touchstatus_e;

struct DhaumBinder {
  uint32_t bits;
  uint32_t mask;

  DhaumMidi midi;

  touchstatus_e touched;
  char debounce;
  touchstatus_e touched_filtered;

  DhaumBinder(DhaumObject obj, DhaumMidi param_midi, uint32_t param_mask = 0xffffffff) : bits(obj.bits), mask(param_mask), midi(param_midi) {}
};

extern DhaumBinder * binders;
extern int binders_size;

#endif

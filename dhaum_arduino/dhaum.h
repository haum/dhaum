#ifndef DHAUM_H
#define DHAUM_H

#include <Arduino.h>

typedef uint32_t DhaumBits;

struct DhaumObject {
  DhaumBits bits;
  DhaumObject(uint8_t pad_nr) : bits(1 << (pad_nr-1)) {}
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
  uint8_t velocity;

  DhaumMidi(enum MidiNote param_note, enum MidiOctave param_octave = MidiOctave_3, MidiChannel param_channel = MidiChannel_1, uint8_t param_velocity = 64) :
    note(param_note), octave(param_octave), channel(param_channel), velocity(param_velocity) {}
};

typedef enum {
  UNTOUCHED,
  TOUCHED,
} touchstatus_e;

struct DhaumBinder {
  DhaumBits bits;
  DhaumBits mask;

  DhaumMidi midi;

  touchstatus_e touched;
  int8_t debounce;
  touchstatus_e touched_filtered;

  DhaumBinder(DhaumObject obj, DhaumMidi param_midi, uint32_t param_mask = 0xffffffff) : bits(obj.bits), mask(param_mask), midi(param_midi) {}
};

extern DhaumBinder * binders;
extern uint16_t binders_size;

#endif

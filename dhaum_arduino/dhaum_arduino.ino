#include "dhaum.h"

// Objects
static DhaumObject casserole(1);
static DhaumObject pelote(2);
static DhaumObject chat(6);
static DhaumObject echelle(7);

// Sounds
static DhaumMidi ronronnement(MidiNote_C);
static DhaumMidi coup_de_casserole(MidiNote_D);
static DhaumMidi nyan(MidiNote_E);
static DhaumMidi cuisson(MidiNote_G);
static DhaumMidi coq(MidiNote_B);

// Binders
DhaumBinder binders_data[] = {

  DhaumBinder(
    chat | pelote,
    ronronnement
  ),

  DhaumBinder(
    casserole | chat,
    coup_de_casserole
  ),

  DhaumBinder(
    casserole | pelote,
    cuisson
  ),

  DhaumBinder(
    casserole | echelle,
    coq
  ),

  DhaumBinder(
    casserole | chat | pelote,
    nyan
   ),

};

uint16_t binders_size = (sizeof(binders_data)/sizeof(*binders_data));
DhaumBinder * binders = binders_data;

#include "dhaum.h"

// Objects
static DhaumObject casserole(1);
static DhaumObject pelote(2);
static DhaumObject chat(6);

// Sounds
static DhaumMidi ronronnement(MidiNote_C);
static DhaumMidi coup_de_casserole(MidiNote_D);
static DhaumMidi nyan(MidiNote_E);

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
    casserole | chat | pelote,
    nyan
   ),

};

int binders_size = (sizeof(binders_data)/sizeof(*binders_data));
DhaumBinder * binders = binders_data;

#include "dhaum.h"

// Objects
static DhaumObject casserole(1);
static DhaumObject bouquet(2);
static DhaumObject chat(6);

// Binders
DhaumBinder binders_data[] = {

  DhaumBinder(chat | bouquet),
  DhaumBinder(casserole | chat),
  DhaumBinder(casserole | chat | bouquet),

};

int binders_size = (sizeof(binders_data)/sizeof(*binders_data));
DhaumBinder * binders = binders_data;

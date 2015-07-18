/* To be used with Léoké */

#define PADBIT(PAD) (1 << (PAD-1))
#define PADSNB (sizeof(L)/sizeof(*L))

#define DEBUG_RAW_CODE 0

typedef enum {
  UNTOUCHED, // Not touched at all
  TOUCHED, // Touched this loop
  LASTTOUCHED, // Touched last loop
} touchstatus_e;

struct binder_s {
  uint32_t bits;
  uint32_t mask;

  touchstatus_e touched;
  char debounce;
  touchstatus_e touched_filtered;
} binders[] = {
  { PADBIT(1) | PADBIT(2), 0xffffffff, },
  { PADBIT(5) | PADBIT(6), 0xffffffff, },
};

#define BINDERNB (sizeof(binders)/sizeof(*binders))
#define MAXDEBOUNCE 5

void setup() {
  // All others are input and untouched
  for (int i = 0; i < PADSNB; ++i) {
    pinMode(L[i], INPUT);
    digitalWrite(L[i], LOW);
  }

  // Reset binders
  for (int i = 0; i < BINDERNB; ++i) {
    binders[i].touched = UNTOUCHED;
    binders[i].debounce = 0;
  }

  // Services begin
  Serial.begin(115200);
}

void loop() {
  // For each key
  uint32_t active = 1; // Current bit operated
  for (int i = 1; i < PADSNB; ++i) {
    uint32_t pushed = active; // Bitfield of pressed pads
    uint32_t bitj = active; // Current bit in inner loop

    // Activate ith pad
    pinMode(L[i], OUTPUT);

    // Detect active pads
    for (int j = i + 1; j < PADSNB; ++j) {
      bitj <<= 1;
      if (!digitalRead(L[j]))
        pushed |= bitj ;
    }

    // Debug show multi presses
    if (active != pushed && DEBUG_RAW_CODE) {
      Serial.print("Code : ");
      Serial.println(pushed, HEX);
    }

    // Detect touch events
    for (int j = 0; j < BINDERNB; ++j) {
      binder_s & binder = binders[j];
      touchstatus_e touched = ((binder.bits & binder.mask) == (pushed & binder.mask)) ? TOUCHED : UNTOUCHED;
      if (touched == TOUCHED)
        binder.touched = TOUCHED;
    }

    // Deactivate ith pad
    pinMode(L[i], INPUT);
    active <<= 1;
  }

  // Detect untouch events + debounce
  for (int j = 0; j < BINDERNB; ++j) {
    binder_s & binder = binders[j];
    if (binder.touched == LASTTOUCHED) {
      binder.touched = UNTOUCHED;

    } else if (binder.touched == TOUCHED) {
      binder.touched = LASTTOUCHED;
    }

    binder.debounce += (binder.touched == UNTOUCHED) ? -1 : 1;
    if (binder.debounce > MAXDEBOUNCE)
      binder.debounce = MAXDEBOUNCE;
    if (binder.debounce < 0)
      binder.debounce = 0;
      if (binder.debounce == MAXDEBOUNCE && binder.touched_filtered == UNTOUCHED) {
        Serial.print("On ");
        Serial.println(binder.bits, HEX);
        binder.touched_filtered = LASTTOUCHED;
      } else if (binder.debounce == 0 && binder.touched_filtered != UNTOUCHED) {
        Serial.print("Off ");
        Serial.println(binder.bits, HEX);
        binder.touched_filtered = UNTOUCHED;
      }
  }

  // Debug separator
  if (DEBUG_RAW_CODE)
    Serial.println("==");

  // Debounce
  delay(5);
}


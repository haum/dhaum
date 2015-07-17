/* To be used with Léoké */

#define KEYSNB (sizeof(L)/sizeof(*L))

#define PADBIT(PAD) (1 << PAD)

typedef enum {
  UNTOUCHED,
  TOUCHED,
} touchstatus_e;

struct binder_s {
  uint32_t bits;
  uint32_t mask;

  touchstatus_e touched;
} binders[] = {
  { PADBIT(1) | PADBIT(2), 0xffffffff, UNTOUCHED },
  { PADBIT(5) | PADBIT(6), 0xffffffff, UNTOUCHED },
};

#define BINDERNB (sizeof(binders)/sizeof(*binders))

void setup() {
  // All others are input and untouched
  for (int i = 0; i < KEYSNB; ++i) {
    pinMode(L[i], INPUT);
    digitalWrite(L[i], LOW);
  }

  // Reset binders
  for (int i = 0; i < BINDERNB; ++i) {
    binders[i].touched = UNTOUCHED;
  }

  // Services begin
  Serial.begin(115200);
}

void loop() {
  // For each key
  uint32_t active = 1;
  for (int i = 1; i < KEYSNB; ++i) {
    uint32_t pushed = active;
    uint32_t bitj = active;
    pinMode(L[i], OUTPUT);
    for (int j = i + 1; j < KEYSNB; ++j) {
      bitj <<= 1;
      int sensorValue = digitalRead(L[j]);
      if (!sensorValue)
        pushed |= bitj ;
    }
    if (active != pushed) {
      Serial.print("Code : ");
      Serial.println(pushed, HEX);
    }
    for (int j = 0; j < BINDERNB; ++j) {
      binder_s & binder = binders[j];
      touchstatus_e touched = (binder.bits & binder.mask == pushed & binder.mask) ? TOUCHED : UNTOUCHED;
      if (touched && binder.touched == UNTOUCHED) {
        Serial.print("On ");
        Serial.println(pushed, HEX);

      } else if (!touched && binder.touched == TOUCHED) {
        Serial.print("Off ");
        Serial.println(pushed, HEX);
      }
      binder.touched = touched;
    }
    active <<= 1;
    pinMode(L[i], INPUT);
  }
  delay(100);
}


/* To be used with Léoké */

#define KEYSNB (sizeof(L)/sizeof(*L))

typedef enum {
  UNTOUCHED,
  TOUCHED,
} touchstatus_e;

touchstatus_e touching[KEYSNB];

void setup() {
  // All others are input and untouched
  for (int i = 0; i < KEYSNB; ++i) {
    pinMode(L[i], INPUT);
    digitalWrite(L[i], LOW);
    touching[i] = UNTOUCHED;
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
      if (!sensorValue && !touching[j]) {
        Serial.print("On ");
        Serial.println(j);
        pushed |= bitj;
      } else if (sensorValue && touching[j]) {
        Serial.print("Off ");
        Serial.println(j);
      }
      touching[j] = (!sensorValue) ? TOUCHED : UNTOUCHED;
    }
    if (active != pushed) {
      Serial.print("Code : ");
      Serial.println(pushed, HEX);
    }
    active <<= 1;
    pinMode(L[i], INPUT);
  }
  delay(100);
}


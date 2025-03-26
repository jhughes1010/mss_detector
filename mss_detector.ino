//MSS block detector
//ATTINY85
//version 2025.3.23

//these will change with new PCB layout
#define TEST_PIN PB0
#define DETECT_IN PB4
#define LED PB2
#define UNUSED PB3
#define MCU_OCCUPIED_OUT PB1

void setup() {
  pinMode(DETECT_IN, INPUT_PULLUP);
  pinMode(TEST_PIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(MCU_OCCUPIED_OUT, OUTPUT);

  digitalWrite(LED, LOW);
  digitalWrite(MCU_OCCUPIED_OUT, LOW);
  delay(1000);
  digitalWrite(MCU_OCCUPIED_OUT, HIGH);
  delay(5000);
}

void loop() {
  int heartbeat;
  int occupied;
  int test;
  static long int activeTime = 0;
  static bool active = false;


  heartbeat = !((millis() / 500) % 4);
  occupied = !digitalRead(DETECT_IN);
  test = !digitalRead(TEST_PIN);
  if (!active) {
    digitalWrite(LED, heartbeat);
  }
  //evaluate inputs and set active flag
  if (occupied || test) {
    activeTime = millis();
    active = true;
    //timer to reduce flicker
  } else {
    if (activeTime + 1000 < millis()) {
      active = false;
    }
  }

    //control outputs based on active flag
    if (active) {
      digitalWrite(MCU_OCCUPIED_OUT, HIGH);
      digitalWrite(LED, HIGH);
    } else {
      digitalWrite(MCU_OCCUPIED_OUT, LOW);
      digitalWrite(LED, LOW);
    }
}

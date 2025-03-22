//MSS block detector
//ATTINY85

#define TEST_PIN PB0
#define LED PB0
#define DETECT_IN PB1
#define MSS_OUT PB2

void setup() {
  pinMode(DETECT_IN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(MSS_OUT, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(MSS_OUT, LOW);

}

void loop() {
  int heartbeat;
  int occupied;
  int test;
  static long int activeTime = 0;


  heartbeat = !((millis() / 500) % 4);
  occupied = !digitalRead(DETECT_IN);
  test = digitalRead(TEST_PIN);
  digitalWrite(LED, heartbeat);

  if (occupied) {
    activeTime = millis();
    digitalWrite(MSS_OUT, HIGH);
    digitalWrite(LED, HIGH);
  } else {
    if (activeTime + 1000 < millis()) {
      digitalWrite(MSS_OUT, LOW);
    }
  }
}

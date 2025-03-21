//MSS block detector
//ATTINY85


#define LED PB0
#define DETECT_IN PB1
#define MSS_OUT PB2

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(MSS_OUT, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(MSS_OUT, LOW);
}

void loop() {
  int heartbeat;
  int occupied;
  static long int activeTime = 0;


  heartbeat = (millis() / 1000) % 2;
  occupied = digitalRead(DETECT_IN);

  digitalWrite(LED, heartbeat);

  if(occupied){
    activeTime=millis();
    digitalWrite(MSS_OUT, HIGH);
    digitalWrite(LED, HIGH);
  }
  else{
    if(activeTime+400<millis()){
      digitalWrite(MSS_OUT, LOW);
    }
  }
}

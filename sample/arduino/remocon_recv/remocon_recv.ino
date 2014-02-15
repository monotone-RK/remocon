#define IR_INPIN   7
#define LOW_STATE  0  // receiving IR signal
#define HIGH_STATE 1
#define WAITTIME   5000000  // 5sec
#define BAUDRATE   115200

void setup() {
  pinMode(IR_INPIN, INPUT);
  Serial.begin(BAUDRATE);
}
 
void waitIfLow() {
  while (digitalRead(IR_INPIN) == LOW);  // waiting
}
 
void waitIfHigh() {
  while (digitalRead(IR_INPIN) == HIGH);  // waiting
} 

int waitByTime() {
  unsigned long start = micros();
  while (digitalRead(IR_INPIN) == HIGH) {
    if (micros() - start > WAITTIME) return 1;
  }
  return 0;
}

void recvSignal() {
  unsigned long measure_end = micros();
  unsigned long measure_start = micros();
  int state = HIGH_STATE;
  boolean recv_signal = false;
  Serial.print("Ready to receive IR signals\n");
  while (1) {
    if (state == LOW_STATE) {
      waitIfLow();
    } else {
      int ret = waitByTime();
      if (ret == 1 && recv_signal) {
        Serial.print("\n");
        Serial.print("END\n");        
        return;  // next turn
      } else if (ret == 1 && !recv_signal) {
        waitIfHigh();  // waiting for receiving signals
      }
    }
    measure_end = micros();  // finish measuring transmittion time
    if (!recv_signal) { 
      recv_signal = true;
    } else {
      Serial.print((measure_end - measure_start)/10, DEC); // per 10us
      Serial.print(",");
    }
    measure_start = measure_end;  // start to measure transmittion time
    if (state == HIGH_STATE) state = LOW_STATE;
    else                     state = HIGH_STATE;
  }
}

void loop() {
  recvSignal();
}

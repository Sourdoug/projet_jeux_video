#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK, 12);

const int pins[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16};
const int btnNr[12] = {2, 0, 7, 4, 5, 6, 8, 9, 1, 10, 11, 3};

void setup() {
  for(int i=0; i<sizeof(pins)/sizeof(pins[0]); i++) {
    pinMode(pins[i], INPUT_PULLUP);
  }
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  Joystick.begin();
}

void loop() {
  Joystick.setXAxis(map(analogRead(A3), 0, 1023, 0, 255));
  Joystick.setYAxis(map(analogRead(A2), 0, 1023, 0, 255));
  Joystick.setZAxis(map(analogRead(A1), 0, 1023, 255, 0));
  Joystick.setRzAxis(map(analogRead(A0), 0, 1023, 255, 0));
  for(int i=0; i<sizeof(pins)/sizeof(pins[0]); i++) {
    if(!digitalRead(pins[i])) {
      Joystick.pressButton(btnNr[i]);
    } else {
      Joystick.releaseButton(btnNr[i]);
    }
  }
  delay(10);
}
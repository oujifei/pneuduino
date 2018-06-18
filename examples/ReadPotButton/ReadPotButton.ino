#include <PneuDuino.h>

PneuDuino p;

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);
}

// Global variables
unsigned long cycle_start;
unsigned long turn_off_time;
const unsigned long cycle_length = 200L;

void loop() {
  p.update();

  // read the potentiometer and button
  int pot = p.readPot();
  bool button = p.readButton(0);

  // handle potentiometer
  // first check the current time
  unsigned long m = millis();

  // current cycle has ended, start a new one
  if(m > cycle_start + cycle_length) {
    turn_off_time = m + map(pot, 0, 63, 0, cycle_length);
    p.in(1, LEFT);
    cycle_start = m;
  }

  // turn off time reached
  if(m >= turn_off_time) {
    p.out(1, LEFT);
  }

  // handle button state
  if(button) {
    p.in(1, RIGHT);
  } else {
    p.out(1, RIGHT);
  }
}


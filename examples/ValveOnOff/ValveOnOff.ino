#include <PneuDuino.h>

PneuDuino p;

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);
}

void loop() {
  // call this every loop()
  p.update();

  // number of 500ms increments that have passed
  int time = millis()/500;

  // turn valves on/off cycling over 4 time increments
  switch(time % 4) {
  case 0:
    p.in(1, LEFT); // p.in(address, side)
    break;
  case 1:
    p.out(1, LEFT);
    break;
  case 2:
    p.in(1, RIGHT);
    break;
  case 3:
    p.out(1, RIGHT);
    break;
  }
}

#include <PneuDuino.h>

PneuDuino p;

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);
}


void loop() {
  p.update();

  // read the potentiometer
  int pot = p.readPot();

  int pressure = p.readPressure(1);
  Serial.println(pressure);

  // set the desired pressure as a function of pot position
  // note: to end automatic pressure management, call inflate(), deflate(), or hold()
  p.setPressure(1, map(pot, 0, 63, 55, 90));
}


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

  if(p.readButton(0)) {
    p.deflate(1);
  } else {
    p.setPressure(1, map(pot, 0, 63, 55, 90));
  }
}


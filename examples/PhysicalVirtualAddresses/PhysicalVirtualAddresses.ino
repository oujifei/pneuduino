#include <PneuDuino.h>

PneuDuino p;

void setup() {
  Serial.begin(9600);
  p.begin();
}


void loop() {
  p.setAddressMode(PNEUDUINO_ADDRESS_PHYSICAL);
  delay(5000);
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);
  delay(5000);
}


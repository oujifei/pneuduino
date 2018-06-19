#include <PneuDuino.h>

PneuDuino p;

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);
}

void loop() {
  p.update();

  // read pressure from board with virtual address 1
  int pressure = p.readPressure(1);
  Serial.println(pressure);

  delay(500);
}

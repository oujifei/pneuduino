#include <PneuDuino.h>
#include <Wire.h>

PneuDuino p;

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);

  // uncomment this line if the ADDR_SEL pins
  // are connected with a jumper
  //p.setAnalogAddressJumper(true);
}

void loop() {
  p.update();

  // read analog sensor on ANALOG_0
  int reading = p.readAnalog(0);

  // set pressure proportionally to reading
  // adjust map values if necessary
  int pressure = map(reading, 0, 1666, 60, 90);
  p.setPressure(1, pressure);
}


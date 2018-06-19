#include <PneuDuino.h>

PneuDuino p;

// address of the board being used as a logic gate
#define ADDRESS 1

// minimum/maximum pressures for a logic true/false
#define HIGH 80
#define LOW 65

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);
}


void loop() {
  p.update();

  // read the pressure of input B, which is connected to pressure sensor
  int pressure = p.readPressure(ADDRESS);

  // when input B is true, output is equal to input A
  if(pressure >= HIGH) {
    p.in(ADDRESS, LEFT);
  }

  // when input B is false, output is always false
  if(pressure <= LOW) {
    p.out(ADDRESS, LEFT);
  }
}


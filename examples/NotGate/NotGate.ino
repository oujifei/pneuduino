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
  int pressure = p.readPressure(ADDRESS);

  // when input is true, output a false (exhaust air)
  if(pressure >= HIGH) {
    p.out(ADDRESS, LEFT);
  }

  // when input is false, output a true (connect to supply)
  if(pressure <= LOW) {
    p.in(ADDRESS, LEFT);
  }
}


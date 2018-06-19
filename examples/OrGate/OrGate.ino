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

  // when input B is true, connect output to B and disconnect output from A
  if(pressure >= HIGH) {
    p.in(ADDRESS, RIGHT);
    p.out(ADDRESS, LEFT);
  }

  // when input B is false, connect output to A and disconnect output from B
  if(pressure <= LOW) {
    p.in(ADDRESS, LEFT);
    p.out(ADDRESS, RIGHT);
  }
}


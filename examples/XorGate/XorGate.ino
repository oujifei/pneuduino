#include <PneuDuino.h>

PneuDuino p;

// address of the board being used as a logic gate
#define ADDRESS_A 1
#define ADDRESS_B 2

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

  // read the pressures of the inputs
  int pressure_a = p.readPressure(ADDRESS_A);
  int pressure_b = p.readPressure(ADDRESS_B);

  Serial.print("A ");
  Serial.println(pressure_a);
  Serial.print("B ");
  Serial.println(pressure_b);

  // when logic values are the same, output false
  if((pressure_a >= HIGH && pressure_b >= HIGH) || (pressure_a <= LOW && pressure_b <= LOW)) {
    p.out(ADDRESS_A, LEFT);
    p.out(ADDRESS_A, RIGHT);
    p.out(ADDRESS_B, LEFT);
    p.out(ADDRESS_B, RIGHT);
  }

  // otherwise, output true
  else {
    // connect right valves to left valves
    p.in(ADDRESS_A, RIGHT);
    p.in(ADDRESS_B, RIGHT);

    // if A is true, pass its value on
    if(pressure_a >= HIGH) {
      p.in(ADDRESS_A, LEFT);
      p.out(ADDRESS_B, LEFT);
    }

    // if B is true, pass its value on
    if(pressure_b >= HIGH) {
      p.in(ADDRESS_B, LEFT);
      p.out(ADDRESS_A, LEFT);
    }
  }
}


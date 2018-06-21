#include <PneuDuino.h>

PneuDuino p;

// variables for timing each vibration on/off cycle
unsigned long on_time, off_time;
// the length of a single on/off vibration
unsigned long vibration_period;

void setup() {
  Serial.begin(9600);

  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);
}


void loop() {
  p.update();

  // set the vibration rate depending on potentiometer
  int pot = p.readPot();
  vibration_period = map(pot, 0, 63, 50, 20);

  // the pressure at which we turn on LEDs
  int pressure_threshold = 70;

  // the current pressure
  int pressure = p.readPressure(1);

  // pressure below threshold
  if(pressure < pressure_threshold) {
    // maintain pressure slightly below threshold
    p.setPressure(1, pressure_threshold - 3);
  }

  // inflatable was squeezed, pressure risen above threshold
  else {
    // get the time
    unsigned long m = millis();

    // start of a new on/off cycle
    if(m > on_time + vibration_period) {
      p.inflate(1);
      on_time = m;
      off_time = m + (vibration_period / 3);
    }

    // turn off time reached
    if(m > off_time) {
      p.deflate(1);
    }
  }
}


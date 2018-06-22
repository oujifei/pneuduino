#include <PneuDuino.h>

// include the library for the touch sensor
// https://github.com/Seeed-Studio/Grove_I2C_Touch_Sensor
#include <i2c_touch_sensor.h>

PneuDuino p;

// object for the touch sensor
i2ctouchsensor touch;

// timing data
unsigned long turn_off_time;

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);

  // initialize the touch sensor
  touch.initialize();
}


void loop() {
  p.update();

  // update touch sensor
  touch.getTouchState();

  // if the sensor has detected a touch on any channel
  if(touch.touched) {
    // turn on valve and reset time
    p.in(1, LEFT);
    turn_off_time = millis() + 250L;
  }

  // no touch
  else {
    // if enough time has elapsed, turn off valve
    if(millis() > turn_off_time) {
      p.out(1, LEFT);
    }
  }
}


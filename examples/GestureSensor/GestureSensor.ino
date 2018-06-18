#include <PneuDuino.h>

// include the library for our gesture sensor
// https://github.com/Seeed-Studio/Gesture_PAJ7620
#include <paj7620.h>

PneuDuino p;

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);

  // initialize the gesture sensor
  uint8_t error = paj7620Init();
  if(error) {
    Serial.println("Gesture sensor error");
    Serial.println(error);
  }
}


void loop() {
  p.update();

  // declare variables to hold gesture read data
  uint8_t gesture, error;

  // read the gesture sensor
  // see the sensor's library for documentation
  error = paj7620ReadReg(0x43, 1, &gesture);

  // respond to the gesture
  if(!error) {
    switch(gesture) {
    case GES_FORWARD_FLAG: // hand has moved towards sensor
      // turn valve on, as if air had been squeezed in
      p.in(1, LEFT);
      break;
    case GES_BACKWARD_FLAG: // hand has moved away from sensor
      // turn valve off, as if air had been let out
      p.out(1, LEFT);
      break;
    }
  }
}


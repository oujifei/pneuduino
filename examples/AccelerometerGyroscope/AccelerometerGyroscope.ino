#include <PneuDuino.h>

// include the library for the sensor
// https://github.com/Seeed-Studio/Accelerometer_And_Gyroscope_LSM6DS3
#include <SparkFunLSM6DS3.h>

PneuDuino p;

// declare the variable for the accelerometer/gyroscope motion sensor
LSM6DS3 motion(I2C_MODE, 0x6A); 


void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);

  // initialize the motion sensor
  if(motion.begin() != 0) {
    Serial.println("Motion sensor error");
  }
}

// whenever we turn the valve on, we hold it for a short duration
// this prevents valves from rapidly turning on/off
unsigned long on_time;
unsigned long hold_time = 100L;

void loop() {
  p.update();

  // read data from the sensor
  float x = motion.readFloatGyroX();
  float y = motion.readFloatGyroY();
  float z = motion.readFloatGyroZ();

  // if we detect motion of a large magnitude
  if(abs(x) + abs(y) + abs(z) > 1000) {
    // turn valve on
    p.in(1, LEFT);
    // reset the on time
    on_time = millis();
  }
  
  // no significant motion was detected
  else {
    // if enough time elapsed, turn valve off
    if(millis() - on_time > hold_time) {
      p.out(1, LEFT);
    }
  }
}



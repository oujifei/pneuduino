// this code will only run if we are trying to set a new address
#ifdef SET_BLINKM_ADDRESS

#include <Wire.h>

void setup() {
  // initialize I2C as master
  Wire.begin();

  // broadcast to all (address 0)
  Wire.beginTransmission(0);

  // send the 'A' (new address) command
  Wire.write('A');

  // send the new address
  Wire.write(LED_ADDRESS);

  // send the two verification values (refer to BlinkM LED datasheet)
  Wire.write(0xd0);
  Wire.write(0x0d);

  // send the address again
  Wire.write(LED_ADDRESS);

  // done
  Wire.endTransmission();

  // retreive and print address
  delay(100);
  
  while(!Serial) ;
  Serial.println("Address:");
  
  Wire.beginTransmission(LED_ADDRESS);
  Wire.write('a');
  Wire.endTransmission();
  
  Wire.requestFrom(LED_ADDRESS, 1);
  Serial.println(Wire.read());
}

void loop() {
  // do nothing here
}

#endif


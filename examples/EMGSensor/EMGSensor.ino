#include <PneuDuino.h>
#include <Wire.h>

PneuDuino p;

// I2C ADC
// http://wiki.seeedstudio.com/Grove-I2C_ADC/
#define ADDR_ADC121             0x50
#define REG_ADDR_RESULT         0x00
#define REG_ADDR_CONFIG         0x02

// code to read the I2C ADC
// http://wiki.seeedstudio.com/Grove-I2C_ADC/
int read_adc()
{
  int data;

  Wire.beginTransmission(ADDR_ADC121);        // transmit to device
  Wire.write(REG_ADDR_RESULT);                // get result
  Wire.endTransmission();

  Wire.requestFrom(ADDR_ADC121, 2);           // request 2byte from device
  delay(1);
  if(Wire.available()<=2)
  {
    data = (Wire.read()&0x0f)<<8;
    data |= Wire.read();
  }

  return data;
}

// timing data
unsigned long turn_off_time;

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);
}

void loop() {
  p.update();

  // read the ADC
  int reading = read_adc();
  Serial.println(reading);

  // get the time
  unsigned long m = millis();

  // in a resting state the sensor reads around 900-1000
  // set a threshold slightly above (adjust if necessary)
  int threshold = 1100;
  
  // if the sensor has detected EMG
  if(reading > threshold && m > turn_off_time) {
    // turn on valve and reset time
    p.in(1, LEFT);
    turn_off_time = m + 500L;
  }

  // no detection
  else {
    // if enough time has elapsed, turn off valve
    if(millis() > turn_off_time) {
      p.out(1, LEFT);
    }
  }
}


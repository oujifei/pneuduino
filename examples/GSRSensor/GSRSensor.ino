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

// make 10 readings and return the average
int read_average()
{
  int sum = 0;
  for(int i=0; i<10; i++) {
    sum += read_adc();
  }
  return sum / 10;
}

// minimum and maximum observed readings
int min_reading, max_reading;

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);

  // set min and max
  int reading = read_average();
  int min_reading = reading - 1;
  int max_reading = reading + 1;
}

void loop() {
  p.update();

  // read the ADC
  int reading = read_average();

  // print reading for Arduino serial plotter
  Serial.println(reading);

  // set minimum and maximum
  if(reading < min_reading) min_reading = reading;
  if(reading > max_reading) max_reading = reading;

  // scale to pressure
  int pressure = map(reading, max_reading, min_reading, 60, 90);
  p.setPressure(1, pressure);
}


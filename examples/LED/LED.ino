// I2C address of the BlinkM MaxM LED driver
#define LED_ADDRESS 13

#undef SET_BLINKM_ADDRESS
// uncomment this line to tell the led to set a new address instead of running the regular code
//#define SET_BLINKM_ADDRESS

// the code below will only run if we aren't trying to set a new address
#ifndef SET_BLINKM_DDRESS

#include <Wire.h>
#include <PneuDuino.h>

PneuDuino p;

// the RGB values for the current LED color
int r, g, b;


// generate a random color
void randomColor()
{
  // generate three random values 0-255
  int rand_r = random(256);
  int rand_g = random(256);
  int rand_b = random(256);

  // normalize so that max is always 255
  int max_rgb = max(rand_r, max(rand_g, rand_b));
  float scale = 255.0 / (float)max_rgb;

  // store values
  r = (int)(scale * rand_r);
  g = (int)(scale * rand_g);
  b = (int)(scale * rand_b);
}

// send command to LED
void setLED(int brightness)
{
  // scale to brightness
  float scale = (float)brightness / 255.0;
  uint8_t red = (uint8_t)(scale * r);
  uint8_t grn = (uint8_t)(scale * g);
  uint8_t blu = (uint8_t)(scale * b);
  
  // send data over I2C
  Wire.beginTransmission(LED_ADDRESS);
  Wire.write('n');
  Wire.write(red);
  Wire.write(grn);
  Wire.write(blu);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(9600);

  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);

  // begin I2C transmission to communicate with LED
  Wire.begin();

  // seed the RNG with analog noise
  randomSeed(analogRead(0));
}


void loop() {
  p.update();

  // the pressure at which we turn on LEDs
  int pressure_threshold = 70;

  // the current pressure
  int pressure = p.readPressure(1);

  // pressure below threshold
  if(pressure < pressure_threshold) {
    // maintain pressure slightly below threshold
    p.setPressure(1, pressure_threshold - 5);

    // turn off LED and save a random color
    setLED(0);
    randomColor();
  }

  // inflatable was squeezed, pressure risen above threshold
  else {
    // stop air from entering or exiting
    p.hold(1);

    // convert pressure reading to brightness
    int brightness = map(pressure, pressure_threshold, 80, 0, 255);
    brightness = constrain(brightness, 0, 255);

    // send brightness to LED
    setLED(brightness);
  }
}

#endif


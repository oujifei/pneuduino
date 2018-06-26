#include <PneuDuino.h>
#include <Wire.h>

PneuDuino p;


// read the heart rate sensor
// http://wiki.seeedstudio.com/Grove-Finger-clip_Heart_Rate_Sensor_with_shell/
unsigned long last_sensor_read;
int last_heart_rate;
int read_heart_rate()
{
  // return old value if reading too frequently
  if(millis() < last_sensor_read + 500L) {
    return last_heart_rate;
  }
  
  unsigned char c;
  Wire.requestFrom(0xA0 >> 1, 1);    // request 1 bytes from slave device
  while(Wire.available()) {          // slave may send less than requested
    c = Wire.read();                 // receive heart rate value (a byte)
    //Serial.println(c, DEC);          // print heart rate value (optional)
  }
  
  last_sensor_read = millis();
  last_heart_rate = (int)c;
  return last_heart_rate;
}

// timing data
unsigned long start_time;

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);
}

void loop() {
  p.update();

  int heart = read_heart_rate();

  // no heartbeat detected yet
  if(heart == 0) {
    p.out(1, LEFT);
  }

  // heartbeat has been detected
  else {
    // convert heart rate to milliseconds duration
    unsigned long heartbeat_length = 60000L / heart;

    // get current time
    unsigned long m = millis();

    // new pulse
    if(m > start_time + heartbeat_length) {
      p.in(1, LEFT);
      start_time = m;
    }

    // end of current pulse
    if(m > start_time + 100L) {
      p.out(1, LEFT);
    }
  }

  delay(100);
}


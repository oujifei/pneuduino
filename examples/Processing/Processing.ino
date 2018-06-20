#include <PneuDuino.h>

PneuDuino p;

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);

  // decrease the serial timeout to make commands more responsive
  Serial.setTimeout(100);

  // wait for serial connection to be established before proceeding
  while(!Serial) ;

  // output text to show on computer
  Serial.println("Type 'inflate' to turn valve on");
  Serial.println("Type 'deflate' to turn valve off");
}


void loop() {
  p.update();

  // if we have serial data to read
  if(Serial.available()) {
    // read in a single line
    String cmd = Serial.readStringUntil('\n');

    // received "inflate"
    if(cmd.equals("inflate")) {
      // turn valve on
      p.in(1, LEFT);
    }

    // received "deflate"
    if(cmd.equals("deflate")) {
      // turn valve off
      p.out(1, LEFT);
    }
  }
}


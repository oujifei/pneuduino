#include <PneuDuino.h>

PneuDuino p;

// define the states for our program
enum state {
  INFLATING,
  HOLDING,
  DEFLATING,
};

int current_state = DEFLATING;
bool prev_button = false;

void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);
}

void loop() {
  p.update();

  // read the button
  bool button = p.readButton(0);

  // if the button is now pressed, and wasn't previously pressed
  if(button && !prev_button) {
    // change state depending on current state
    switch(current_state) {
    case INFLATING:
      p.hold(1);
      current_state = HOLDING;
      break;
    case HOLDING:
      p.deflate(1);
      current_state = DEFLATING;
      break;
    case DEFLATING:
      p.inflate(1);
      current_state = INFLATING;
      break;
    }
  }

  // set previous state for the next loop iteration
  prev_button = button;
}

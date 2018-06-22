#include <PneuDuino.h>

PneuDuino p;


// to prevent rapidly switching valves, we only run in intervals
unsigned long time_interval = 50L;
unsigned long last_run;


// the state of our valve
enum valve_states {
  INFLATING,
  HOLDING,
  DEFLATING,
};
int valve_state = DEFLATING;


void setup() {
  Serial.begin(9600);
  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);
}


void loop() {
  p.update();

  // if enough time has passed to run again
  if(millis() > last_run + time_interval) {
    // read the potentiometer
    int pot = p.readPot();
    
    // read the actual pressure
    int pressure = p.readPressure(1);
  
    // set the target pressure as a function of pot position
    int target = map(pot, 0, 63, 60, 90);

    // adjust valve state depending on pressure
    if(valve_state == HOLDING && pressure > target + 1) {
      // pressure too high, go from holding to deflating
      p.deflate(1);
      valve_state = DEFLATING;
    }
    if(valve_state == INFLATING && pressure > target) {
      // pressure too high, go from inflating to holding
      p.hold(1);
      valve_state = HOLDING;
    }
    if(valve_state == DEFLATING && pressure < target) {
      // pressure too low, go from deflating to holding
      p.hold(1);
      valve_state = HOLDING;
    }
    if(valve_state == HOLDING && pressure < target - 1) {
      // pressure too low, go from holding to inflating
      p.inflate(1);
      valve_state = INFLATING;
    }

    // reset last run
    last_run = millis();
  }  
}


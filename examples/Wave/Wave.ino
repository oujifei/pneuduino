#include <PneuDuino.h>

PneuDuino p;

// number of valve boards
#define N 2


// length of the wave cycle
unsigned long cycle_length = 1000L;
// time that the most recent cycle began
unsigned long cycle_start_time;

// times to turn on/off each valve
unsigned long on_times[2*N];
unsigned long off_times[2*N];

// duration to keep each valve on
unsigned long on_duration = 100L;


void setup() {
  Serial.begin(9600);

  p.begin();
  p.setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL);
}


void loop() {
  p.update();

  // get the current time
  unsigned long m = millis();

  // cycle is over, reset everything for the next cycle
  if(m > cycle_start_time + cycle_length) {
    // loop through all 2*N valves
    for(int n=0; n<2*N; n++) {
      on_times[n] = m + (n*cycle_length / (2*N));
      off_times[n] = on_times[n] + on_duration;
    }

    // loop through all N valve boards
    // turn off all valves (indexed from 1, not 0)
    for(int n=0; n<N; n++) {
      p.out(n+1, LEFT);
      p.out(n+1, RIGHT);
    }

    // reset cycle start time
    cycle_start_time = m;
  }

  // loop through all N valve boards
  for(int n=0; n<N; n++) {
    // if turn on time is reached, open the valve
    if(m > on_times[2*n])
      p.in(n+1, LEFT);
    if(m > on_times[2*n + 1])
      p.in(n+1, RIGHT);

    // if turn off time is reached, close the valve
    if(m > off_times[2*n])
      p.out(n+1, LEFT);
    if(m > off_times[2*n + 1])
      p.out(n+1, RIGHT);
  }
}


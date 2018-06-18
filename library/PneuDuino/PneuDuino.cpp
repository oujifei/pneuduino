/***************************************************

 ****************************************************/

#include <PneuDuino.h>
#include <Wire.h>
#include "avr/interrupt.h"

#if defined(__AVR__)
 #define WIRE Wire
#elif defined(CORE_TEENSY) // Teensy boards
 #define WIRE Wire
#else // Arduino Due
 #define WIRE Wire1
#endif

// Set to true to print some debug messages, or false to disable them.
#define DEBUG false


PneuDuino::PneuDuino()
{
}

void PneuDuino::begin(void)
{
  pinMode(LED, OUTPUT);
  pinMode(CONNECT_BTN, INPUT_PULLUP);

  leds.begin();  // initialize LED driver
  leds.setPWMFreq(1600);  // maximum PWM frequency
  setAllLEDs(0);

  Wire.begin(); // join the I2C Bus as Master
}

void PneuDuino::update()
{
  // nothing connected
  if(getNodeAmount() == 0){
    digitalWrite(LED, HIGH);
    scanNodes();
    delay(500);
    return;
  }
  digitalWrite(LED, LOW);

  // connect button pressed
  if ( !digitalRead(CONNECT_BTN) ){
    digitalWrite(LED, HIGH);
    while ( !digitalRead(CONNECT_BTN) ) ;
    reset();
    scanNodes();
  }

  // go through all available nodes, read sensors and write state
  checkNodes();
}

void PneuDuino::setAddressMode(int mode)
{
  address_mode = mode;
  setAllLEDs(0);

  // addresses map to themselves
  if(address_mode == PNEUDUINO_ADDRESS_PHYSICAL) {
    for(int i=0; i<=12; i++) {
      address_map[i] = i;
    }
    setAllLEDs(4095);
    delay(500);
    setAllLEDs(0);
  }

  // address map will be made when nodes are added
  // flash leds to indicate virtual addresses
  if(address_mode == PNEUDUINO_ADDRESS_VIRTUAL) {
    for(int i=0; i<=16; i++) {
      // setLED ignores out-of-range LEDs
      setLED(i,   4096);
      setLED(i-1, 2048);
      setLED(i-2, 1024);
      setLED(i-3,  512);
      setLED(i-4,    0);
      delay(40);
    }
  }

  scanNodes();
}


//
// Two-state operation
//

// activate valve at address and side
void PneuDuino::in(int address, int side)
{
  address = address_map[address];
  // update valves_new with new state
  valves_new[address] = valves_new[address] | side;
}

// deactivate valve at address and side
void PneuDuino::out(int address, int side)
{
  address = address_map[address];
  // update valves_new with new state
  valves_new[address] = valves_new[address] & (~side);
}



//
// Three-state operation
//

void PneuDuino::inflate(int address)
{
  address = address_map[address];
  valves_new[address] = INFLATE;
  set_pressure[address] = -1;
}

void PneuDuino::deflate(int address)
{
  address = address_map[address];
  valves_new[address] = DEFLATE;
  set_pressure[address] = -1;
}

void PneuDuino::hold(int address)
{
  address = address_map[address];
  valves_new[address] = HOLD;
  set_pressure[address] = -1;
}

void PneuDuino::setPressure(int address, int pres)
{
  address = address_map[address];
  set_pressure[address] = pres;
}

void PneuDuino::setPressure(int address)
{
  address = address_map[address];
  set_pressure[address] = pressure[address];
}


//
// Sensors
//
int PneuDuino::readPressure(int address)
{
  address = address_map[address];
  if (nodes[address] == 0) return -1;
  //if (getState(address) == "HOLD") return pressureHACK;
  return pressure[address];
}

bool PneuDuino::readButton(int number)
{
  if (nodes[12] == 0) return 0;
  if (number == 0) return !io_btn2;
  if (number == 1) return !io_btn1;
  return 0;
}

int PneuDuino::readPot()
{
  if (nodes[12] == 0) return -1;
  return io_pot;
}

int PneuDuino::getNodeAmount()
{
  int amount = 0;
  for(int i = 1; i <= 12; i++){
    if (nodes[i] == 1) amount++;
  }
  return amount;
}


/***************
     PRIVATE
 ***************/

void PneuDuino::setLED(int pos, int value)
{
  value = constrain(value, 0, 4095);
  pos--;
  if(pos < 0 || pos > 11) return;
  leds.setPWM(LEDmap[pos], 0, value);
}

void PneuDuino::setAllLEDs(int value)
{
  for(int i = 1; i <= 12; i++){
    leds.setPWM(LEDmap[i], 0, value);
  }
}

void PneuDuino::checkNodes(void)
{
  // this is where to distinguish between IO and valve. send different requests accordingly.
  // for the 11 valves
  for (int i = 1; i <= 11; i++) {
    // nothing is connected
    if (! nodes[i]) continue;

    // make request
    Wire.requestFrom(i, 1);

    // if it got disconnected
    if (!Wire.available()) {
      scanNodes();
      return;
    }

    // read data
    while (Wire.available()) {
      pressure[i] = int( Wire.read() );
    }

    if(millis() > last_pressure + PRESSURE_REGULATION_INTERVAL) {
      // if pressure set, adjust pressure
      if(set_pressure[i] > 0) {
        // hold to deflate
        if(valves_new[i] == HOLD && pressure[i] > set_pressure[i] + PRESSURE_RANGE) {
          valves_new[i] = DEFLATE;
        }
        // inflate to hold
        else if(valves_new[i] == INFLATE && pressure[i] >= set_pressure[i] + PRESSURE_RANGE) {
          valves_new[i] = HOLD;
        }
        // deflate to hold
        else if(valves_new[i] == DEFLATE && pressure[i] <= set_pressure[i] - PRESSURE_RANGE) {
          valves_new[i] = HOLD;
        }
        // hold to inflate
        else if(valves_new[i] == HOLD && pressure[i] < set_pressure[i] - PRESSURE_RANGE) {
          valves_new[i] = INFLATE;
        }
      }
      last_pressure = millis();
    }

    // write data if it has changed
    if(valves_new[i] != valves[i]) {
      // update valves to match valves_new
      valves[i] = valves_new[i];
      //       on off
      //  left L  K
      // right R  E
      //  both B  N
      Wire.beginTransmission(i);
      switch(valves[i]) {
      case BOTH:
          Wire.write('B');
          break;
      case LEFT:
          Wire.write('L');
          Wire.endTransmission(false);
          Wire.beginTransmission(i);
          Wire.write('E');
          break;
      case RIGHT:
          Wire.write('R');
          Wire.endTransmission(false);
          Wire.beginTransmission(i);
          Wire.write('K');
          break;
      default:
          Wire.write('N');
          break;
      }
      Wire.endTransmission();
    }
  }

  // check for 1 allowed IO board
  if ( nodes[12] == 1 ) {
    Wire.requestFrom(12, 1);

    // if it got disconnected
    if (!Wire.available()) {
      scanNodes();
      return;
    }

    // read data
    while (Wire.available()) {
      byte inByte = byte( Wire.read() );
      io_btn1 = bitRead(inByte, 0);
      io_btn2 = bitRead(inByte, 1);
      io_pot = (int)(inByte >> 2);
    }
  }
}


void PneuDuino::scanNodes()
{
  if (DEBUG) Serial.println("Check for devices");

  int virtual_address = 1;

  for (int address = 1; address <= 12; address++) {
    Wire.requestFrom(byte(address), 1);

    // nothing is connected
    if (!Wire.available()) {
      nodes[address] = 0;

      // set LED
      if(address == 12 || address_mode == PNEUDUINO_ADDRESS_PHYSICAL) {
        setLED(address, 0);
      } else {
        setLED(virtual_address, 0);
      }

      if (DEBUG) Serial.print(address);
      if (DEBUG) Serial.println(" : nope.");
    }

    // something is connected
    else {
      nodes[address] = 1;

      // read out data
      while (Wire.available()) {
        int temp = int( Wire.read() );
      }

      // set LED
      if(address == 12 || address_mode == PNEUDUINO_ADDRESS_PHYSICAL) {
        setLED(address, 4095);
      } else {
        setLED(virtual_address, 4095);
      }

      // if we're using virtual addresses
      if(address != 12 && address_mode == PNEUDUINO_ADDRESS_VIRTUAL) {
        address_map[virtual_address] = address;
        virtual_address += 1;
      }

      if (DEBUG) Serial.print(address);
      if (DEBUG) Serial.println(" yup");
    }
  }
}

void PneuDuino::reset()
{
  for (int i = 0; i <= 12; i++)
  {
    nodes[i] = 0;
    pressure[i] = 0;
    setAllLEDs(0);
  }

  io_btn1 = false;
  io_btn2 = false;
  io_pot = -1;
}




/****************************
 * THINGS TO BE IMPLEMENTED *
 ****************************/
/*

bool PneuDuino::checkTouch(int address)
{
  if (nodes[address] == 0) return false;
  return touched[address];
}

 String PneuDuino::getState(int address)
{
  if (nodes[address] == 0) return "X";
  if (states[address] == 'X') return "NC";
  if (states[address] == 'I') return "INFLATE";
  if (states[address] == 'D') return "DEFLATE";
  if (states[address] == 'H') return "HOLD";
  if (states[address] == 'R') return "OPEN";
  return "ERROR";
}
*/

/*
void PneuDuino::hold(int address, int side)
{
  if (nodes[address] != 1) return;

  byte b = 'H';
  Wire.beginTransmission(address);
  Wire.write(b);
  Wire.endTransmission();
}

void PneuDuino::clear(int address, int side)
{
  if (nodes[address] != 1) return;

  byte b = 'R';
  Wire.beginTransmission(address);
  Wire.write(b);
  Wire.endTransmission();
}
*/
/*
void PneuDuino::recalibrate(int address)
{
  if (nodes[address] != 1) return;

  byte b = 'C';
  Wire.beginTransmission(address);
  Wire.write(b);
  Wire.endTransmission();
}


void PneuDuino::inflate(int address, int pressure)
{
  if (nodes[address] != 1) return;
  //pressureHACK = pressure;

  byte b = 'P';
  byte p = byte(pressure);
  Wire.beginTransmission(address);
  Wire.write(b);
  Wire.write(p);
  Wire.endTransmission();
}
*/

/*
PneuDuino::reset()
{

}
*/

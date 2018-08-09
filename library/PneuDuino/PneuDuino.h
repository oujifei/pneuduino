/***************************************************
  This is a library for the PneuDuino Modules.
  It facilitates easy control of inflatable actuators and interactive pneumatic systems.

  It includes the Adafruit 16-channel PWM & Servo driver
 ****************************************************/

#ifndef _PneuDuino_h
#define _PneuDuino_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "Arduino.h"
#include "Adafruit-PWM-Servo-Driver-Library/Adafruit_PWMServoDriver.h"
#include "Adafruit_ADS1X15/Adafruit_ADS1015.h"

#define LED 13
#define CONNECT_BTN 0

#define LEFT 1
#define RIGHT 2
#define BOTH (LEFT | RIGHT)
#define INFLATE LEFT
#define HOLD RIGHT
#define DEFLATE 0

#define PNEUDUINO_ADDRESS_PHYSICAL 0
#define PNEUDUINO_ADDRESS_VIRTUAL  1

#define PRESSURE_MAX 255
#define PRESSURE_RANGE 1
#define PRESSURE_REGULATION_INTERVAL 50L

class PneuDuino {
public:
  // Constructor
  PneuDuino();

  // Call this function once in setup()
  void begin(void);

  // Call this function once in loop()
  void update(void);

  // Change between physical and virtual addresses
  // setAddressMode(PNEUDUINO_ADDRESS_PHYSICAL) 
  // setAddressMode(PNEUDUINO_ADDRESS_VIRTUAL)
  void setAddressMode(int mode);

  // Two-state operation: turn a single valve on or off
  // In the on state, the output is connected to the pressure supply
  // In the off state, the output is connected to exhaust
  // side is either LEFT or RIGHT
  void in(int address, int side);
  void out(int address, int side);

  // Three-state operation: use two valves on a board together
  // Inflate: output connected to pressure supply
  // Hold: output not connected to anything (air cannot enter or leave)
  // Deflate: output connected to exhaust
  void inflate(int address);
  void deflate(int address);
  void hold(int address);

  // Pressure regulation: Automatically inflate, deflate, or hold to maintain a set pressure
  // A reasonable range of pressures is from 60 to 90
  // Calling setPressure with just the address sets the target pressure to the current pressure
  // Calling one of inflate, deflate, or hold ends automatic pressure regulation
  void setPressure(int address, int pres);
  void setPressure(int address);

  // Pressure sensor: returns pressure as integer between 0 and 255
  // Reasonable pressures range from 60 (roughly atmospheric) to 90 (roughly the upper limit for inflatables)
  int readPressure(int address);

  // Button: returns true when pressed
  // For a single-button board, the button number is 0 (zero)
  bool readButton(int number = 0);

  // Potentiometer: returns its position
  // Values range from 0 (leftmost) to 63 (rightmost)
  int readPot();

  // Analog sensor: ANALOG_0 and ANALOG_1 ports on sensor board
  // Each analog port has two channels:
  //    A0 and A1 on ANALOG_0
  //    A2 and A3 on ANALOG_1
  // readAnalog reads the default channel (A0 or A2). Use this for most Grove sensors.
  // readAnalogRaw directly returns the reading for A0, A1, A2, A3
  // readAnalogDifferential reads the difference between the 2 channels on a port.
  unsigned int readAnalog(int number);
  unsigned int readAnalogRaw(int number);
  int readAnalogDifferential(int number);
  void setAnalogAddressJumper(bool state);

  // Returns the number of extension boards connected
  int getNodeAmount();

private:
  void reset(void);


/*
 * TO BE IMPLEMENTED:

  void hold(int address, int side);
  void clear(int address, int side);
  void inflate(int address, int pressure);
  bool checkTouch(int address);
  String getState(int address);
  void recalibrate(int address);
*/



 private:
  Adafruit_ADS1015 adc;

  Adafruit_PWMServoDriver leds;
  int LEDmap[12] = {8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7};

  int nodes[13]      = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int valves[13]     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int valves_new[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  int pressure[13]     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int set_pressure[13] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  unsigned long last_pressure;

  bool touched[13] =  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char states[13] = {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'} ;

  int address_mode = PNEUDUINO_ADDRESS_PHYSICAL;
  int address_map[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  void setLED(int pos, int value);
  void setAllLEDs(int value);

  void checkNodes(void);
  void scanNodes(void);

  bool io_btn1 = false;
  bool io_btn2 = false;
  int io_pot = -1;

 };

#endif

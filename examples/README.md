# Pneuduino Examples
The following examples demonstrate the functionality of Pneuduino.

## Table of Contents

* Introductory Examples
    These examples aim to teach the basic functions of the Pneuduino library.
    * [01 Physical and Virtual Addresses](./PhysicalVirtualAddresses)
    * [02 Valve On/Off](./ValveOnOff)
    * [03 Read Pressure](./ReadPressure)
    * [04 Read Potentiometer and Button](./ReadPotButton)
    * [05 Three-state Operation](./ThreeState)
    * [06 Pressure Regulation](./PressureRegulator)
* Using Sensors
    Pneuduino can interface with sensors to dynamically respond to user input and environmental changes.
    * [07 I2C Gesture Sensor](./GestureSensor)
    * [08 I2C Accelerometer and Gyroscope](./AccelerometerGyroscope)
    * [09 Serial IO with Computer](./SerialIO)
* Pneumatic Logic and Circuits
    Pneumatic logic uses air pressure to convey information. Pneuduino can be programmed to emulate logic gates and circuits. TBD.
    * [NOT Gate](#not-gate)
    * [AND Gate](#and-gate)
    * [OR Gate](#or-gate)
    * [XOR Gate](#xor-gate)
* Advanced Examples
    These examples combine multiple features and showcase more complex capabilities of Pneuduino. TBD.
    * [Haptic](#haptic)
    Haptic (vibration) feedback is usually done with rotating motors. However, it is possible to achieve a more natural effect by rapidly inflating and exhausting air.
    * [Wave](#wave)
    In this example, we demonstrate how to inflate and deflate a row of inflatables in sequence. This style of motion can be applied to propel &quot;crawling&quot; pneumatic robots.
    * [Pressure Regulator v2](#pressure-regulator-v2)
    In this example, we explore and implement the pressure regulation feature in the Pneuduino library.


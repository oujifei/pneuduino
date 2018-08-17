## Pneuduino Sensor Hub
**Boards:** Master, valve board, and sensor hub board</br>
**Tube connections:** Same as the [Pressure Regulation](../PressureRegulator) example

The new Pneuduino sensor hub allows both I2C and analog sensors to be plugged into the same board. On the board's top, there are two identical I2C ports. On the board's bottom, there are two analog ports labeled `ANALOG_0` and `ANALOG_1`. The I2C ports function the same as those on the Grove extension board. The analog ports are connected to an onboard [ADS1015 ADC](https://www.adafruit.com/product/1083). With the sensor hub, the Grove I2C ADC used in previous examples is no longer necessary.

With the Grove I2C ADC, it was necessary to copy the code to read it into your program. However, the code to read analog sensors connected directly to the sensor hub is included in the latest version of the Pneuduino library. The `readAnalog` function takes in the port number (0 or 1) and returns the analog reading as an unsigned integer from zero to 4096. This function is appropriate for virtually all Grove analog sensors.

The example code here is the same as the previous [Light Sensor](../LightSensor) example, except the sensor hub is used in place of the Grove I2C ADC. Connect the light sensor to `ANALOG_0`, leave the `ADDR_SEL` pins disconnected, and upload the code to the Pneuduino master board. In `loop()`, the reading from the sensor (ranging from roughly zero to 1666) is mapped to a range of common pressures for inflatables. As this example sets pressure using the library's automatic pressure regulation functionality, connect tubing in the same manner as in the Pressure Regulation example. Expose the sensor to bright light, and the inflatable will be inflated firmly. Dim the light, and the inflatable will become softer. Cover up the sensor, and pressure will be released.

### Further information
For more advanced usage, the library provides functions exposing some of the more low-level capabilities of the ADC hardware. The ADS1015 supports four single-ended channels or two differential pairs. Thus, each analog port on the sensor hub actually has two independent analog channels. (Grove sensors only use one of these two channels, and `readAnalog` will read this channel.) The `readAnalogDifferential` function takes a port number (0 or 1) and returns the voltage difference between its two channels as a signed integer.  The `readAnalogRaw` function takes an ADS1015 channel number and returns its analog reading.

The ADS1015 has its own I2C address (`0x48`), which is used for communicating with the Pneuduino library. However, this address may conflict with the address of a sensor plugged into an I2C port. In this situation, it is possible to change the ADS1015's address to `0x49` by connecting the two `ADDR_SEL` pins with a jumper (the default state is to leave the pins disconnected). Before making any analog readings, call the `setAnalogAddressJumper` function with the state of the jumper (`true` if jumper is present, `false` if the jumper was removed).



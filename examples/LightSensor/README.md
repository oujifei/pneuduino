## Light Sensor
**Boards:** Master, valve board, Grove extension board, and Grove I2C ADC</br>
**Tube connections:** Same as the [Pressure Regulation](../PressureRegulator) example

Pneuduino's Grove extension board allows for Grove I2C sensors to be plugged in, but analog sensors can also be used via the [Grove I2C ADC](http://wiki.seeedstudio.com/Grove-I2C_ADC/). In this example, we read analog values from the Light Sensor and use them to control the pressure of an inflatable.

The code to read the ADC can be found on the device's wiki page, linked above. In `loop()`, the reading (ranging from roughly zero to 2400) is mapped to a range of common pressures for inflatables. As this example sets pressure using the library's automatic pressure regulation functionality, connect tubing in the same manner as in the Pressure Regulation example. Expose the sensor to bright light, and the inflatable will be inflated firmly. Dim the light, and the inflatable will become softer. Cover up the sensor, and pressure will be released.


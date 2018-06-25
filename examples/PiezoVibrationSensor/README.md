## Piezo Vibration Sensor
**Boards:** Master, valve board, Grove extension board, and Grove I2C ADC</br>
**Tube connections:** Same as the [Gesture Sensor](../GestureSensor) example

The Piezo Vibration Sensor is very similar to the Collision Sensor. It detects if the piezoelectric material in the sensor attachment has been bent, impacted, or deformed in any manner. The sensor has an onboard potentiometer that can be used to adjust its sensitivity.

Like the Collision Sensor, we read this sensor through the Grove I2C ADC. However, this sensor gives a high signal on a positive reading, so we instead test if our reading is above the threshold. Try out this sensor, and try changing both the threshold in the code and potentiometer in the hardware. Compare it to the Collision Sensor, and see if you find it better or not.


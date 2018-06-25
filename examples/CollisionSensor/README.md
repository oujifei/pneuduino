## Collision Sensor
**Boards:** Master, valve board, Grove extension board, and Grove I2C ADC</br>
**Tube connections:** Same as the [Gesture Sensor](../GestureSensor) example

The Collision Sensor is another example of a sensor that can be read through the Grove I2C ADC. It detects if something has collided into the sensor and is sensitive to taps, bumps, and shakes. The code for this example is very similar to that of the Sound Sensor example. We read the sensor through the ADC, and we compare the reading against a threshold. However, note that this sensor pulls the analog line low when a positive reading is detected, meaning that we must test to see if our reading is below the threshold. Upload the code and try out the sensor. Adjust the threshold, and observe what happens.


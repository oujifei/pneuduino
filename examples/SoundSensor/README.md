## Sound Sensor
**Boards:** Master, valve board, Grove extension board, and Grove I2C ADC</br>
**Tube connections:** Same as the [Gesture Sensor](../GestureSensor) example

Like the [Light Sensor](../LightSensor), the Sound Sensor is also an analog sensor that can be read through the Grove I2C ADC. In this example, we bring together elements of the Touch Sensor and Light Sensor examples. We compare analog readings against a discrete cutoff, triggering an event (inflating for a brief amount of time) whenever a sufficiently strong reading is observed.

The code to read the ADC for this example is identical to that for the Light Sensor example. However, the examples differ with what is done with the reading. Instead of mapping it continuously, we compare it against a threshold level, which was determined empirically. Upload this example to the Pneuduino master board, and observe what happens. Shout, clap, or tap on the sensor's microphone, and air will be inflated. Try adjusting the value of the threshold, and observe the resulting changes in behavior.


## EMG Sensor
**Boards:** Master, valve board, Grove extension board, and Grove I2C ADC</br>
**Tube connections:** Same as the [Gesture Sensor](../GestureSensor) example

The EMG Sensor is one of the more complicated analog sensors to use with Pneuduino. Like all analog sensors, it must be read through the Grove I2C ADC. This sensor detects the small electrical signals in human muscles and amplifies them to a readable analog voltage. Attach the sensor's electrodes to your arm, and run the example code. Relax your arm and hold still while the sensor's output settles. Now forcefully move your arm, and the sensor should trigger a positive reading. The EMG sensor is very sensitive and sometimes unstable. Adjusting the value of the threshold is likely to be necessary in order for this example to function properly.


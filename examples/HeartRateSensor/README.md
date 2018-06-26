## I2C Heart Rate Sensor
**Boards:** Master, valve board, and Grove extension board</br>
**Tube connections:** Same as the [Gesture Sensor](../GestureSensor) example

The Grove Finger-clip Heart Rate Sensor uses an optical sensor to measure heart rate. It communicates through an I2C interface and can easily be used with Pneuduino. In this example, we use the sensor to measure heart rate and then pulse an inflatable at the same rate.

Connect this sensor to the Grove extension board, and run the code. Place your finger against the sensor's green light and wait patiently. It will take several seconds for the sensor to detect a heartbeat. When a heartbeat is detected, the code converts the heart rate into the duration (in milliseconds) between beats. We send pulses of air to the inflatable at this rate, allowing you to physically see and feel your heartbeat.


## I2C Touch Sensor
**Boards:** Master, valve board, and Grove extension board</br>
**Tube connections:** Same as the [Gesture Sensor](../GestureSensor) example

The Grove I2C Touch Sensor is a multi-channel capacitive touch sensor that allows for easy tactile input and feedback. It is able to detect touch through thin surfaces, meaning that it can be placed inside an inflatable. In this example, we demonstrate how to use the touch sensor's library. After initializing in `setup()`, we update the sensor's state with a call to `getTouchState()`. The new data is written to the `touched` variable. When a touch on any channel is observed, `touched` will be non-zero. (To see the specific channel(s), the *n*-th bit will be set to `1` if the *n*-th channel is touched.) We open the valve for a brief amount of time whenever a touch is observed.


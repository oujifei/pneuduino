## 04 Read Potentiometer and Button
**Boards:** Master, valve board, and input board</br>
**Tube connections:** None

The Pneuduino input board contains a potentiometer and a button. This example shows how to read these input devices and use the input data to control valve operation. The potentiometer measures the knob&#39;s angular position, and `readPot()` returns an integer between 0 and 63. The button state can be retrieved with `readButton(0)`, which returns `true` when the button is pressed and `false` otherwise.

In this example, the left valve is pulse-width modulated at a period of 200ms. The potentiometer&#39;s position controls the width of the pulse, adjusting the proportion of time the valve is turned on. The right valve is actuated simply when the button is pressed.


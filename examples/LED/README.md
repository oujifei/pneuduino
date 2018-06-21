## BlinkM LED Driver
**Boards:** Master, valve board, and Grove extension board</br>
**Tube connections:** Connect tubes as in the [Pressure Regulation](../PressureRegulator) example.

The [BlinkM MaxM](https://www.sparkfun.com/products/9000) is a I2C LED driver that can control three large onboard LEDs or any common-anode RGB LED strip, with the option to use an external power input. In order to use the BlinkM MaxM, it is necessary to solder a Grove cable onto the board's input pins. Connect black to `-`, red to `+`, white to `d`, and yellow to `c`. Plug the other end of the cable into Pneuduino's Grove extension board.

The BlinkM MaxM has the ability to have its I2C address reset through an I2C command. The board's default address is 0x9, which conflicts with a Pneuduino valve board. In the example code, the `SET_BLINKM_ADDRESS` define can be used to create a program to reset the board's address. With a new BlinkM board, this address-setting program must be run once before the regular code can be used.

Every time `loop()` is run, the code for this example checks the pressure reading against a threshold pressure. If the pressure is below this threshold, we tell the Pneuduino library to continue maintaining a pressure slighly below the threshold. We turn off the LED and store a random color. When the inflatable is squeezed, the pressure will rise above the threshold. Now, we hold pressure and set the LED's brightness proportionally to the pressure. Thus, the LEDs brighten up the harder the inflatable is squeezed. When the inflatable is released, the pressure falls below the threshold, and the situation repeats.


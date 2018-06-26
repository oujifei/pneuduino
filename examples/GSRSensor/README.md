## GSR Sensor
**Boards:** Master, valve board, Grove extension board, and Grove I2C ADC</br>
**Tube connections:** Same as the [Pressure Regulator](../PressureRegulator) example

Like the EMG sensor, the GSR sensor also measures electrical properties of the human body. It is also one of the more complicated sensors to use with Pneuduino, and is read through the Grove I2C ADC. The GSR sensor measures the galvanic skin response, which correlates to the electrical resistance of the skin. The measured value changes depending on how firmly the electrodes are squeezed against your skin.

In this example, we use the value to set the pressure of our inflatable. Run the example, and open the Arduino serial plotter to display a graph of readings. Now pick up the electrodes and hold them gently one in each hand. If the electrodes are properly making contact with your skin, you should see a drop in the measured resistance. Now squeeze the electrodes between your fingers so that they are firmly pressed into your skin. The measured value should become lower. By varying how hard you squeeze, you should be able to change the pressure of the inflatable.


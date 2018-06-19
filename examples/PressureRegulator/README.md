## 06 Pressure Regulation
**Boards:** Master, valve board, and input board</br>
**Tube connections:** Connect tubes as shown below

 ![](../images/PressureRegulator.jpg)

The Pneuduino library has the ability to use the onboard pressure sensor as a software pressure regulator, automatically switching the valves to inflate, deflate, or hold as necessary to maintain a pressure. The tube connections for this feature are mostly the same as for the previous example, with the exception that the output tube goes to a T connector. One branch of the T connects to the inflatable, while the other branch connects to the pressure sensor.

When the code is run, the potentiometer&#39;s position is used to set the desired pressure. The Pneuduino library handles the control of the valves automatically. Best results are achieved with a larger inflatable, as a greater volume of air tends to result in a more stable pressure.


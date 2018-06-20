## AND Gate
**Boards:** Master and valve board</br>
**Tube connections:** Connect tubes as shown below

 ![](../images/NotAndGate.jpg)

The AND gate is a logic gate that takes two inputs, A and B. It outputs a `true` when both A and B are `true`. With pneumatic logic, a high pressure indicates `true` and a low pressure indicates `false`. As Pneuduino valve boards have pressure sensors, they can be programmed to open and close valves depending on an applied pressure. With the right code and tube connections, we can implement pneumatic logic gates.

For the AND gate, connect input A to the supply port of the left valve (clear tube in the above image). Connect input B to the pressure sensor (black tube in the image). Connect the left valve's output to the inflatable. Run the code, and connect both the A and B inputs to the compressed air supply. As both inputs are `true`, the output is `true` and air is sent to the inflatable. Disconnect any one of the inputs from the pressurized air, and the output will change to `false`.


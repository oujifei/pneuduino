## 02 Valve On/Off
**Boards:** Master and one valve board</br>
**Tube connections:** None

This example demonstrates how to actuate valves, while also showing the basic form of a Pneuduino program. In `setup()`, we call `begin` to initialize the library and `setAddressMode` to use virtual addresses. We run `update` each `loop()` to allow the library to process changes in state. The demo code here cycles valve states over four time increments of 500ms each.

Each valve on the Pneuduino valve board has three ports. From bottom to top, these are output, supply, and exhaust. Typically, the supply port is connected to a source of compressed air, and the exhaust port is left open to release air into the atmosphere. The `in` function places a valve in its &quot;on&quot; state, where the output port is connected to the supply port, and the exhaust port is blocked. Likewise, the `out` function places a valve in its &quot;off&quot; state, connecting output to exhaust and leaving supply blocked.


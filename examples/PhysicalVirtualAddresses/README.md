## 01 Physical and Virtual Addresses
**Boards:** Master, one valve board (preferably with a physical address not equal to 1)</br>
**Tube connections:** None

This example demonstrates the Pneuduino library&#39;s support for physical and virtual addresses. In physical address mode, functions in the library directly take in an extension board&#39;s hardware I2C address. Consequently, replacing an extension board with one of a different address requires a rewrite of the master board&#39;s code. To overcome this inconvenience, the Pneuduino library can map physical addresses to virtual addresses, and function calls automatically convert virtual address inputs to the hardware I2C addresses needed for communication. For any _n_ valve boards with distinct physical addresses, the virtual address system will map them to addresses 1 through _n_, with the lowest physical address mapped to 1, the second lowest mapped to 2, and so on.

Upload the code for this demo to the master board, and observe what occurs. First, the LEDs flash simultaneously, indicating physical address mode. The LED corresponding to the valve board&#39;s physical address remains lit. After a few seconds, the LEDs flash in sequence, indicating virtual address mode. Now, LED 1 will remain lit, as the board has been mapped to virtual address 1. A few seconds later, we switch back to physical addresses, and this process repeats indefinitely.


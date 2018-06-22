## Pressure Regulator v2
**Boards:** Master, valve board, and input board</br>
**Tube connections:** Same as in the [Pressure Regulator](../PressureRegulator) example.

In this example, we explore and implement the pressure regulation feature in the Pneuduino library. The general idea of software pressure regulation is to read the pressure with the pressure sensor, compare the reading against a desired value, and open/close valves as necessary to adjust the pressure. Hovever, many real-world complexities make this task harder than it appears.

Let's go through the example code. First, we set a `time_interval` for running the pressure regulation routine. Experiment with this value. Too short, and there will be high-frequency oscillations. Too long, and the pressure regulation will not be responsive. Next, we also note that our tube connections are made so that we have three states: inflating, holding, and deflating.

Take a look at `loop()`. When more time than `time_interval` has elapsed, we first determine our actual and desired (from potentiometer) pressure values. The core of the routine is composed of the four `if` statements, covering the four possible situations where the valve state needs to be changed. If we are holding pressure, and the observed pressure is too high or too low, we must deflate or inflate, respectively. This covers the first and last `if` statement. If we are inflating or deflating, and the pressure has passed the target value, we want to hold pressure. This covers the middle two `if` statements. Moreover, we want to require a greater discreptancy between actual and desired pressure to move out of the holding state than to move into the holding state. This, in essence, adds "stickiness" to the holding state, which helps to reduce oscillations. We don't want to always be stuck in a rapid inflate-hold-deflate-hold cycle.


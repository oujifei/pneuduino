## Haptic (Vibration) Feedback
**Boards:** Master, valve board, and input board</br>
**Tube connections:** Connect tubes as in the [Pressure Regulation](../PressureRegulator) example.

Haptic (vibration) feedback is usually done with rotating motors. However, it is possible to achieve a more natural effect by rapidly inflating and exhausting air. In this example, we implement such a feature, making an inflatable vibrate when it is squeezed.

Each individual vibration can be represented by an on time (where the valve is turned on and air flows in) and an off time (where the valve is turned off and air leaves). The vibration speed depends on the length of a on/off cycle. In this example, the potentiometer position is first used to set the vibration cycle duration. Normally, the program maintains the inflatable at a set pressure. When the inflatable is squeezed, the measured pressure rises, and the code to generate vibrations runs. Twist the potentiometer knob while the inflatable vibrates, and observe the change in vibration speed. Note that haptic feedback is most effective with smaller inflatables, as it takes less air volume to achieve a change in pressure.


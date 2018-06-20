## Facial Recognition with Processing.org
**Boards:** Master and valve board</br>
**Tube connections:** Same as previous example

With the ability to perform serial communication with a computer, all the hardware of a computer can be used as sensors for controlling air flow. This example uses the video stream from a typical laptop webcam for facial recognition, which is done with [Processing.org](https://www.processing.org/) and the [OpenCV library](https://github.com/atduskgreg/opencv-processing).

The Arduino code for this example is the same as that of the previous example. Pneuduino will respond to the `inflate` and `deflate` commands when sent over serial. Complementing this code is a Processing sketch that reads webcam video frames and calls OpenCV's facial detection algorithm. Depending on whether faces were detected, the appropriate serial command is sent to Pneuduino.

To run this example, first upload the Arduino code to the Pneuduino master board. Run the Processing sketch on a laptop, and a window will open that displays the image captured from the webcam. Make sure the Arduino serial monitor is not connected, because we must leave the serial port open for Processing to access it. Move your face into the webcam's field of view, and the inflatable will inflate. Move your face away, and it will deflate.


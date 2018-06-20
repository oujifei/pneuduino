// Based on Face It by Daniel Shiffman //<>//
// https://github.com/shiffman/Face-It/blob/master/OpenCV/LiveFaceDetect/LiveFaceDetect.pde


import processing.serial.*;
import processing.video.*;
import gab.opencv.*;
import java.awt.Rectangle;


// Serial port
Serial serial;

// Computer vision
OpenCV opencv;

// Camera capture
Capture cam;

// Array of faces found
Rectangle[] faces;

void setup() {
  // Open a window
  size(320, 240,P2D);
  
  // Start serial communication
  serial = new Serial(this, Serial.list()[0], 9600);
  
  // Start the camera
  cam = new Capture(this, 320, 240);
  cam.start();

  // Create the OpenCV object
  opencv = new OpenCV(this, cam.width, cam.height);
  
  // Load the data for face detection
  opencv.loadCascade(OpenCV.CASCADE_FRONTALFACE);      
}


// This is automatically run when a new video frame is available
void captureEvent(Capture cam) {
  cam.read();
}


void draw() {
  // Start with a black background
  background(0);
  
  // We have to always "load" the camera image into OpenCV 
  opencv.loadImage(cam);
  
  // Detect the faces
  faces = opencv.detect();
  
  // Draw the video frame onto the screen
  image(cam, 0, 0);

  // If we find faces, draw them!
  if (faces != null && faces.length > 0) {
    for (int i = 0; i < faces.length; i++) {
      strokeWeight(2);
      stroke(255,0,0);
      noFill();
      rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
    }
    
    // Send a command over to Pneuduino to inflate
    serial.write("inflate\n");
  }
  
  // No faces were found
  else {
    // Send a command over to Pneuduino to deflate
    serial.write("deflate\n");
  }
}

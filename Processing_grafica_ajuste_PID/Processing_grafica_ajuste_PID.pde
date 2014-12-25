/**
 * Many Serial Ports
 * 
 * Read data from the multiple Serial Ports
 */


import processing.serial.*;

Serial myPorts ;  // Create a list of objects from Serial class
float[] velDeseada0 = new float[900];         // a list to hold data from the serial ports
float[] velReal0 = new float[900];
float[] velEscribir0 = new float[900];
float[] velDeseada1 = new float[900];         // a list to hold data from the serial ports
float[] velReal1 = new float[900];
float[] velEscribir1 = new float[900];


void setup()  {
  size(1000, 500);
  // print a list of the serial ports:
  printArray(Serial.list());
  // On my machine, the first and third ports in the list
  // were the serial ports that my microcontrollers were 
  // attached to.
  // Open whatever ports ares the ones you're using.

// get the ports' names:
//  String portOne = Serial.list()[0];
//  String portTwo = Serial.list()[2];
  // open the ports:
  myPorts = new Serial(this, Serial.list()[1], 9600);
  myPorts.clear();
//   background(0);
//  myPorts[1] = new Serial(this, portTwo, 9600);
}


void draw() {
  // clear the screen:
 if (myPorts.available()>0){
//   while (myPorts.read()!='+');
   String a =myPorts.readStringUntil('\n');
   if ((a != null)&&(a.indexOf('+')==0)){
     println(a);
     for (int n=0;n<899;n++){
       velDeseada0[n]=velDeseada0[n+1];
       velReal0[n]=velReal0[n+1];
       velEscribir0[n]=velEscribir0[n+1];
       velDeseada1[n]=velDeseada1[n+1];
       velReal1[n]=velReal1[n+1];
       velEscribir1[n]=velEscribir1[n+1];
     }
     print(velEscribir0[899]=float(a.substring(a.indexOf('+'),a.indexOf(','))));
     print('\t');
     print(velReal0[899]=float(a.substring(a.indexOf(',')+1,a.indexOf('_'))));
     print('\t');
     print(velDeseada0[899]=float(a.substring(a.indexOf('_')+1,a.indexOf('>'))));
     print(velEscribir1[899]=float(a.substring(a.indexOf('+'),a.indexOf(','))));
     print('\t');
     print(velReal0[899]=float(a.substring(a.indexOf(',')+1,a.indexOf('_'))));
     print('\t');
     println(velDeseada0[899]=float(a.substring(a.indexOf('_')+1,a.indexOf('>'))));
   }
 }
 background(255);
 noFill();
 beginShape();
 for (int n=0;n<900;n++){
   stroke(255, 0, 0);
   curveVertex(n,500-velEscribir0[n]*2);
    }
 endShape();
 beginShape();
 for (int n=0;n<900;n++){
   stroke(0, 255, 0);
   curveVertex(n,500-velReal0[n]*45);
 }
 endShape();
 beginShape();
 for (int n=0;n<900;n++){
   stroke(0, 0, 255);
   curveVertex(n,500-velDeseada0[n]*45);
 }
endShape();
  // use the latest byte from port 0 for the first circle
//  fill(dataIn[0]);
//  ellipse(width/3, height/2, 40, 40);
    // use the latest byte from port 1 for the second circle
//   fill(dataIn[1]);
//  ellipse(2*width/3, height/2, 40, 40);
}



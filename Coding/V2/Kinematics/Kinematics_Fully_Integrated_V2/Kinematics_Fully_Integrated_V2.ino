#include <Herkulex.h>
#include <math.h>
#include "Arduino.h"
//Link Lengths
float l0 = 6.0;
float l1 = 6.7;
float l2 = 5.7;
float l3 = 3.4;

//Intersection Stuff
float A[2]; 
float B[2];
float a;
float b;

double p_1[2];
double p_2[2];

//For serial inuting
char rx_byte =0;
String rx_str = "";

//Motors Value
int motor0 = 0x00;
int motor1 = 0x01;
int motor2 = 0x02;
int motor3 = 0x03;

//Coordinates
float x = 0;
float y = 13;
float z = 5;

//Rotation Values
float theta0 = 0;
float theta1 = 0;
float theta2 = 0;
float theta3 = 0;

//Position Values
int position0 = 0;
int position1 = 0;
int position2 = 0;
int position3 = 0;


//flags
boolean input = false;

//Thresholds
int lT0 = 21;
int uT0 = 1002;
int lT1 = 259;
int uT1 = 706;
int lT2 = 283;
int uT2 = 750;
int lT3 = 381;
int uT3 = 829;

//ZeroPos
int zero = 511;
int offset0 = 519-zero;
int offset1 = 485 - zero;
int offset2 = 514 - zero;
int offset3 = 605 - zero;

void setup(){
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.beginSerial1(115200); //open serial port 1 
  Herkulex.reboot(0xfe); //reboot Motors
  delay(500); 
  Herkulex.initialize(); //initialize motors
  
  // read status
  Serial.println("");
  Serial.print("Status1:"); 
  Serial.println(Herkulex.stat(motor0));

  delay(1000);
  Herkulex.setLed(motor0, LED_GREEN);
  delay(1000);
 }

void loop(){
  getCoordinates();
  kine();
  setPosition();
  printSystem();
  Herkulex.moveAll(motor0, position0, 2);
  Herkulex.moveAll(motor1, position1, 2);
  Herkulex.moveAll(motor2, position2, 2);
  Herkulex.moveAll(motor3, position3, 2);
  Herkulex.actionAll(900);
  delay(2000);
  if(z==5){
      nod();
  }
}

void printSystem(){
  Serial.print("Motor 0 status: ");
  Serial.println(Herkulex.stat(0));
  Serial.print("Motor 1 status: ");
  Serial.println(Herkulex.stat(1));
  Serial.print("Motor 2 status: ");
  Serial.println(Herkulex.stat(2));
  Serial.print("Motor 3 status: ");
  Serial.println(Herkulex.stat(3));
  Serial.print("Angle 0: ");
  Serial.println(theta0);
  Serial.print("Angle 1: ");
  Serial.println(theta1);
  Serial.print("Angle 2: ");
  Serial.println(theta2);
  Serial.print("Angle 3: ");
  Serial.println(theta3);
  Serial.print("Desired Position 0: ");
  Serial.println(position0);
  Serial.print("Actual Position 0: ");
  Serial.println(Herkulex.getPosition(motor0));
  Serial.print("Desired Position 1: ");
  Serial.println(position1);
  Serial.print("Actual Position 1: ");
  Serial.println(Herkulex.getPosition(motor1));
  Serial.print("Desired Position 2: ");
  Serial.println(position2);
  Serial.print("Actual Position 2: ");
  Serial.println(Herkulex.getPosition(motor2));
  Serial.print("Desired Position 3: ");
  Serial.println(position3);
  Serial.print("Actual Position 3: ");
  Serial.println(Herkulex.getPosition(motor3));

}

void setPosition(){
    position0 = map(theta0, -159, 159, 20, 1002)+offset0;
    position1 = map(theta1, -159, 159, 20, 1002)+offset1;
    position2 = map(theta2, -159, 159, 20, 1002)+offset2;
    position3 = map(-theta3, -159, 159, 20, 1002)+offset3;

    if(position0 > uT0){
      position0 = uT0;
      Serial.println("Too Large Angle 0");
    }
    if(position0 < lT0){
      position0 = lT0;
      Serial.println("Too Small Angle 0");
    }
    
    if(position1 > uT1){
      position1 = uT1;
      Serial.println("Too Large Angle 1");
    }
    if(position1 < lT1){
      position1 = lT1;
      Serial.println("Too Small Angle 1");
    }

    if(position2 > uT2){
      position2 = uT2;
      Serial.println("Too Large Angle 2");
    }
    if(position2 < lT2){
      position2 = lT2;
      Serial.println("Too Small Angle 2");
    }

    if(position3 > uT3){
      position3 = uT3;
      Serial.println("Too Large Angle 3");
    }
    if(position3 < lT3){
      position3 = lT3;
      Serial.println("Too Small Angle 3");
    }
}

void intersection(){
  double c = sqrt(pow(A[0]-B[0], 2) + pow(A[1]-B[1], 2));
  double cosAlpha = (pow(b, 2) + pow(c, 2)- pow(a, 2))/(2*b*c);
  double u_AB[] = {(B[0]-A[0])/c, (B[1]-A[1])/c};
  double pu_AB[] = {u_AB[1], -u_AB[0]};
  p_1[0] = A[0]+(u_AB[0]*(b*cosAlpha)) + (pu_AB[0]*(b*sqrt(1-pow(cosAlpha, 2))));
  p_1[1]= A[1]+(u_AB[1]*(b*cosAlpha))+ (pu_AB[1]*(b*sqrt(1-pow(cosAlpha, 2))));
  p_2[0] = A[0]+(u_AB[0]*(b*cosAlpha)) - (pu_AB[0]*(b *sqrt(1-pow(cosAlpha, 2))));
  p_2[1] = A[1]+(u_AB[1]*(b*cosAlpha)) - (pu_AB[1]*(b*sqrt(1-pow(cosAlpha, 2))));
}

void kine(){
  float p0[] = {0, 0};
  float p1[] = {0, l0};
  float w0 = sqrt(pow(x, 2) + pow(y, 2))-l3;
  float p3[] = {w0, z}; 
  float p2[2]; 
  if(p3 == p1){
    p2[0] = 0;
    p2[1] = l2;
    float p2[] = {0, l2};
  }
  else{
      A[0] = p1[0];
      A[1] = p1[1];
      B[0] = p3[0];
      B[1] = p3[1];
      a = l1;
      b = l2;
      intersection();
      if(p_1[1]>p_2[1]){
        p2[0] = p_1[0];
        p2[1] = p_1[1];
      }
      else{
        p2[0] = p_2[0];
        p2[1] = p_2[1];
      }
  }
  float p2adj[] = {p2[0], p2[1]-l0};
  float p3adj[] = {p3[0]-p2[0], p3[1]-p2[1]};
  Serial.println(x);
  Serial.println(y);
  Serial.println(z);
  
  theta0 = atan2(x, y);
  theta0 *= 180/PI; //convertin to degrees


  theta1 = atan2(p2adj[0], p2adj[1]);
  theta1 *= 180/PI;
  
  theta2 = atan2(p3adj[1], p3adj[0]);
  theta2 *= 180/PI;
  theta2 -= theta1;
  
  theta3 =  -theta1-theta2;
  theta1 = 90 - theta1;

  
}

void getCoordinates(){
  String coord = getInput();
  if(input){
    if(coord.indexOf('x')>-1 && coord.indexOf('y')>-1 && coord.indexOf('z')>-1){
      int i = coord.indexOf('x');
      String xPos = "";
      i++;
      while(coord.charAt(i) != ' ' && i < coord.length()){
        xPos += coord.charAt(i);
        i++;
      }
      x = xPos.toFloat();      
      i = coord.indexOf('y');
      String yPos = "";
      i++;
      while(coord.charAt(i) != ' ' && i < coord.length()){
        yPos += coord.charAt(i);
        i++;
      }
      y = yPos.toFloat(); 
      i = coord.indexOf('z');
      String zPos = "";
      i++;
      while(coord.charAt(i) != ' ' && i < coord.length()){
        zPos += coord.charAt(i);
        i++;
      }
      z = zPos.toFloat(); 
      Serial.println("_________________");
      Serial.print("X: ");
      Serial.print(x);
      Serial.print(" Y: ");
      Serial.print(y);    
      Serial.print(" Z: ");
      Serial.println(z); 
    }
    else{
      Serial.println("Input needs to contain x and y, in lower case");
      Serial.println("followed by their respective values and eperated by a space");
      Serial.println("i.e: x100 y300");
      delay(3000);
    }
  }
}


String getInput(){
  if(Serial.available() > 0){
    rx_str = "";// clear the string for reuse
    while (Serial.available() > 0) {    // is a character available?
      input = true;
      rx_byte = Serial.read();       // get the character
      if (rx_byte != '\n') {
        // a character of the string was received
        rx_str += rx_byte;
      }
      else {
        return rx_str;
               // clear the string for reuse
      }      
    }
  }
  input = false;  
  return rx_str;
}

void nod(){
  Serial.println("Nodding");
  int up = position3 +200;
  int down = position3 -200;

  if(up > uT3){
    up = uT3;
    down = position3 - (position3 - uT3);
    Serial.println("Too Large Angle Upper nod");
  }
  
  if(down < lT3){
    down = lT3;
    up = position3 + (position3 - lT3);
    Serial.println("Too Small Angle Lower Nod");
  }
     
  Herkulex.moveOne(motor3, up, 400, LED_GREEN);
  delay(500);
  Herkulex.moveOne(motor3, down, 400, LED_GREEN);
  delay(500);
  Herkulex.moveOne(motor3, up, 400, LED_GREEN);
  delay(500);
  Herkulex.moveOne(motor3, down, 400, LED_GREEN);
  delay(500);
  Herkulex.moveOne(motor3, up, 400, LED_GREEN);
  delay(500);
}


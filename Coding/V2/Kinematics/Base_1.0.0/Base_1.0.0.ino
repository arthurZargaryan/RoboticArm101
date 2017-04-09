#include <Herkulex.h>
//For serial inuting
char rx_byte = 0;
String rx_str = "";

//Motors Value
int motor0 = 0x00;


//Rotation Values
int angle = 0;

//flags
boolean input = false;

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
  Serial.print("Status1:");
  Serial.println(Herkulex.stat(motor0));
  int motor0Theta = getRotationValue();
  Serial.println(motor0Theta);
  delay(1000);
  Herkulex.moveAll(motor0, motor0Theta, 2);
  Herkulex.actionAll(200);
}


int getRotationValue(){
  int tmp = getInput();
  if(input){
      Serial.println("Change");
      angle = tmp; 
  }
  
  if(angle > 159){
    angle = 159;
    Serial.println("Angle too large");
  }
  else if(angle < -159){
    angle = -159;
    Serial.println("Angle too large");
  }
  
  return map(angle, -159, 159, 20, 1002);
}


int getInput(){
  
  while (Serial.available() > 0) {    // is a character available?
    input = true;
    int val = 0;
    Serial.println(rx_str);
    rx_byte = Serial.read();       // get the character
    if (rx_byte != '\n') {
      // a character of the string was received
      rx_str += rx_byte;
    }
    else {
      int val = rx_str.toInt();
      if(rx_str.charAt(1) == '-'){
        val = -val;
      }
      rx_str = "";
      Serial.println(val);
      return val;
             // clear the string for reuse
    }      
  }
  input = false;
}

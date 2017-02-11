#include <Herkulex.h>
// remeber only give pos between 1002 and 21. The recomended range

int targetMotor = 0x01; // new id you want motor to have
int currentPos = 500;// needs to be updated depending on target motor, look below for the initial positions
int upperLimit = 1010;
int lowerLimit = 25;
char rx_byte = 0;
String rx_str = "";


void setup(){
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.beginSerial2(115200); //open serial port 1 
  Herkulex.reboot(0xfe); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors 
  Herkulex.setLed(0xfe,LED_GREEN); //set the led
  delay(500); 
  Serial.print("Motor 0 status: ");
  Serial.println(Herkulex.stat(0));
  Serial.print("Motor 1 status: ");
  Serial.println(Herkulex.stat(1));
  Serial.print("Motor 2 status: ");
  Serial.println(Herkulex.stat(2));
  Serial.print("Motor 3 status: ");
  Serial.println(Herkulex.stat(3));
  Serial.print("Motor 4 status: ");
  Serial.println(Herkulex.stat(4));

  delay(1000);
  Serial.println("CLEAR area robot STARTING-UP in 5 seconds");
  delay(5000);
  Herkulex.moveAll(0x00, 630, LED_BLUE);  
  Herkulex.moveAll(1, 500, LED_BLUE); 
  Herkulex.moveAll(2, 557, LED_BLUE); 
  Herkulex.moveAll(3, 512, LED_BLUE); 
  Herkulex.moveAll(4, 512, LED_BLUE); 
  Herkulex.actionAll(1000);
}




void loop(){
  delay(3000);
  
  int val = getInput();
  //currentPos = Herkulex.getPosition(targetMotor);
  Serial.print(" Val :");
  Serial.println(val);
  if( (val + currentPos  <= upperLimit) && (val + currentPos >= lowerLimit)){
    currentPos = val + currentPos;
  }
  Herkulex.moveOne(targetMotor, currentPos, 500, LED_PINK); 
  Serial.println(currentPos);
  Serial.println(Herkulex.getPosition(targetMotor));
  Serial.println(Herkulex.stat(targetMotor));
  
}



int getInput(){
  int val = 0;
  while (Serial.available() > 0) {    // is a character available?
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
      return val;
             // clear the string for reuse
    }
         
  }
}



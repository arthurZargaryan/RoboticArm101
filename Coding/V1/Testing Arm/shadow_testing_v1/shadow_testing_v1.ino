#include <Herkulex.h>
#include <SoftwareSerial.h>

int n=0xfe; //motor ID - verify your ID !!!!
int knobPin = 0;  // analog pin used to connect the potentiometer
int val;
int tempVal;
int mapVal;

void setup()  
{
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.beginSerial1(115200); //open serial port 1 
  Herkulex.reboot(n); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  delay(200);  
  Serial.println("Shadowing Begun");
}

void loop(){
  tempVal = analogRead(knobPin);
  if( val - 2 < tempVal < val + 2){
    tempVal = val; 
  }
  val = tempVal;
  mapVal = map(val, 0, 1023, -160, 160);
  Serial.println(val);
  //Herkulex.moveOneAngle(n, val, 100, LED_BLUE); //move motor with 300 speed  
}



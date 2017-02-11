#include <Herkulex.h>
int knob3 = 3;

int val3;
int tempVal3;
int mapVal3;


int motor3 = 0x03;

void setup(){
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.beginSerial1(115200); //open serial port 1 
  Herkulex.reboot(0xfe); //reboot first motor
 // Herkulex.reboot(motor2); //reboot second motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  
  // read status
  Serial.println(Herkulex.stat(motor3));

  delay(1000);
  Herkulex.setLed(motor3, LED_GREEN);
  delay(1000);
 }

void loop(){
  tempVal3 = analogRead(knob3);
 

  if( tempVal3 > val3 - 2 && tempVal3 < val3 + 2){
    tempVal3 = val3; 
  }
  val3 = tempVal3;
  mapVal3 = map(val3, 0, 1023, -159, 159);

  Serial.print("M3333 ");
  Serial.println(Herkulex.stat(motor3));
  Serial.println(analogRead(knob3));
  Serial.println(-mapVal3);
  
  Herkulex.moveAllAngle(motor3, - mapVal3, 2);
  Herkulex.actionAll(100);
}


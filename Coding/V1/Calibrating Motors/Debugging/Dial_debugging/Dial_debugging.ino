#include <Herkulex.h>

int knob0 = 0;
int knob1 = 1;
int knob2 = 2;
int knob3 = 3;

int tempVal0;
int tempVal1;
int tempVal2;
int tempVal3;


void setup(){
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(9600);    // Open serial communications
  Serial.println("Begin");
}

void loop(){
  tempVal0 = analogRead(knob0);
  tempVal1 = analogRead(knob1);
  tempVal2 = analogRead(knob2);
  tempVal3 = analogRead(knob3);

  Serial.println("--------------------------------------------------------");
  Serial.println(tempVal0);
  Serial.println(tempVal1);
  Serial.println(tempVal2);
  Serial.println(tempVal3);
}


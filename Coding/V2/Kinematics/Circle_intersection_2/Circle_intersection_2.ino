#include <math.h>

double A[2]= {1.000, -1.000} ; 
double B[2]= {2.000, -2.000};
double a =5.000;
double b =4.000;

double p_1[2];
double p_2[2];


void setup() {
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  intersection();
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
  Serial.print( p_1[0], 4);
  Serial.print("  ");
  Serial.println(p_1[1], 4);
  Serial.print(p_2[0], 4);
  Serial.print("  ");
  Serial.println( p_2[1], 4);
}


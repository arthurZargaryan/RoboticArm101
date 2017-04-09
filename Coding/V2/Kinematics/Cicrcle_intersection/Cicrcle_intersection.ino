void triangulate(
  double Ax, double Ay,
  double Bx, double By,
  double AB, double AC, double BC,
  double &Cx1, double &Cy1,
  double &Cx2, double &Cy2)
{
  double cos1 = (AC * AC + AB * AB - BC * BC) / (2 * AC * AB);
  double sin1 = sqrt(1 - cos1 * cos1);

  double B1x, B1y;

  // get the location of B relative to A
  B1x = Bx - Ax;
  B1y = By - Ay;

  // scale by AC/AB,

  B1x *= AC / AB;
  B1y *= AC / AB;

  // rotate B1 by the calculated angle - plus or minus, and add A

  Cx1 = B1x * cos1 + B1y * sin1 + Ax;
  Cy1 = B1y * cos1 - B1x * sin1 + Ay;

  Cx2 = B1x * cos1 - B1y * sin1 + Ax;
  Cy2 = B1y * cos1 + B1x * sin1 + Ay;
}

double dist(double x1, double y1, double x2, double y2 ) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void printxy(double x, double y) {
  Serial.print("(");
  Serial.print(x) ;
  Serial.print(",");
  Serial.print(y);
  Serial.print(")");
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // seed random with A0, which is floating
  randomSeed(analogRead(0));

}

void loop() {

  // create some sample data
  double Ax, Ay, Bx, By, Cx, Cy, AB, AC, BC;

  // position of sensor A
  Ax = random(-100, 100);
  Ay = random(-100, 100);

  // position of sensor B
  Bx = random(-100, 100);
  By = random(-100, 100);

  // the object that we are trying to calculate the position of
  Cx = random(-100, 100);
  Cy = random(-100, 100);

  AB = dist(Ax, Ay, Bx, By); // we know this from where we have positioned the sensors
  AC = dist(Ax, Ay, Cx, Cy); // this is given by the ultrasonic
  BC = dist(Bx, By, Cx, Cy); // this is given by the ultrasonic

  double Solution1x, Solution1y, Solution2x, Solution2y;

  triangulate(Ax, Ay, Bx, By, AB, AC, BC, Solution1x, Solution1y, Solution2x, Solution2y);

  Serial.print("Sensor A is at ");
  printxy(Ax, Ay);
  Serial.print(", Sensor B is at ");
  printxy(Bx, By);
  Serial.println();
  Serial.print("Distance AB is ");
  Serial.print(AB);
  Serial.println();

  Serial.print("Sensed object is at ");
  printxy(Cx, Cy);
  Serial.println();
  Serial.print("Distance from sensor A to object is ");
  Serial.print(AC);
  Serial.println();
  Serial.print("Distance from sensor B to object is ");
  Serial.print(BC);
  Serial.println();


  Serial.print("Solution 1 is ");
  printxy(Solution1x, Solution1y);
  Serial.print(", which is accurate to ");
  Serial.print(dist(Cx, Cy, Solution1x, Solution1y));
  Serial.println();

  Serial.print("Solution 2 is ");
  printxy(Solution2x, Solution2y);
  Serial.print(", which is accurate to ");
  Serial.print(dist(Cx, Cy, Solution2x, Solution2y));
  Serial.println();

  Serial.println();

  delay(1000);

}

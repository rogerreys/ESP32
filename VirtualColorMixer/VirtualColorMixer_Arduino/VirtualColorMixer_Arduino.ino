const int redPin = A0;      // sensor to control red color

const int greenPin = A1;    // sensor to control green color

const int bluePin = A2;     // sensor to control blue color

void setup() {

  Serial.begin(9600);
}

void loop() {
  Serial.print(map(analogRead(redPin),0,1024,0,255));
  Serial.print(",");
  Serial.print(map(analogRead(greenPin),0,1024,0,255));
  Serial.print(",");
  Serial.println(map(analogRead(bluePin),0,1024,0,255));
  delay(500);
}
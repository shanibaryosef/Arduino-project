
int rotateLeftPin = 6;
int rotateRightPin = 5;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // Left rotaation
  analogWrite(rotateLeftPin, 100);
  analogWrite(rotateRightPin, 0);

  // sleep 5 seconds
  delay(5000);

  // Stop
  analogWrite(rotateLeftPin, 0);
  analogWrite(rotateRightPin, 0);

  // sleep 5 seconds
  delay(5000);

  // Right rotaation
  analogWrite(rotateLeftPin, 0);
  analogWrite(rotateRightPin, 100);

  // sleep 5 seconds
  delay(5000);
}

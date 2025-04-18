
int rotateLeftPin = 6;
int rotateRightPin = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);

}

void loop() {
  // Read Value
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);

  if(voltage > 3)
  {
  // Left rotaation
    float diff = voltage - 3.0;
    int speed = diff / 2.0 * 255;
    analogWrite(rotateLeftPin, speed);
    analogWrite(rotateRightPin, 0);
    analogWrite(9, speed);

  }
  else if(voltage < 2)
  {
    // Right
    float diff = 2.0 - voltage;  
    int speed = diff / 2.0 * 255;
    analogWrite(rotateLeftPin, 0);
    analogWrite(rotateRightPin,speed);
    analogWrite(9, speed);


  }
  else
  {
  // Stop
    analogWrite(rotateLeftPin, 0);
    analogWrite(rotateRightPin, 0);
    analogWrite(9, 0);

  }
}

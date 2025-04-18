//Encoder Example

// Define Pins

#define ENCODER_PINA 2

#define ENCODER_PINB 3

// encoder variables
volatile int encoderCounts = 0;
float rotationsPerSecond = 0;  // Rotations per second
unsigned long lastTime = 0;    // To track time
float rpm = 0;                 // RPM value

// Encoder ISR functions - Interupt Service Routine

void encoderA();

void encoderB();

void setup() {

  // initialize serial communication at 115200 bits per second:

  Serial.begin (115200);

 

  // initialize encoder, attache ISR functions

  pinMode(ENCODER_PINA, INPUT);

  pinMode(ENCODER_PINB, INPUT);

   // Attached interrupt to encoder pins

  attachInterrupt(digitalPinToInterrupt(ENCODER_PINA), encoderA, CHANGE);

  attachInterrupt(digitalPinToInterrupt(ENCODER_PINB), encoderB, CHANGE);

  Serial.print("Encoder_Value");

}

void loop() {
  int sensorValue = analogRead(A0);
  analogWrite(5, sensorValue);
  unsigned long currentTime = millis();
  
  if (currentTime - lastTime >= 1000) {
    rotationsPerSecond = encoderCounts / 360;
    rpm = rotationsPerSecond * 60;
    Serial.println(rpm);
   
    encoderCounts = 0;
    lastTime = currentTime;
  }
}

// EncoderA ISR

void encoderA() {

  // look for a low-to-high on channel B

  if (digitalRead(ENCODER_PINA) == HIGH) {

    // check channel A to see which way encoder is turning

    digitalRead(ENCODER_PINB) ? encoderCounts++ : encoderCounts--;    

  }else{

    // check channel A to see which way encoder is turning

    digitalRead(ENCODER_PINB) ? encoderCounts-- : encoderCounts++;

  }

} // End EncoderA ISR

// EncoderB ISR

void encoderB() {

  // look for a low-to-high on channel B

  if (digitalRead(ENCODER_PINB) == HIGH) {

    // check channel A to see which way encoder is turning

    digitalRead(ENCODER_PINA) ? encoderCounts-- : encoderCounts++;    

  }else{

    // check channel A to see which way encoder is turning

    digitalRead(ENCODER_PINA) ? encoderCounts++ : encoderCounts--;

  }

} // End EncoderB ISR

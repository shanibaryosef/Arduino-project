
#define ENCODER_PINA 3
#define ENCODER_PINB 2

#define IN1_PIN 5
#define IN2_PIN 6

volatile int encoderCounts = 0;
int targetPosition = 0;

// PID constants
float Kp = 2.0;
float Ki = 0.05;
float Kd = 0.1;

// PID variables
float error = 0;
float lastError = 0;
float integral = 0;
float derivative = 0;

unsigned long lastControlTime = 0;
const unsigned long CONTROL_INTERVAL = 10;  // 100 Hz

void encoderA();
void encoderB();

void setup() {
  Serial.begin(115200);

  pinMode(ENCODER_PINA, INPUT);
  pinMode(ENCODER_PINB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PINA), encoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PINB), encoderB, CHANGE);

  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  Serial.println("Enter target position in degrees (0–360):");
}

void loop() {
  // Handle Serial input
  if (Serial.available()) {
    String inputString = Serial.readStringUntil('\n');
    int input = inputString.toInt();
    if (input >= 0 && input <= 360) {
      targetPosition = map(input, 0, 360, 0, 360); // 1 count per degree
      //Serial.print("New target: ");
      //Serial.print(input);
      //Serial.println(" degrees");
    } else {
      Serial.println("Invalid input. Please enter 0–360.");
    }
  }

  // PID at 100 Hz
  unsigned long currentTime = millis();
  if (currentTime - lastControlTime >= CONTROL_INTERVAL) {
    int position = encoderCounts;
    error = targetPosition - position;

    integral += error * (CONTROL_INTERVAL / 1000.0);
    derivative = (error - lastError) / (CONTROL_INTERVAL / 1000.0);
    float output = Kp * error + Ki * integral + Kd * derivative;
    lastError = error;

    int pwmValue = abs(output);
    pwmValue = constrain(pwmValue, 0, 255);

    
    if (abs(error) < 5) {
      integral = 0;
      derivative = 0;
      pwmValue = 0;

      digitalWrite(IN1_PIN, LOW);
      digitalWrite(IN2_PIN, LOW);  // Stop motor
    } else {
      if (output > 0) {
        digitalWrite(IN1_PIN, LOW);
        analogWrite(IN2_PIN, pwmValue);
      } else {
        digitalWrite(IN2_PIN, LOW);
        analogWrite(IN1_PIN, pwmValue);
      }
    }


    // Debug info every 100 ms
    static int counter = 0;
    if (++counter >= 10) {
      // Serial.print("Pos: ");
      // Serial.print(position);
      // Serial.print(" | Target: ");
      // Serial.print(targetPosition);
      // Serial.print(" | PWM: ");
      // Serial.print(pwmValue);
      // Serial.print(" | Error: ");
      // Serial.println(error);
      Serial.print("Error\t");
      Serial.print(error);
      Serial.print("\tPosition\t");
      Serial.print(position);
      Serial.print("\tTarget\t");
      Serial.println(targetPosition);
      counter = 0;
    }

    lastControlTime = currentTime;
  }
}

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


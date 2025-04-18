#define ENCODER_PINA 3
#define ENCODER_PINB 2

#define IN1_PIN 5
#define IN2_PIN 6

#define POT_PIN A0

volatile int encoderCounts = 0;
int lastEncoderCounts = 0;

float measuredRPM = 0;
float filteredRPM = 0;
float targetRPM = 0;

// LPF smoothing factor (closer to 1 = smoother)
float alpha = 0.85;

// PI controller
float Kp = 2.5;
float Ki = 0.3;
float error = 0;
float integral = 0;

// Timing
unsigned long lastControlTime = 0;
const unsigned long CONTROL_INTERVAL = 100;  // ms = 100 Hz
const float dt = CONTROL_INTERVAL / 1000.0; // seconds

const float countsPerRev = 360.0;

void encoderA();
void encoderB();

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);

  pinMode(ENCODER_PINA, INPUT);
  pinMode(ENCODER_PINB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PINA), encoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PINB), encoderB, CHANGE);

  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  Serial.println("Enter target RPM (e.g. 60):");
}

void loop() {
  // Serial input for new target
  int potVal = analogRead(POT_PIN);  // 0–1023
  targetRPM = map(potVal, 0, 1023, 0, 360);  // Max 120 RPM

  // Run every 10ms (100Hz)
  unsigned long now = millis();
  if (now - lastControlTime >= CONTROL_INTERVAL) {
    // 1. Measure velocity
    int deltaCounts = encoderCounts - lastEncoderCounts;
    measuredRPM = (deltaCounts * 60.0) / (countsPerRev * dt);
    lastEncoderCounts = encoderCounts;

    // 2. Apply LPF
    filteredRPM = alpha * filteredRPM + (1 - alpha) * measuredRPM;

    // 3. PI Controller
    error = targetRPM - filteredRPM;
    integral += error * dt;
    float output = Kp * error + Ki * integral;

    // 4. Set motor output
    int pwmValue = constrain(abs(output), 0, 255);
    if (abs(error) < 5) {
      integral = 0;
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

    // 5. Plot step response
    Serial.print("Target\t");
    Serial.print(targetRPM);
    Serial.print("\tRPM\t");
    Serial.println(filteredRPM);

    lastControlTime = now;
  }
}

void encoderA() {
  if (digitalRead(ENCODER_PINA) == HIGH) {
    digitalRead(ENCODER_PINB) ? encoderCounts++ : encoderCounts--;
  } else {
    digitalRead(ENCODER_PINB) ? encoderCounts-- : encoderCounts++;
  }
}
void encoderB() {
  if (digitalRead(ENCODER_PINB) == HIGH) {
    digitalRead(ENCODER_PINA) ? encoderCounts-- : encoderCounts++;
  } else {
    digitalRead(ENCODER_PINA) ? encoderCounts++ : encoderCounts--;
  }
}

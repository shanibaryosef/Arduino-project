/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  int sensorValue = analogRead(A0);

  // Convert the analog value to voltage
  float voltage = sensorValue * (5.0 / 1023.0);

  // Print the result in both raw ADC value and voltage
  //Serial.print("ADC Value: ");
  //Serial.println(sensorValue);
  Serial.print("\tVoltage: ");
  Serial.println(voltage, 3); // Print voltage with 3 decimal places

  delay(10); // Delay for a second before the next reading
}

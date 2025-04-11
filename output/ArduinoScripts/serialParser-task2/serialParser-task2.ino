void setup() {
  // Initialize serial communication at 115200 bits per second
  Serial.begin(115200);

  // Set LED pins as outputs
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.println("Enter brightness levels for 3 LEDs separated by commas (0-255):");
}

void loop() {
  static String inputString = "";
  static bool stringComplete = false;

  while (Serial.available()) {
    char incomingChar = (char)Serial.read();
    
    if (incomingChar != '\n') {
      inputString += incomingChar;
    } else {
      stringComplete = true;
    }
  }

  if (stringComplete) {
    int brightness1 = 0;
    int brightness2 = 0;
    int brightness3 = 0;
    int delimiterPos1 = inputString.indexOf(',');
    int delimiterPos2 = inputString.indexOf(',', delimiterPos1 + 1);

    if (delimiterPos1 != -1 && delimiterPos2 != -1) {
      brightness1 = inputString.substring(0, delimiterPos1).toInt();
      brightness2 = inputString.substring(delimiterPos1 + 1, delimiterPos2).toInt();
      brightness3 = inputString.substring(delimiterPos2 + 1).toInt();
      
      if (isValidBrightness(brightness1) && isValidBrightness(brightness2) && isValidBrightness(brightness3)) {
        analogWrite(9, brightness1);
        analogWrite(10, brightness2);
        analogWrite(11, brightness3);
      } else {
        Serial.println("Error: Brightness values must be between 0 and 255.");
      }
    } else {
      Serial.println("Error: Invalid input format. Please enter 3 brightness values separated by commas.");
    }

    // Clear the string for the next input
    inputString = "";
    stringComplete = false;  // Reset flag
  }
}

// Helper function to validate the brightness range
bool isValidBrightness(int brightness) {
  return brightness >= 0 && brightness <= 255;
}

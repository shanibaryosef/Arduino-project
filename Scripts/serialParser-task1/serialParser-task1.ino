void setup() {
  Serial.begin(115200);
  pinMode(9, OUTPUT);
  Serial.println("Enter brightness level (0-255):");
}

void loop() {
  static String inputString = "";
  static bool stringComplete = false;
  
  while (Serial.available()) {
    char incomingChar = (char)Serial.read();
    
    if (incomingChar != '\n') {
      inputString += incomingChar;
    }
    else
    {
      stringComplete = true;
    }
  }
  if(stringComplete)
  {
    int brightness = inputString.toInt();
    Serial.println(brightness);
    if (brightness >= 0 && brightness <= 255) {
      analogWrite(9, brightness);
    } else {
      Serial.println("Error: Brightness value must be between 0 and 255.");
    }
    stringComplete = false;
    inputString = "";
  }
}

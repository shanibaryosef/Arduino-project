# Arduino-project
This repository demonstrates various control system projects implemented on an Arduino Uno using a custom home kit shield. The projects cover basic to advanced topics, including LED control, motor control, sensor integration, encoder feedback, and serial communication.

## Projects Overview

### LED Control & Fading
- **Blink and Sequenced Blinking Effects:**  
  Implemented using external LEDs.
- **FadeModified.ino:**  
  LED fading effect whose speed is controlled by a potentiometer (using the `map()` function to convert analog readings from 0–1023 to PWM values 0–255).

### DC Motor Control
- **Rotator.ino:**  
  Simple 5-second sequences for motor rotations (CCW, stop, CW) using the DRV8837 driver.
- **Dynamic Motor Control Based on Potentiometer Input:**  
  The motor's direction and speed are adjusted depending on the analog voltage measured.

### Sensor Integration
- **ReadDistanceMotor.ino:**  
  Uses a VL53L4CD distance sensor to adjust motor speed according to the measured distance.
- Sensor data is visualized using the Arduino Serial Plotter.

### Encoder Feedback & RPM Measurement
- Implements interrupts to count pulses from a magnetic encoder.
- Tasks include calculating gear ratio and converting encoder counts into RPM, with real-time plotting and velocity control.

### Arduino Serial Parsers
- **serislParser-task1.ino:**  
  A simple parser that reads a newline-terminated ASCII string to update LED brightness.
- **serislParser-task2.ino:**  
  An advanced parser that splits an input string (using commas as delimiters) into multiple brightness values for three LEDs.

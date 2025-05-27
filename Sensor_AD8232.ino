// Constants and variables
const int ad8232Pin = A1;
int ad8232Signal;
int ad8232Threshold = 500;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  
  // Read AD8232 signal
  ad8232Signal = analogRead(ad8232Pin);

  // Print AD8232 sensor value to serial monitor
  Serial.print("AD8232 sensor value: ");
  Serial.println(ad8232Signal);

  // Check if the signal is above the threshold
  if (ad8232Signal > ad8232Threshold) {
    // Do something if the signal is above the threshold
    Serial.println("Signal is above the threshold");
  }

  // Delay for 1 second
  delay(1000);
}

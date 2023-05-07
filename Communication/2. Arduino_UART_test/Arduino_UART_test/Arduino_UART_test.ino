void setup() {
  // Start the serial communication
  Serial.begin(2400);
}

void loop() {
  // Check if data is available on the serial port
  if (Serial.available()) {
    // Read the incoming data
    String data = Serial.readString();
    // Print the data to the serial monitor
    Serial.println(data);
  }

}

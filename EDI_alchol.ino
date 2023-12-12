#include <SoftwareSerial.h>
int alcoholPin = A0; // analog input pin for alcohol sens
int threshold = 230;
void setup() {
    Serial.begin(9600); // initialize serial communication

}

void loop() {
  int alcoholValue = analogRead(alcoholPin); // read analog value
  float voltage = alcoholValue * (5.0 / 1023.0); // convert to voltage
  int alcoholLevel = map(alcoholValue, 0, 1023, 0, 500); // map to alcohol level (0-500)
  Serial.println(alcoholLevel);

  if (alcoholLevel > threshold) {
    Serial.println("ALERT: Alcohol level is above threshold!"); // send alert message
  }

  delay(5000); // wait for 1 second
}



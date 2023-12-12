#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 3, TXPin = 4;// Here we make pin 4 as RX of arduino & pin 3 as TX of arduino 
static const uint32_t GPSBaud = 9600;


TinyGPSPlus gps;

SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop()
{
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(),6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(),6);

    // CHECKING CO-ORDINATES
    // if(gps.location.lat() >= 18.46d && gps.location.lng() == 73.87d) {

    // }
    // else {
    //   Serial.print(gps.location.lat(), 2);
    // Serial.print(F(","));
    // Serial.print(gps.location.lng(), 2);
    // }
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  
  Serial.println();
}



// #include <TinyGPS++.h> // library for GPS module
// #include <SoftwareSerial.h>
// #include <ESP8266WiFi.h>
// TinyGPSPlus gps;  // The TinyGPS++ object
// SoftwareSerial ss(4, 5); // The serial connection to the GPS device

// void setup()
// {
//   Serial.begin(115200);
//   ss.begin(9600);

// }

// void loop()
// {
//   while (ss.available() > 0) //while data is available
//     if (gps.encode(ss.read())) //read gps data
//     {
//       if (gps.location.isValid()) //check whether gps location is valid
//       {
//         Serial.print(gps.location.lat(),6);
//         Serial.print(F(","));
//         Serial.print(gps.location.lng(),6);
//       }

//     }}

















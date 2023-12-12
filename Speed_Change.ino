#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <LiquidCrystal_I2C.h>


int alcoholPin = A0; // analog input pin for alcohol sens
int threshold = 160;
int buzzerPin = 12;
int lcdColumns = 16;
int lcdRows = 2;
const int buzzer = 12; 
const int LED = 13;

static const int RXPin = 3, TXPin = 2;// Here we make pin 4 as RX of arduino & pin 3 as TX of arduino 
static const uint32_t GPSBaud = 9600;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

int a=8;
int b=9;

int c=6;
int d=7;


void setup() 
{
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);

pinMode(13, OUTPUT);

pinMode(10,OUTPUT);
pinMode(5,OUTPUT);

pinMode(12, OUTPUT); // Set pin 9 as output

Serial.begin(9600);
ss.begin(GPSBaud);

lcd.init();                 
lcd.backlight();

pinMode(4, OUTPUT); // Set buzzer - pin 4 as an output
noTone(buzzer);

}

void loop()
{
 
  digitalWrite(a,HIGH);
  digitalWrite(b,LOW);
  analogWrite(5, 255);

  digitalWrite(d,HIGH);
  digitalWrite(c,LOW);   
  analogWrite(10, 255);
  
  int alcoholValue = analogRead(alcoholPin); // read analog value
  float voltage = alcoholValue * (5.0 / 1023.0); // convert to voltage
  int alcoholLevel = map(alcoholValue, 0, 1023, 0, 500); // map to alcohol level (0-500)
  Serial.println(alcoholLevel);



  if (alcoholLevel > threshold) {
    String message ="ALERT: Alcohol level is above threshold!";
    Serial.println("ALERT: Alcohol level is above threshold!"); // send alert message
    ss.write("ALERT:Alcohol Detect");
    ss.write("CAR ID : 101102.....");
    digitalWrite(LED, HIGH);
    scrollMessage(1, message, 100, 12);
    Serial.println("Calling GPS");
    tone(buzzer, 500);
    delay(500);
    noTone(buzzer);
    callgps();
  }

  delay(5000);
  
 
}

void slowdown()
{
  
  Serial.println("Slowdion!");
  for (int i = 256; i > 0; i--) 
  {
    analogWrite(5, i);
    analogWrite(10, i);
    tone(buzzer, 500);
    delay(200);
    noTone(buzzer);
    delay(100);
    
  }

  digitalWrite(a,LOW);
  digitalWrite(c,LOW);
  digitalWrite(b,LOW);
  digitalWrite(d,LOW);
  
  noTone(buzzer);
  delay(50000);
}

void callgps()
{
   while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("GPS Detected -> "));
    ss.write("18.463520,73.868212");
    tone(buzzer, 500);
    delay(500);
    noTone(buzzer);
    slowdown();
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
    ss.write("18.463520, 73.868212");
    slowdown();
  }
  else
  {
    Serial.print(F("Aquaring"));
    ss.write("18.463520, 73.868212");
    slowdown();
  }
  
}

void scrollMessage(int row, String message, int delayTime, int totalColumns) {
  for (int i=0; i < totalColumns; i++) {
    message = " " + message;  
  } 
  message = message + " "; 
  for (int position = 0; position < message.length(); position++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(position, position + totalColumns));
    tone(buzzer, 500);
    delay(200);
    noTone(buzzer);
    delay(delayTime);
  }
   lcd.setCursor(0, 0);
   lcd.print("ALERT ..!!");
   lcd.setCursor(0, 1);
   lcd.print("Driver Intoxicated");

}

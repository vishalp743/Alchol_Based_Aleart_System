#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "OPPO";// Enter your WIFI SSID
const char* password = "vishal321"; // Enter your WIFI Password


#define BOTtoken "6172845798:AAEVomTfjZkYkKHfDsAMiJoZnF4xqywXUfA" // Enter the bottoken you got from botfather
#define CHAT_ID "998635769" // Enter your chatID you got from chatid bot


X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
static const int RXPin = D2, TXPin = D3;
SoftwareSerial ss(RXPin, TXPin);
String data;


void setup() {
  // put your setup code here, to run once:
  ss.begin(9600);
  Serial.begin(9600);

  configTime(0, 0, "pool.ntp.org");      
  client.setTrustAnchors(&cert);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int a = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    a++;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  bot.sendMessage(CHAT_ID, "Wifi Connected!", "");
  bot.sendMessage(CHAT_ID, "System has Started!!", "");
}

void loop() {
  char buffer[20]="";
  
  if(ss.available()>0)
  {
       ss.readBytesUntil('\n',buffer,20);
       String myString = "";  // Create an empty string
       myString += buffer;
       bot.sendMessage(CHAT_ID, myString,"");
       Serial.println(myString);
  }
   else
   {
     
   }

}

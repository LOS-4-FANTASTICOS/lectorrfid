#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 #include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 4  //D2
#define RST_PIN 5 //D1

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
const char* ssid = "Tesalia";
const char* password = "1123581321";
int statuss = 0;
int out = 0;
 
void setup () {
 
Serial.begin(115200);
WiFi.begin(ssid, password);
SPI.begin(); 
mfrc522.PCD_Init(); 
while (WiFi.status() != WL_CONNECTED) {
 
delay(1000);
Serial.print("Connecting..");
 
}
 
}
 
void loop() {
 
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
HTTPClient http;  //Declare an object of class HTTPClient
 
http.begin("http://192.168.40.24/api/v1/test");  //Specify request destination
int httpCode = http.GET();                                                                  //Send the request
 
if (httpCode > 0) { //Check the returning code
 
String payload = http.getString();   //Get the request response payload
Serial.println(payload);                     //Print the response payload
 
}
 
http.end();   //Close connection
 {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
//  if (content.substring(1) == "04 C0 0A 7A 83 57 80") //change UID of the card that you want to give access
//  {
//    Serial.println(" Access Granted ");
//    Serial.println(" Welcome Mr.Circuit ");
//    delay(1000);
//    Serial.println(" Have FUN ");
//    Serial.println();
//    statuss = 1;
//  }
//  
//  else   {
//    Serial.println(" Access Denied ");
//    delay(3000);
//  }
} 
}
 
delay(1000);    //Send a request every 30 seconds
 
}

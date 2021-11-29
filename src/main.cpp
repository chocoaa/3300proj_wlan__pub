#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#define INPUT_SIZE 12
// Initialize Wifi connection to the router 
const char* ssid     = "**********"; 
const char* password = "**********"; 
// Initialize Telegram BOT 
const char BotToken[] = "***************************************"; 
#define CHAT_ID "********************"
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure net_ssl; 
UniversalTelegramBot bot(BotToken, net_ssl);
// the number of the LED pin   


void setup()  
{   
  Serial.begin(74880);   
  while (!Serial) {}  //Start running when the serial is open  
  delay(3000);   
  // attempt to connect to Wifi network:   
  Serial.println(ssid);   
  net_ssl.setTrustAnchors(&cert);
  WiFi.setAutoReconnect(1);
  WiFi.begin(ssid, password);
  while ( WiFi.waitForConnectResult()!= WL_CONNECTED) {   
    delay(500);   
    WiFi.begin(ssid, password);
  }
  configTime(0, 0, "pool.ntp.org");
}   


void loop()  
{   
 if (Serial.available () > 0){ //when serial buffer receive data

  // Get next command from Serial (add 1 for final 0)
	char input[INPUT_SIZE + 1];
	byte size = Serial.readBytes(input, INPUT_SIZE);
	// Add the final 0 to end the C string
	input[size] = 0;
  if(!strcmp("SendTimeUP",input)){
    bot.sendMessage(CHAT_ID,"Yo! Your Cup Noodle is Ready! Have a nice meal!");
  }
  Serial.flush();
 }
}   
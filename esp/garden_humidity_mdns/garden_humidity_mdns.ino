#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <mDNSResolver.h>
#include <ESP8266HTTPClient.h>


#define WIFI_AP         "XXXX"
#define WIFI_PASS       "XXXX"
#define NAME_TO_RESOLVE "garden.local"

using namespace mDNSResolver;

IPAddress ip;
int rainPin = A0;

WiFiClient wifiClient;
WiFiUDP udp;
Resolver resolver(udp);
String id = "daisy";

void setup() {
  Serial.begin(115200);
  int WiFiCounter = 0;

  // We start by connecting to a WiFi network
  Serial.println("Connecting to ");
  Serial.println(WIFI_AP);

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_AP, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED && WiFiCounter < 30) {
    delay(1000);
    WiFiCounter++;
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Resolving ");
  Serial.println(NAME_TO_RESOLVE);

  resolver.setLocalIP(WiFi.localIP());
  
  ip = resolver.search(NAME_TO_RESOLVE);
  
  if(ip != INADDR_NONE) {
    Serial.print("Resolved: ");
    Serial.println(ip);
  } else {
    Serial.println("Not resolved");
  }
}

void loop() {
  // Required to clear the UDP buffer, as we can't unjoin a multicast group yet
  resolver.loop();
  delay(1000); //1 sec
  int sensorValue = analogRead(rainPin);
  Serial.println(sensorValue);
  getPage(String(sensorValue));
  delay(60000); //60 secs
}

String DisplayAddress(IPAddress address)
{
 return String(address[0]) + "." + 
        String(address[1]) + "." + 
        String(address[2]) + "." + 
        String(address[3]);
}

bool getPage(String garden_url) {
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient

    if(ip != INADDR_NONE) {

      Serial.println("url");
      String url = "http://"+DisplayAddress(ip)+"/"+id+"/"+garden_url;

      Serial.println(url);
      http.begin(url);  //Specify request destination
      int httpCode = http.GET();                                                                  //Send the request
 
      if (httpCode > 0) { //Check the returning code
 
        String payload = http.getString();   //Get the request response payload
        Serial.println(payload);                     //Print the response payload
 
      }else{
        Serial.println("error");      
        Serial.println(http.errorToString(httpCode).c_str());
        Serial.println(String(httpCode));
        http.end();   //Close connection
        return false;
      }

      http.end();   //Close connection
      return true;
    }
  
  }

}

/*
Qian Jin
CASA0014-CE
*/


#include <ESP8266WiFi.h>
#include <ezTime.h>

const char* ssid     = "CE-Hub";
const char* password = "()c454,w1f1";

// Create a Timezone instance called GB
Timezone GB;

void setup() {
  Serial.begin(115200);
  delay(100);

  // Start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
// Call a ezTime function, broker a connection to the NTP server.
  waitForSync();

  Serial.println("UTC: " + UTC.dateTime());
  
// Get our localised time 
  GB.setLocation("Europe/London");
  Serial.println("London time: " + GB.dateTime());  

}
// Wait and then print the current time in this format
void loop() {
  delay(1000);
  Serial.println(GB.dateTime("H:i:s")); // UTC.dateTime("l, d-M-y H:i:s.v T")
}

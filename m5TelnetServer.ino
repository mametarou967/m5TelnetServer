#include <WiFi.h>

const char* ssid     = "";
const char* password = "";
const int port = 23;

WiFiServer server(port);

void setup()
{
    Serial.begin(115200);

    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Server port: ");
    Serial.println(port);

    server.begin();

}


void loop(){
 WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");

    while (client.connected()) {
      //if (client.available()) {
        // char c = client.read();
      //}
      Serial.write("Hello Client!");
      client.write("Hello Client!");

      delay(1000);
    }

    client.stop();
    Serial.println("Client Disconnected.");
  }
}
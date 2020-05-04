#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>

#define SENT "<html><head><title>BABY-PLANT POT</title></head><body><div style=\"background-color: powderblue;\">Sent Emotion Score</div></body></html>"

SoftwareSerial mySerial(10,11);
DFPlayerMini_Fast myMP3;

const char *ssid = "Teddy";
const char *password = "880307880307";

ESP8266WebServer server(80);

void handleRoot()
{

  server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound()
{

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void)
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  //MP3
  mySerial.begin(9600);
  myMP3.begin(mySerial);
  myMP3.volume(20);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266"))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.on("/1", []() {
    server.send(200, "text/html", SENT);
    Serial.println("Emotion in range 1");
    // Play()
    myMP3.paly(1);
  });
  server.on("/2", []() {
    server.send(200, "text/html", SENT);
    Serial.println("Emotion in range 2");
    // Play()
    myMP3.play(2);
  });
  server.on("/3", []() {
    server.send(200, "text/html", SENT);
    Serial.println("Emotion in range 3");
    // Play()
    myMP3.play(3)
  });
  server.on("/4", []() {
    server.send(200, "text/html", SENT);
    Serial.println("Emotion in range 4");
    // Play()
    myMP3.play(4)
  });
  server.on("/0", []() {
    server.send(200, "text/html", SENT);
    Serial.println("Failed !!");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient();
}

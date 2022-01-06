#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>   // Include the WebServer library

const int h1 = 13;
const int pino_sinal_analogico=17;
float ledVal = 0;
const int led = 2;
ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

extern void handleRoot();              // function prototypes for HTTP handlers
extern void handleNotFound();
extern void handleLED();
extern void aba2(), Root();


void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("********", "********");   // add Wi-Fi networks you want to connect to
//  wifiMulti.addAP("********", "********");
//  wifiMulti.addAP("nome_da_rede", "senha_da_rede");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
  
  ArduinoOTA.setHostname("ESP8266");
  ArduinoOTA.setPassword("esp8266");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("OTA ready");

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/",HTTP_GET, handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/LED", HTTP_POST, handleLED);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.on("/h1", aba2);
  server.on("/Root", Root);
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");

  pinMode(h1, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  pinMode(pino_sinal_analogico, INPUT);
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();                    // Listen for HTTP requests from clients
//  for (int x=0; x<360; x++) 
//  {
//    // converte graus para radianos e então obtém o valor do seno
//    sinVal = (sin(x*(3.1412/360)));
//    ledVal = int(sinVal*255);
//    analogWrite(ledPin, ledVal);
//    delay(25);
//  }
}

// #include<Arduino.h>
// #include <WiFi.h>

// const char* ssid = "Sagar home 5G";
// const char* password = "Janfeb@12";

// void setup() {
//   Serial.begin(115200);
//   delay(10);

//   // We start by connecting to a WiFi network
//   Serial.println();
//   Serial.println();
//   Serial.print("Connecting to ");
//   Serial.println(ssid);

//   WiFi.begin(ssid, password);

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }

//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   // Serial.println(WiFi.localIP());

// }

// void loop() {

//     Serial.println(WiFi.localIP());
//     delay(500);

// }

// #include <Arduino.h>
// #include <WiFi.h>

// // ------------- CHANGE THESE -------------
// const char *ssid = "Sagar home 5G";
// const char *password = "Janfeb@12";

// // Your server (laptop/PC) IP address
// const char *server_ip = "10.0.0.97"; // <-- CHANGE THIS!
// const uint16_t server_port = 5050;
// // ----------------------------------------

// WiFiClient client;

// void connectToWiFi()
// {
//   Serial.print("Connecting to WiFi");
//   WiFi.begin(ssid, password);

//   while (WiFi.status() != WL_CONNECTED)
//   {
//     Serial.print(".");
//     delay(500);
//   }

//   Serial.println("\nWiFi Connected!");
//   Serial.print("IP Address: ");
//   Serial.println(WiFi.localIP());
// }

// void connectToServer()
// {
//   Serial.print("Connecting to server ");

//   while (!client.connect(server_ip, server_port))
//   {
//     Serial.print(".");
//     delay(500);
//   }

//   Serial.println("\nConnected to server!");
// }

// void setup()
// {
//   delay(3000); // Prevents upload issues on ESP32-C3
//   Serial.begin(115200);

//   connectToWiFi();
//   connectToServer();
// }

// void loop()
// {

//   // Check if disconnected from server
//   if (!client.connected())
//   {
//     Serial.println("Disconnected from server! Reconnecting...");
//     client.stop();
//     connectToServer();
//   }

//   // Send data
//   client.println("Hello from ESP32-C3!");

//   // Check for server response
//   if (client.available())
//   {
//     String message = client.readStringUntil('\n');
//     Serial.print("Server: ");
//     Serial.println(message);
//   }

//   delay(1000);
// }


#include <Arduino.h>
#include <WiFi.h>

const char* ssid     = "Sagar home 5G";
const char* password = "Janfeb@12";

const char* server_ip = "10.178.205.13";   // your server
const uint16_t server_port = 5050;

WiFiClient client;

const int HEADER_SIZE = 64;

void sendMessage(String msg) {
  // 1️⃣ Convert message length to a header string
  String lengthStr = String(msg.length());
  
  // 2️⃣ Pad header to 64 bytes
  while (lengthStr.length() < HEADER_SIZE) {
    lengthStr += " ";
  }

  // 3️⃣ Send header
  client.print(lengthStr);

  // 4️⃣ Send actual message
  client.print(msg);
}

void setup() {
  Serial.begin(115200);
  delay(3000);

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected!");

  // Connect to server
  Serial.print("Connecting to server: ");
  Serial.println(server_ip);

  if (client.connect(server_ip, server_port)) {
    Serial.println("CONNECTED to server!");
  } else {
    Serial.println("FAILED to connect!");
    return;
  }
}

void loop() {
  if (!client.connected()) {
    Serial.println("Disconnected from server. Reconnecting...");
    client.connect(server_ip, server_port);
    delay(1000);
    return;
  }

  // send message
  sendMessage("Hello from ESP32-C3!");

  // read server response
  if (client.available()) {
    String resp = client.readString();
    Serial.print("Server: ");
    Serial.println(resp);
  }

  delay(1000);
}

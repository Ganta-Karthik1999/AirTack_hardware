#include "client.h"
#include <WiFi.h>
// Constructor

// Constructor
client::client(const char *_ssid, const char *_password, const char *server_ip, uint16_t server_port, int header_size)
    : _ssid(_ssid), 
      _password(_password), 
      server_ip(server_ip), 
      server_port(server_port),
      header_size(header_size)
{
    // Constructor body (if needed)
    
}


void client::initialize()
{
    printf("SSID: %s password : %s, SERVER %s:%d HEADER SIZE %d\n", _ssid, _password, server_ip, server_port, header_size);

}

void client::wificonnect()
{
    Serial.print("Connecting to WiFi");
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void client::clientconnect()
{
    
//   Serial.print("Connecting to server: ");
   Serial.println(server_ip);
   Serial.print(" on port: ");
    Serial.println(server_port);
   if(espclient.connect(server_ip, server_port)){
    Serial.println("CONNECTED to server!");
   }
    else{
     Serial.println("FAILED to connect to server !!");
     return;
    }


}


void client::sendMessgae(String data)
{
    if(espclient.connected()){
        String lengthStr = String(data.length());
        while (lengthStr.length() < header_size) {
        lengthStr += " ";
      }
        espclient.print(lengthStr);
        espclient.print(data);
        Serial.println("Message sent to server:");
        Serial.println(data);
    }
    else{
        Serial.println("Client not connected to server. Message not sent.");
    }
}

void client::receiveMessage()
{
    if(espclient.available()){
        String message = espclient.readString();
        Serial.println("Message received from server:");
        Serial.println(message);
    }
}
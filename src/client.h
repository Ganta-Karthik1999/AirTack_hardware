#ifndef WIFI_H
#define WIFI_H
#include <Arduino.h>
#include <WiFi.h>
class client
{
public:
client(const char *_ssid, const char *_password, const char *server_ip, uint16_t server_port, int header_size);
    void initialize();
    void wificonnect();
    void clientconnect();
    void sendMessgae(String data);

private:
    const char *_ssid;
    const char *_password;
    const char *server_ip;
    const uint16_t server_port;
    const int header_size ;
// protected:
    WiFiClient espclient;

    
};

#endif


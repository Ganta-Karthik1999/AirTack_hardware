#ifndef WIFI_H
#define WIFI_H


class Wifi {
public:
    void begin(const char* ssid, const char* password);
    bool connect();
    void disconnect();
    bool isConnected(); 
private:
    const char* _ssid; 
    const char* _password;  
};






#endif WIFI_H

#include <Arduino.h>
#include "TM7711.h"
#include "client.h"
#include <WiFi.h>
// Pin definitions (GPIO)
#define DATA_PIN  D4  // DOUT (data output) from TM7711
#define CLOCK_PIN D5  // PD_SCK (clock input) to TM7711
#define GREEN_LED D0 //  Green LED pin
#define BUZZER_PIN D1 // Buzzer pin

// Create TM7711  
TM7711 tm7711(DATA_PIN, CLOCK_PIN);


client wifiClient("Sagar home 5G", 
                  "Janfeb@12",
                  "10.110.210.23",
                    5050,
                    64
);




void setup() {
    Serial.begin(115200);
    tm7711.initialize(); // Initialize the TM7711
    pinMode(GREEN_LED, OUTPUT); // Initialize the green LED pin as an output
    pinMode(BUZZER_PIN, OUTPUT); // Initialize the buzzer pin as an output
    wifiClient.wificonnect();
    wifiClient.clientconnect();
}

void loop() {
    // Read average raw value
    long rawValue = tm7711.readAverage(25);

    // Convert raw value to voltage
    float voltage = tm7711.convertToVoltage(rawValue);

    // Convert voltage to pressure
    float pressure = tm7711.convertToPressure(voltage);

    // Map pressure to percentage
    int pressurePercentage = tm7711.mapPressurePercentage(voltage);

    // Print results
    // Serial.print("Raw Value: ");
    // Serial.print(rawValue);
    // Serial.print(" | Voltage: ");
    // Serial.print(voltage, 3);
    // Serial.print(" V | Pressure: ");
    // Serial.print(pressure, 2);
    // Serial.print(" kPa | Pressure Percentage: ");
    // Serial.print(pressurePercentage);
    // Serial.println(" %");

    if(pressure> 25){

        digitalWrite(GREEN_LED, LOW); // Turn the LED on (HIGH is the voltage level)
        digitalWrite(BUZZER_PIN, HIGH);// turning on the buzzer
    }

    else{
        digitalWrite(GREEN_LED, HIGH); // Turn the LED off by making the voltage LOW
        digitalWrite(BUZZER_PIN, LOW);// turning off the buzzer

    }
    // wifiClient.sendMessgae("Hello from ESP32\n");

    

}
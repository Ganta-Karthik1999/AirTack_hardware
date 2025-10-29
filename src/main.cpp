#include <Arduino.h>
#include "TM7711.h"

// Pin definitions (GPIO)
#define DATA_PIN  D4  // DOUT (data output) from TM7711
#define CLOCK_PIN D5  // PD_SCK (clock input) to TM7711


// Create TM7711  
TM7711 tm7711(DATA_PIN, CLOCK_PIN);

void setup() {
    Serial.begin(115200);
    tm7711.initialize(); // Initialize the TM7711
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


    Serial.print(rawValue);
    Serial.print(",");
    Serial.print(voltage, 3);
    Serial.print(",");
    Serial.print(pressure, 2);
    Serial.print(",");
    Serial.print(pressurePercentage);
    // delay(1000);
}

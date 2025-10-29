#include "TM7711.h"

// Constructor
TM7711::TM7711(uint8_t dataPin, uint8_t clockPin) : _dataPin(dataPin), _clockPin(clockPin) {}

// Initialize the TM7711
void TM7711::initialize() {

    pinMode(_dataPin, INPUT);   // DOUT is input
    Serial.print("GPIO pin ");
    Serial.print(_dataPin);
    Serial.println(" (dataPin) set to INPUT");

    pinMode(_clockPin, OUTPUT); // PD_SCK is output
    digitalWrite(_clockPin, LOW); // Ensure clock starts low
    Serial.print("GPIO pin ");
    Serial.print(_clockPin);
    Serial.println(" (clockPin) set to LOW, waiting for data to get LOW");

    // Check data pin status
    if (digitalRead(_dataPin) == HIGH) {
        Serial.print("GPIO pin ");
        Serial.print(_dataPin);
        Serial.println(" (dataPin) still HIGH, waiting...");
    }
}

// Check if the TM7711 is ready
bool TM7711::isReady() {
    return digitalRead(_dataPin) == LOW; // DOUT goes LOW when ready
}

// Read raw data from TM7711
long TM7711::readRaw(uint8_t nextMode) {
    while (!isReady()); // Wait until TM7711 is ready

    long value = 0;

    // Read 24 bits of data
    for (int i = 0; i < 24; i++) {
        digitalWrite(_clockPin, HIGH); // Pulse the clock high
        delayMicroseconds(1);
        value = (value << 1) | digitalRead(_dataPin); // Shift in data bit
        digitalWrite(_clockPin, LOW); // Pulse the clock low
        delayMicroseconds(1);
    }

    // Sign-extend the value for two's complement if MSB is set
    if (value & 0x800000) {
        value |= 0xFF000000; // Sign-extend to 32 bits
    }

    // Send 25-27 clock pulses to set the next mode
    for (int i = 0; i < nextMode; i++) {
        digitalWrite(_clockPin, HIGH);
        delayMicroseconds(1);
        digitalWrite(_clockPin, LOW);
        delayMicroseconds(1);
    }

    return value;
}

// Read multiple raw values and return the average
long TM7711::readAverage(uint8_t nextMode, uint8_t numReadings) {
    long total = 0;

    for (int i = 0; i < numReadings; i++) {
        total += readRaw(nextMode);
        delay(50); // Short delay between readings
    }

    return total / numReadings;
}

// Convert raw value to voltage
float TM7711::convertToVoltage(long rawValue, float vRef) {
    return (rawValue * vRef) / 8388608.0; // Scale raw value to voltage
}

// Convert voltage to pressure
float TM7711::convertToPressure(float voltage, float minVoltage, float maxVoltage) {
    return (voltage - minVoltage) * 100.0 / (maxVoltage - minVoltage); // Scale voltage to pressure
}

// Map pressure to percentage (0-100%)
int TM7711::mapPressurePercentage(float voltage, float minVoltage, float maxVoltage) {
    if (voltage <= minVoltage) return 0;
    if (voltage >= maxVoltage) return 100;
    return (int)((voltage - minVoltage) * 100.0 / (maxVoltage - minVoltage));
}

#ifndef TM7711_H
#define TM7711_H

#include <Arduino.h>

class TM7711 {
public:
    // Constructor
    TM7711(uint8_t dataPin, uint8_t clockPin);

    // Public methods
    void initialize();
    long readRaw(uint8_t nextMode);
    long readAverage(uint8_t nextMode, uint8_t numReadings = 5);
    float convertToVoltage(long rawValue, float vRef = 3.3);
    float convertToPressure(float voltage, float minVoltage = 0.172, float maxVoltage = 3.3);
    int mapPressurePercentage(float voltage, float minVoltage = 0.172, float maxVoltage = 3.3);

private:
    // Private attributes
    uint8_t _dataPin;
    uint8_t _clockPin;

    // Private methods
    bool isReady();
};

#endif

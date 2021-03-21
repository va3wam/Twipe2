#ifndef aaChip_h
#define aaChip_h
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io

#define serialBaudRate 115200 // Speed of serial port

// Define aaChip class
class aaChip // Indicate that we are extending LiquidCrystal_I2C class with our class 
{
   public:
      aaChip(); // Constructor
      void cfgToConsole();
      uint8_t getRevision();
      uint32_t getSerialSpeed();
      uint32_t getCodeSize();
      uint32_t getFreeHeap();
      uint32_t getCpuId();
      uint32_t getCpuClock();
   private:
      unsigned long serialSpeed; 
}; //class aaChip

#endif
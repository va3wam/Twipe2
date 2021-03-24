#ifndef aaChip_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define aaChip_h // Precompiler macro used for precompiler check.

#include <Arduino.h> // Required for variable type declarations. Arduino Core for ESP32. Comes with Platform.io

#define serialBaudRate 115200 // Speed of serial port

class aaChip // Define aaChip class 
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

#endif // End of precompiler protected code block.
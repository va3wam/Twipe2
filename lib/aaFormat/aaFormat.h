#ifndef aaFormat_h
#define aaFormat_h

#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io

// Define aaFormat class
class aaFormat
{
   public:
      aaFormat(); // Constructor
      const char* noColonMAC(String macAddress); // Returns string of MAC address with no colons in it
      String StringToUpper(String strToConvert); // Retruns string converted to all uppercase
      String ipToString(IPAddress ip); // Returns string of IP address
      void ipToByteArray(const char* str, byte* bytes); // Convert char array containing IP address to byte array
      void macToByteArray(const char* str, byte* bytes); // Convert char array containing MAC address to byte array
      void joinTwoConstChar(const char *a, const char *b, char *out); // Concatinate two const char* arrays  to one buffer.
   private:
      void _parseBytes(const char* str, char sep, byte* bytes, int8_t maxBytes, int8_t base); // Convert char array (ASCII) to byte array
}; //class aaFormat

#endif
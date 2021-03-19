/*************************************************************************************************************************************
 * @file amFormat.h
 * @author theAgingApprentice
 * @brief A collection of handy formatting functions. 
 * @details Converts datatypes in ways that makes it possib;e to use the output of one library as input for another.
 * @copyright Copyright (c) 2021 the Aging Apprentice
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files 
 * (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, 
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished 
 * to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * YYYY-MM-DD Dev        Description
 * ---------- ---------- -------------------------------------------------------------------------------------------------------------
 * 2021-03-18 Old Squire Program created
 *************************************************************************************************************************************/
#ifndef aaFormat_h
#define aaFormat_h
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io

// Define aaFormat class
class aaFormat
{
   public:
      aaFormat(); // Constructor
      String noColonMAC(String macAddress); // Returns string of MAC address with no colons in it
      String StringToUpper(String strToConvert); // Retruns string converted to all uppercase
      String ipToString(IPAddress ip); // Returns string of IP address
      void ipToByteArray(const char* str, byte* bytes); // Convert char array containing IP address to byte array
      void macToByteArray(const char* str, byte* bytes); // Convert char array containing MAC address to byte array
      void _parseBytes(const char* str, char sep, byte* bytes, int8_t maxBytes, int8_t base); // Convert char array (ASCII) to byte array
   private:
//      void _parseBytes(const char* str, char sep, byte* bytes, int8_t maxBytes, int8_t base); // Convert char array (ASCII) to byte array
}; //class aaFormat

#endif
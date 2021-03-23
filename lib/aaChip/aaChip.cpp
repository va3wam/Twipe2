/************************************************************************************
 * @file aaChip.cpp
 * @author theAgingApprentice
 * @brief Common API for retrieving ESP32 chip configuration information. 
 * @details Retrieve chip configuration details from both FreeRTOS and the ESP32 
 * Arduino framework.
 * @copyright Copyright (c) 2021 the Aging Apprentice
 * Permission is hereby granted, free of charge, to any person obtaining a copy of 
 * this software and associated documentation files (the "Software"), to deal in the 
 * Software without restriction, including without limitation the rights to use, copy, 
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, subject to the 
 * following conditions: The above copyright notice and this permission notice shall 
 * be included in all copies or substantial portions of the Software. THE SOFTWARE 
 * IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE 
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * YYYY-MM-DD Dev        Description
 * ---------- ---------- ------------------------------------------------------------
 * 2021-03-17 Old Squire Program created.
  ***********************************************************************************/
#include <aaChip.h> // Header file for linking.

/**
 * @brief Common API for retrieving ESP32 chip configuration information. 
 * @details Retrieve chip configuration details from both FreeRTOS and the ESP32 
 * Arduino framework.
 * =================================================================================*/
aaChip::aaChip()
{
   serialSpeed = serialBaudRate;

} //aaChip::aaChip()

/**
 * @brief Returns the revision number of the ESP32 chip.
 * @return uint32_t ESP.getChipRevision()   
 * =================================================================================*/
uint8_t aaChip::getRevision()
{
   return ESP.getChipRevision();
} //aaChip::getRevision()

/**
 * @brief Returns the size of the binary file in bytes.
 * @return uint32_t ESP.getSketchSize()   
 * =================================================================================*/
uint32_t aaChip::getCodeSize()
{
   return ESP.getSketchSize();
} //aaChip::getCodeSize()

/**
 * @brief Returns the amount of free heap (sorted memory the program can use) in bytes.
 * @return uint32_t ESP.getFreeHeap()   
 * =================================================================================*/
uint32_t aaChip::getFreeHeap()
{
   return ESP.getFreeHeap();
} //aaChip::getFreeHeap()

/**
 * @brief Returns the current speed setting of the serial port (baud rate).
 * @return uint32_t Serial.baudRate()   
 * =================================================================================*/
uint32_t aaChip::getSerialSpeed()
{
   return Serial.baudRate();
} //aaChip::getSerialSpeed()

/**
 * @brief Returns the CPU ID of the application core.
 * @return uint32_t xPortGetCoreID()   
 * =================================================================================*/
uint32_t aaChip::getCpuId()
{
   return xPortGetCoreID();
} //aaChip::getCpuId()

/**
 * @brief Returns the clock speed of the application core in Mhz.
 * @return uint32_t Serial.baudRate()   
 * ==================================================================================*/
uint32_t aaChip::getCpuClock()
{
   return getCpuFrequencyMhz();
} //aaChip::getCpuClock()

/**
 * @brief Send detailed chip configuration information to the console.
 * @details The ESP32-D0WDQ6 chip has dual Tensilica LX6 micro controllers. All WiFi 
 * logic runs on the PRO_CPU (core0) aka the processor core. This firmware runs on the 
 * APP_CPU (core 1) aka the application core.     
 * ==================================================================================*/
void aaChip::cfgToConsole()
{
   Serial.println("<aaChip::cfgToConsole> APP_CPU (core 1) settings:");  
   Serial.print("<aaChip::cfgToConsole> ... Chip revision = "); 
   Serial.println(getRevision()); 
   Serial.print("<aaChip::cfgToConsole> ... SDK version = "); 
   Serial.println(ESP.getSdkVersion()); 
   Serial.print("<aaChip::cfgToConsole> ... Sketch size = "); 
   Serial.print(getCodeSize()); Serial.println(" bytes");  
   Serial.print("<aaChip::cfgToConsole> ... Free heap = "); 
   Serial.print(getFreeHeap()); Serial.println(" bytes"); 
   Serial.print("<aaChip::cfgToConsole> ... Serial baud rate = "); 
   Serial.print(getSerialSpeed()); Serial.println(" Hz");
   Serial.print("<aaChip::cfgToConsole> ... Arduino core = "); 
   Serial.println(getCpuId());
   Serial.print("<aaChip::cfgToConsole> ... Arduino core clock frequency = "); 
   Serial.print(getCpuClock()); Serial.println(" MHz");
} //aaChip::cfgToConsole()
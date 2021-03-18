/*************************************************************************************************************************************
 * @file libTemplate.h
 * @author theAgingApprentice
 * @brief Common API for retrieving ESP32 chip configuration information. 
 * @details Retrieve chip configuration details from both FreeRTOS and the ESP32 Arduino framework.
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
 * 2021-03-17 Old Squire Program created.
 *************************************************************************************************************************************/
#ifndef libTemplate_h
#define libTemplate_h
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io

// Define libTemplate class
class libTemplate // Indicate that we are extending LiquidCrystal_I2C class with our class 
{
   public:
      libTemplate(); // Constructor for this class
      bool exampleFunction(uint8_t var1, uint8_t var2); // This is how yoou define a function
   private:
}; //class libTemplate

#endif
/***************************************************************************************************
 * @file main.cpp
 * @author the Aging Apprentice
 * @brief Twipe2 robot firmware 
 * @details Basic operating code for the Twipe2 robot 
 * @copyright Copyright (c) 2020 theAgingApprentice@protonmail.com
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
 * associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions: The above copyright notice and this 
 * permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * YYYY-MM-DD Dev        Description
 * ---------- ---------- ---------------------------------------------------------------------------
 * 2021-03-17 Old Squire Template created
 ***************************************************************************************************/
#include <aaChip.h> // Used to access details about the core (CPU) that the Arduino framework runs on

// Instantiate library objects
aaChip appCpu; // Access information about the ESP32 application microprocessor

/**
 * @brief Initialize the serial output with the specified baud rate measured in bits per second
=================================================================================================== */
void setupSerial()
{
   Serial.begin(serialBaudRate); // Open a serial connection at specified baud rate 
   while (!Serial); // Wait for Serial port to be ready
} //setupSerial()

/** 
 * @brief Capture and show the environment details of the robot
=================================================================================================== */
void showCfgDetails()
{
   Serial.println("<showCfgDetails> Robot Configuration Report");
   Serial.println("<showCfgDetails> ==========================");
   Serial.print("<showCfgDetails> ... Robot firmware version = "); 
   appCpu.cfgToConsole(); // Display core0 information on the console
} //showCfgDetails()

/** 
 * @brief Standard set up routine for Arduino programs 
=================================================================================================== */
void setup()
{
   setupSerial(); // Set serial baud rate  
   Serial.println("<setup> Start of setup");
   showCfgDetails(); // Show all configuration details
   Serial.println("<setup> End of setup");
} //setup()

/**
 * @brief Standard looping routine for Arduino programs
=================================================================================================== */
void loop()
{

} //loop()
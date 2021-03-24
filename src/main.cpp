/** 
 * @file main.cpp
 *
 * @mainpage Twipe2 robot firmware 
 * 
 * @section intro_section Introduction
 * 
 * This is the source code for the the Twipe2 robot. It is comprised of a number of 
 * custom general purpose libraries that will be reused for other applications as 
 * well as the main logic specific to the function oof this particular robot.
 * 
 * @section dependencies Dependencies
 *
 * This code depends on the following external code sources. 
 * @ref includes   
 *   
 * @section author Author 
 * 
 * Written as Aging Apprentices by:
 * @authors Doug Elliott, Old Squire
 * 
 * @copyright Copyright (c) 2021 the Aging Apprentice
 * 
 * @section license License
 * 
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
 * @section history Edit History
 * 
 * YYYY-MM-DD Dev        Description
 * ---------- ---------- ------------------------------------------------------------
 * 2021-03-17 Old Squire Code base created.
 ************************************************************************************/
#include <main.h> // Allows us to have functions appear out of order. 

/**
 * @brief Initialize the serial output with the specified baud rate measured in bits 
 * per second.
 * =================================================================================*/
void setupSerial()
{
   Serial.begin(serialBaudRate); // Open a serial connection at specified baud rate. 
   while (!Serial); // Wait for Serial port to be ready.
} //setupSerial()

/** 
 * @brief Show the environment details of this application.
 * =================================================================================*/
void showCfgDetails()
{
   Serial.println("<showCfgDetails> Robot Configuration Report");
   Serial.println("<showCfgDetails> ==========================");
   appCpu.cfgToConsole(); // Display core0 information on the console.
   network.cfgToConsole(); // Display network information on the console.
} //showCfgDetails()

/** 
 * @brief Arduino mandatory function #1. Runs once at boot. 
 * =================================================================================*/
void setup()
{
   setupSerial(); // Set serial baud rate. 
   Serial.println("<setup> Start of setup");
   network.connect(); // Start WiFi connection.
   showCfgDetails(); // Show all configuration details.
   Serial.println("<setup> End of setup");
} //setup()

/**
 * @brief Arduino mandatory function #2. Runs continually.
 * =================================================================================*/
void loop()
{

} //loop()
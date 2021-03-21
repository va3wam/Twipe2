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
 * 2021-03-17 Old Squire Codebase created.
 ***************************************************************************************************/
//#include <WiFi.h> // Required to connect to WiFi network. Comes with Platform.io
#include <aaChip.h> // Used to access details about the core (CPU) that the Arduino framework runs on
//#include <aaFormat.h> // Collection of handy format conversion functions
#include <aaNetwork.h> // Required for handling Wifi functions. 

// Instantiate library objects
aaChip appCpu; // Access information about the ESP32 application microprocessor (Core1)
aaFormat convert; // Assortment of handy conversion functions
aaNetwork network; // WiFi session management

// Global variables
//const char* myMacChar; // Pointer to char array containing the SOC MAC address.   
//const int8_t macNumBytes = 6; // MAC addresses have 6 byte addresses.
//byte myMacByte[macNumBytes]; // Byte array containing the 6 bytes of the SOC Mac address.

//const char* mqttBrokerIpChar; // Pointer to char array containing MQTT broker IP address
//const int8_t ipv4NumBytes = 4; // IPv4 has 4 byte address
//byte mqttBrokerIpByte[ipv4NumBytes]; // Byte array for IP address
//char ipv4ByteSep = '.'; // IP address bytes are seperated with a period

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
   appCpu.cfgToConsole(); // Display core0 information on the console
   network.cfgToConsole(); // Display network information on the console
} //showCfgDetails()

/** 
 * @brief Standard set up routine for Arduino programs 
=================================================================================================== */
void setup()
{
   setupSerial(); // Set serial baud rate  
   Serial.println("<setup> Start of setup");
   network.connect(); // Start WiFi connection
   showCfgDetails(); // Show all configuration details
//   const char *a = "part a";
//   const char *b = " part b";
//   char all[14];
//   convert.joinTwoConstChar(a ,  b, all);// doConcat(a, b, all);
//   Serial.println(all);
/*   
   convert.ipToByteArray(mqttBrokerIpChar, mqttBrokerIpByte); // Convert to byte array
   Serial.print("<setup> Broker IP = ");
   Serial.print(mqttBrokerIpByte[0],DEC);
   Serial.print(".");
   Serial.print(mqttBrokerIpByte[1],DEC);
   Serial.print(".");
   Serial.print(mqttBrokerIpByte[2],DEC);
   Serial.print(".");
   Serial.println(mqttBrokerIpByte[3],DEC);
   
*/

   Serial.println("<setup> End of setup");
} //setup()

/**
 * @brief Standard looping routine for Arduino programs
=================================================================================================== */
void loop()
{

} //loop()
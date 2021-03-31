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
 *
 * @ref mainIncludes   
 *   
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
 * @brief Start up the web server.
 * @details Web server supports configuring the MQTT broker IP without needing to 
 *          rebuild. It also provides a web interface for doing OTA code downloads.
 * =================================================================================*/
void startWebServer()
{
   char uniqueName[HOST_NAME_SIZE]; // Contain unique name for Wifi network purposes. 
   char *uniqueNamePtr = &uniqueName[0]; // Pointer to starting address of name. 
   network.getUniqueName(uniqueNamePtr); // Get unique name. 
   Serial.print("<startWebServer> Unique Name: "); Serial.println(uniqueName);
   Serial.print("<startWebServer> Name length: "); Serial.println(strlen(uniqueName));
   isWebServer = localWebService.start(uniqueNamePtr); // Start web server and track result.
   if(isWebServer)
   {
      Serial.println("<startWebServer> Web server successfully started.");
   } //if
   else
   {
      Serial.println("<startWebServer> Web server failed to start.");
   } //else
} //startWebServer()

/**
 * @brief Monitor local web service to see if there are any client requests.
 * @details Call to checkForClientRequest() does two things. First, it causes the 
 * localWebServer service to process any new binay downloads. Second, it returns a 
 * boolean, that when TRUE, indicates there is a new IP address for the MQTT broker 
 * that needs to be saved to NV RAM.
 * =================================================================================*/
void monitorWebServer()
{
   if(localWebService.checkForClientRequest()) // New binary or broker IP?
   {
      IPAddress tmpIP = localWebService.getBrokerIP(); // Get awaiting IP address.
      Serial.print("<monitorWebServer> Set broker IP to "); Serial.println(tmpIP);
      flash.writeBrokerIP(tmpIP); // Write address to flash.
   } //if
} //monitorWebServer()

/** 
 * @brief Arduino mandatory function #1. Runs once at boot. 
 * =================================================================================*/
void setup()
{
   setupSerial(); // Set serial baud rate. 
   Serial.println("<setup> Start of setup");
   network.connect(); // Start WiFi connection.
   startWebServer(); // Start up web server.
   showCfgDetails(); // Show all configuration details.
   brokerIP = flash.readBrokerIP(); // Retrieve MQTT broker IP address from NV-RAM.
   network.getUniqueName(uniqueNamePtr); // Puts unique name value into uniqueName[]
   Serial.print("<setup> Ping of broker at "); Serial.print(brokerIP);
   Serial.print(" resulted in ");
   Serial.println(network.pingIP(brokerIP, 5));
   Serial.print("<setup> Unique name = ");
   Serial.println(uniqueName);
   mqtt.connect(brokerIP, uniqueName);
   mqtt.publishMQTT("/health", "This is a test message");
   Serial.println("<setup> End of setup");
} //setup()

/**
 * @brief Arduino mandatory function #2. Runs continually.
 * =================================================================================*/
void loop()
{
   if(localWebService.connectStatus()) // Is there is a valid WiFi connection?
   {
      monitorWebServer(); // Handle any pending web client requests. 
   } //if   
} //loop()


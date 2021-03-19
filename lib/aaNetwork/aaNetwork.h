/*************************************************************************************************************************************
 * @file aaNetwork.h
 * @author theAgingApprentice
 * @brief Handle WiFi networking logic. 
 * @details Manages WiFi session management including disconnecting and reconnecting. Inspired by this code: 
 * https://github.com/marvinroger/async-mqtt-client/blob/master/examples/FullyFeatured-ESP32/FullyFeatured-ESP32.ino
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
 * 2021-03-18 Old Squire Program created.
 *************************************************************************************************************************************/
#ifndef aaNetwork_h // Precompiler check to avoid dupicate inclusion of this library.
#define aaNetwork_h // Precompiler macro used for precompiler check.

#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <WiFi.h> // Required to connect to WiFi network. Comes with Platform.io.
#include <aaFormat.h> // Collection of handy format conversion functions.
#include <known_networks.h> // Defines Access points and passwords that the robot can scan for and connect to.

// Define aaNetwork class
class aaNetwork 
{
   public:
      aaNetwork(); // Constructor.
      void connect(); // Handle connecting to the WiFI network. 
      bool connectStatus(); // Returns the status of the WiFi connection. 
      String getAccessPointName(); // Retrieve the name of the Access Point the robot is using.
      String getMacAddress(); // Retrieve the MAC of the Access Point of our WiFi radio transmitter. 
      IPAddress getIpAddress(); // Retrieve the IP address assigned to this SOC in string format.
      String getUniqueName(); // Retrieve the name that we will be known by on the AP and the MQTT broker.
      void cfgToConsole(); // Write out WiFi details. 
      void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info); // Event handler for all wifi events that occur
   private:
      const char* _lookForAP(); // Scan the 2.4GHz WiFi radio band looking for known Access Points.
      String _translateEncryptionType(wifi_auth_mode_t encryptionType); // Converts AP ENUM encryption value to human readable format.
      const char* _apSsid; // Access point SSID selected to connect to.
      const char* _apPassword; // Password of access point selected to connect to.
      const char* _hostName; // Name the robot will be known by on the network.
      aaFormat _convert; // Accept various variable type/formats and return a different variable type/format.
      const char* HOST_NAME_PREFIX = "Twipe2"; // Prefix added to MAC address to ensure unique ID.
      void _connectToWifi(); // Handle connecting to the WiFi network.
}; //class aaNetwork

#endif
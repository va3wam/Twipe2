/************************************************************************************
 * @file aaNetwork.cpp
 * @author theAgingApprentice
 * @brief Handle all of the networking logic required by the robot. 
 * @details Manages TCP/IP, HTTP server, OTA firmware loading and MQTT messaging. 
 *          See https://lastminuteengineers.com/esp32-ota-web-updater-arduino-ide/
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
 * 2021-03-22 Old Squire Replaced all String vars with char[] and const char*.
 * 2021-03-19 Old Squire Overhauled code base to allow for wifi event callbacks and 
 *            added signal evaluation and encryption method data. 
 * 2021-03-18 Old Squire Program created.
 ************************************************************************************/
#include <aaNetwork.h> // Required for Webserver data type

// This should be in the header file but that causes a warning durng build time.
static const char* HOST_NAME_PREFIX = "Twipe2"; // Prefix of unique name of this device on the network.

/**
 * @brief Handle all of the networking logic required by the robot. 
 * @details Manages TCP/IP, HTTP server, OTA firmware loading and MQTT messaging. 
 * See https://lastminuteengineers.com/esp32-ota-web-updater-arduino-ide/
 * =================================================================================*/
aaNetwork::aaNetwork() 
{
   Serial.println("<aaNetwork::aaNetwork> aaNetwork default constructor running.");
} //aaNetwork::aaNetwork()

/**
 * @brief This is the second form of the constructor for this class.
 * =================================================================================*/
aaNetwork::aaNetwork(const char *ssid, const char *password)
{
   Serial.println("<aaNetwork::aaNetwork> aaNetwork second form constructor running.");
} //aaNetwork::aaNetwork()

/**
 * @brief This is the destructor for this class.
 * =================================================================================*/
aaNetwork::~aaNetwork() 
{
   Serial.println("<aaNetwork::aaNetwork> aaNetwork destructor running.");
} //aaNetwork::aaNetwork()

/**
 * @brief Scan the 2.4Ghz band for known Access Points and select the one with the 
 * strongest signal.
 * @return const char _ssid which is the SSID of the best AP candidate to connect to
 * =================================================================================*/
const char* aaNetwork::_lookForAP()
{
   Serial.println("<aaNetwork::_lookForAP> Scanning the 2.4GHz radio spectrum for known Access Points.");
   _ssid = _unknownAP; //  At the start no known Access Point has been foundto connect to
   int numberOfNetworks = WiFi.scanNetworks(); // Used to track how many APs are detected by the scan
   int StrongestSignal = -127; // Used to find the strongest signal. Set as low as possible to start
   bool APknown; // Flag to indicate if the current AP appears in the known AP list
   Serial.println(numberOfNetworks);

   // Loop through all detected APs
   for(int i = 0; i < numberOfNetworks; i++)
   {
      APknown = false;
   
      // Scan table of known APs to see if the current AP is known to us
      for (int j = 0; j < numKnownAPs; j++)
      {
         // If the current scanned AP appears in the known AP list note the index value and flag found
         if(WiFi.SSID(i) == SSID[j])
         {
            APknown = true;
            _SSIDIndex = j;
         } //if
      }   //for

      // If the current AP is known and has a stronger signal than the others that have been checked
      // then store it in the variables that will be used to connect to the AP later
      if((APknown == true) && (WiFi.SSID(i).toInt() > StrongestSignal))
      {
         _ssid = SSID[_SSIDIndex].c_str();
         _password = Password[_SSIDIndex].c_str();
         StrongestSignal = WiFi.SSID(i).toInt();
      } //if
   } //for
   return _ssid;
}  //aaNetwork::lookForAP()

/**
 * @brief Event handler for wifi events.
 * @brief Tracks all wifi event activity even though we do not act on any of it at 
 * this time. At the very least the logs help us troule shoot wifi issues but this 
 * routine also acts as a reminder of what functional possibilities exist for future 
 * consideration.
 * @param WiFiEvent_t event tells us what type of event occurred
 * @param WiFiEventInfo_t info provides additional information about the event as a 
 * struct
 * =================================================================================*/
void aaNetwork::_wiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info)
{
   switch(event) 
   {
      case SYSTEM_EVENT_AP_START:
//         WiFi.softAP(AP_SSID, AP_PASS); //can set ap hostname here   
//         WiFi.softAPenableIpV6(); //enable ap ipv6 here
         Serial.println("<aaNetwork::WiFiEvent> Detected SYSTEM_EVENT_AP_START");            
         break;
      case SYSTEM_EVENT_STA_START:         
//         WiFi.setHostname(AP_SSID); //set sta hostname here
         Serial.println("<aaNetwork::WiFiEvent> Detected SYSTEM_EVENT_STA_START");            
         break;
      case SYSTEM_EVENT_STA_CONNECTED:         
//         WiFi.enableIpV6(); //enable sta ipv6 here
         Serial.println("<aaNetwork::WiFiEvent> Detected SYSTEM_EVENT_STA_CONNECTED");            
         break;
      case SYSTEM_EVENT_AP_STA_GOT_IP6:
         Serial.println("<aaNetwork::WiFiEvent> Detected SYSTEM_EVENT_AP_STA_GOT_IP6");            
         break;
      case SYSTEM_EVENT_STA_GOT_IP:
//         wifiOnConnect(); // Call function to do things dependant upon getting wifi connected
         Serial.println("<aaNetwork::WiFiEvent> Detected SYSTEM_EVENT_STA_GOT_IP");            
         break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
         Serial.println("<aaNetwork::WiFiEvent> Detected SYSTEM_EVENT_STA_DISCONNECTED");            
         break;
      case WL_NO_SSID_AVAIL:
         Serial.println("<aaNetwork::WiFiEvent> WL_NO_SSID_AVAIL");            
         break;
      case WL_IDLE_STATUS: 
         Serial.println("<aaNetwork::WiFiEvent> Detected WL_IDLE_STATUS");            
         break;
      default:
         Serial.println("<aaNetwork::WiFiEvent> ERROR - UNKNOW SYSTEM EVENT"); 
         Serial.print("<aaNetwork::WiFiEvent> ... Event = "); Serial.println(event);           
         break;
   } //switch
} //aaNetwork::WiFiEvent()

/**
 * @brief Provide human readable text for wifi connection status codes.
 * @return const char* "Text that explains what the code means".
 * =================================================================================*/
const char* aaNetwork::connectionStatus(wl_status_t status) 
{
   switch(status) 
   {
      case WL_NO_SHIELD: return "WL_NO_SHIELD"; // For compatibility with WiFi Shield library
      case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
      case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
      case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
      case WL_CONNECTED: return "WL_CONNECTED";
      case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
      case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
      case WL_DISCONNECTED: return "WL_DISCONNECTED";
      default: return "UNKNOWN_STATUS";
   } //switch
} // aaNetwork::_connectionStatus()

/**
 * @brief This function translates the type of encryption that an Access Point (AP) 
 * advertises. 
 * @brief Returns a more human readable description of what that encryption method is.
 * @param wifi_auth_mode_t encryptionType is the ENUM that the Access Point advertises 
 * for encryption.
 * @return String containing human readable label for the type of encryption the 
 * Access Point uses.
 * =================================================================================*/
const char* aaNetwork::_translateEncryptionType(wifi_auth_mode_t encryptionType)
{
   switch (encryptionType)
   {
      case (WIFI_AUTH_OPEN): return "Open";
      case (WIFI_AUTH_WEP): return "WEP";
      case (WIFI_AUTH_WPA_PSK): return "WPA_PSK";
      case (WIFI_AUTH_WPA2_PSK): return "WPA2_PSK";
      case (WIFI_AUTH_WPA_WPA2_PSK): return "WPA_WPA2_PSK";
      case (WIFI_AUTH_WPA2_ENTERPRISE): return "WPA2_ENTERPRISE";
      default: return "UNKNOWN";
   } //switch
} //aaNetwork::translateEncryptionType()

/**
 * @brief Manage the process of connecting to the WiFi network.
 * @details Scan for a suitable Access Point and if one is found then connect to it 
 * using the init_wifi() method. 
 * @return bool where true means a connection was made and false means no connection 
 * was made.
 * =================================================================================*/
void aaNetwork::connect()
{
   if(_lookForAP() == _unknownAP) // Scan the 2.4Ghz band for known Access Points and select the one with the strongest signal 
   {
      Serial.println("<aaNetwork::connect> No known Access Point SSID was detected. Cannot connect to WiFi at this time.");
   } // if
   else // Found a known Access Point to connect to
   {
      WiFi.onEvent(_wiFiEvent); // Set up WiFi event handler
      WiFi.begin(_ssid, _password); // Connect too strongest AP found
      Serial.print("<aaNetwork::connect> Attempting to connect to Access Point with the SSID ");
      Serial.println(_ssid);
      while(WiFi.waitForConnectResult() != WL_CONNECTED) // Hold boot process here until IP assigned
      {
         delay(500);
      } //while
      Serial.println("");
      Serial.print("<aaNetwork::connect> Connected to Access Point with the SSID ");
      Serial.print(_ssid);
      Serial.print(" with status code "); 
      Serial.print(WiFi.status());
      Serial.print(" (");
      Serial.print(connectionStatus(WiFi.status())); 
      Serial.println(")"); 
   } //else
} //aaNetwork::connect()

/**
 * @brief Puts a name which is both unique and predictable into the char array 
 * _uniqueName[].
 * @details Combines a prefix (HOSTNAME_PREFIX) with the 6 byte mac address 
 * of the WiFi module to produce a name that will be unque on the network. 
 * @param char *_uniqueNamePtr pointer to variable called _uniqueName[].   
 * =================================================================================*/
void aaNetwork::getUniqueName(char *_uniqueNamePtr)
{
   String macAdd = WiFi.macAddress(); // Get MAC address as String
   const char* myMacChar; // Pointer to char array containing the SOC MAC address.   
   const int8_t macNumBytes = 6; // MAC addresses have 6 byte addresses.
   byte myMacByte[macNumBytes]; // Byte array containing the 6 bytes of the SOC Mac address.
   myMacChar = macAdd.c_str(); // Convert to pointer to const char array   
   _convert.macToByteArray(myMacChar, myMacByte); // Convert to Byte array
   _convert.joinTwoConstChar(HOST_NAME_PREFIX, _convert.noColonMAC(macAdd), _uniqueNamePtr);
} //aaNetwork::getUniqueName()

/**
 * @brief Take measurements of the Wi-Fi strength and return the average result.
 * @details RSSI (Received Signal Strength Indicator) is a common measurement, but 
 * most WiFi adapter vendors handle it differently, as it isn't standardized. Ultimately, 
 * the easiest and most consistent way to express signal strength is with dBm, which 
 * stands for decibels relative to a milliwatt. Since RSSI is handled differently by 
 * most WiFi adapters, it's usually converted to dBm to make it consistent and human
 * readable.
 * mW - milliwatts (1 mW = 0 dBm)
 * RSSI - Received Signal Strength Indicator (usually 0-60 or 0-255)
 * dBm - Decibels in relation to a milliwatt (usually -30 to -100). dBm does not scale 
 * in a linear fashion like you'd expect, instead being logarithmic. That means that 
 * signal strength changes aren't smooth and gradual. The Rule of 3s and 10s 
 * highlights the logarithmic nature of dBm:
 * 3 dB of loss = -3 dB = halves signal strength
 * 3 dB of gain = +3 dB = doubles signal strength
 * 10 dB of loss = -10 dB = 10 times less signal strength (0.1 mW = -10 dBm, 0.01 mW = -20 dBm, etc.)
 * 10 dB of gain = +10 dB = 10 times more signal strength (0.00001 mW = -50 dBm, 0.0001 mW = -40 dBm, etc.) 
 * @param int8_t dataPoints is the number of readings to average together. 
 * @return long averageRSSI which is the average of 100 signal strength readings in dBm.   
 * =================================================================================*/
long aaNetwork::rfSignalStrength(int8_t dataPoints)
{
   long rssi = 0;
   long averageRSSI = 0;
   for(int i=0; i < dataPoints; i++)
   {
      rssi += WiFi.RSSI();
      delay(20);
   } //for
   averageRSSI = rssi / dataPoints;
   return averageRSSI;
} //aaNetwork::rfSignalStrength()

/**
 * @brief Return human readable assessment of signal strength.
 * @param int16_t signalStrength signal in dBm.
 * @return const char* Text assessment of signal strength.   
 * =================================================================================*/
const char* aaNetwork::evalSignal(int16_t signalStrength)
{
   if(signalStrength <= unusable) return "Unusable";
   if(signalStrength <= notGood) return "Not good";
   if(signalStrength <= okay) return "Okay";
   if(signalStrength <= veryGood) return "Very Good";
   return "Amazing";
} //evalSignal()

/**
 * @brief Send detailed network configuration information to the console.
 * @details The ESP32-D0WDQ6 chip has dual Tensilica LX6 micro controllers. All WiFi 
 * logic runs on the PRO_CPU (core0) aka the processor core. This firmware runs on 
 * the APP_CPU (core 1) aka the application core.     
 * =================================================================================*/
void aaNetwork::cfgToConsole()
{
   wifi_auth_mode_t encryption = WiFi.encryptionType(_SSIDIndex);
   int8_t dataReadings = 10; // Number of data readings to average to determine Wifi signal strength.
   long signalStrength = rfSignalStrength(dataReadings); // Get average signal strength reading.
   Serial.println("<aaNetwork::cfgToConsole> Network settings:");  
   Serial.print("<aaNetwork::cfgToConsole> ... Access Point Name = "); Serial.println(WiFi.SSID()); 
   Serial.print("<aaNetwork::cfgToConsole> ... Access Point Encryption method = "); Serial.print(encryption,HEX);
   Serial.print(" ("); Serial.print(_translateEncryptionType(WiFi.encryptionType(encryption))); Serial.println(")"); 
   Serial.print("<aaNetwork::cfgToConsole> ... Wifi signal strength = "); Serial.print(signalStrength);
   Serial.print(" ("); Serial.print(evalSignal(signalStrength)); Serial.println(")"); 
   String macAdd = WiFi.macAddress(); // Get MAC address as String
   const int8_t macNumBytes = 6; // MAC addresses have 6 byte addresses.
   byte myMacByte[macNumBytes]; // Byte array containing the 6 bytes of the SOC Mac address.
   const char* myMacChar = WiFi.macAddress().c_str();  
   _convert.macToByteArray(myMacChar, myMacByte); // Convert to Byte array
   Serial.print("<aaNetwork::cfgToConsole> ... Robot MAC address: ");
   Serial.printf("%02X",myMacByte[0]);    
   Serial.print(":");
   Serial.printf("%02X",myMacByte[1]);
   Serial.print(":");
   Serial.printf("%02X",myMacByte[2]);
   Serial.print(":");
   Serial.printf("%02X",myMacByte[3]);
   Serial.print(":");
   Serial.printf("%02X",myMacByte[4]);
   Serial.print(":");
   Serial.printf("%02X",myMacByte[5]);
   Serial.println();
   Serial.print("<aaNetwork::cfgToConsole> ... Robot IP address: "); 
   const char* myIpChar = _convert.ipToString(WiFi.localIP()).c_str(); // Pointer to char array containing MQTT broker IP address
   const int8_t ipv4NumBytes = 4; // IPv4 has 4 byte address 
   byte myIpByte[ipv4NumBytes]; // Byte array for IP address   
   _convert.ipToByteArray(myIpChar, myIpByte); // Convert to byte array
   Serial.print(myIpByte[0],DEC);
   Serial.print(".");
   Serial.print(myIpByte[1],DEC);
   Serial.print(".");
   Serial.print(myIpByte[2],DEC);
   Serial.print(".");
   Serial.println(myIpByte[3],DEC); 
   getUniqueName(_uniqueNamePtr); 
   Serial.print("<aaNetwork::cfgToConsole> ... Robot Host Name: "); Serial.println(_uniqueName);
} //aaNetwork::cfgToConsole()

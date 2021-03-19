/*************************************************************************************************************************************
 * @file aaNetwork.cpp
 * @author theAgingApprentice
 * @brief Handle all of the networking logic required by the robot. 
 * @details Manages TCP/IP, HTTP server, OTA firmware loading and MQTT messaging. See https://lastminuteengineers.com/esp32-ota-web-updater-arduino-ide/
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
#include <aaNetwork.h> // Required for Webserver data type

/**
 * @brief This is the constructor for this class.
 * @details This class extends the LiquidCrystal_I2C class
===================================================================================================*/
aaNetwork::aaNetwork() // Constructor for this class
{

} //aaNetwork::aaNetwork()

/**
 * @brief Event handler for wifi connection event.
 * @param WiFiEvent_t event tells us what type of event occurred
 * @param WiFiEventInfo_t info provides additional information about the event as a struct
===================================================================================================*/
void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info)
{
/*
   switch(event) 
   {
      case SYSTEM_EVENT_AP_START:
         WiFi.softAP(AP_SSID, AP_PASS); //can set ap hostname here   
         WiFi.softAPenableIpV6(); //enable ap ipv6 here
         break;
      case SYSTEM_EVENT_STA_START:
         //set sta hostname here
         WiFi.setHostname(AP_SSID);
         break;
      case SYSTEM_EVENT_STA_CONNECTED:
         //enable sta ipv6 here
         WiFi.enableIpV6();
         break;
      case SYSTEM_EVENT_AP_STA_GOT_IP6:
         //both interfaces get the same event
         break;
      case SYSTEM_EVENT_STA_GOT_IP:
         //wifiOnConnect();
         wifi_connected = true;
         break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
         wifi_connected = false;
         break;
      default:
         break;
   } //switch
*/
} //aaNetwork::WiFiEvent()

/**
 * @brief This function translates the type of encryption that an Access Point (AP) advertises (an an ENUM) 
 * and returns a more human readable description of what that encryption method is.
 * @param wifi_auth_mode_t encryptionType is the ENUM that the Access Point advertises for encryption.
 * @return String containing human readable label for the type of encryption the Access Point uses.
 */
String aaNetwork::_translateEncryptionType(wifi_auth_mode_t encryptionType)
{
   switch (encryptionType)
   {
      case (WIFI_AUTH_OPEN):
         return "Open";
      case (WIFI_AUTH_WEP):
         return "WEP";
      case (WIFI_AUTH_WPA_PSK):
         return "WPA_PSK";
      case (WIFI_AUTH_WPA2_PSK):
         return "WPA2_PSK";
      case (WIFI_AUTH_WPA_WPA2_PSK):
         return "WPA_WPA2_PSK";
      case (WIFI_AUTH_WPA2_ENTERPRISE):
         return "WPA2_ENTERPRISE";
      default:
         return "UNKNOWN";
   } //switch
} //aaNetwork::translateEncryptionType()

/**
 * @brief Scan the 2.4Ghz band for known Access Points and select the one with the strongest signal.
 * @return const char _apSsid which is the SSID of the best AP candidate to connect to
=================================================================================================== */
const char* aaNetwork::_lookForAP()
{
   _apSsid = "unknown"; //  At the start no known Access Point has been foundto connect to
   int numberOfNetworks = WiFi.scanNetworks(); // Used to track how many APs are detected by the scan
   int StrongestSignal = -127; // Used to find the strongest signal. Set as low as possible to start
   int SSIDIndex = 0; // Contains the SSID index number from the known list of APs
   bool APknown; // Flag to indicate if the current AP appears in the known AP list
   Serial.println(numberOfNetworks);

   // Loop through all detected APs
   for (int i = 0; i < numberOfNetworks; i++)
   {
      APknown = false;
   
      // Scan table of known APs to see if the current AP is known to us
      for (int j = 0; j < numKnownAPs; j++)
      {
         // If the current scanned AP appears in the known AP list note the index value and flag found
         if (WiFi.SSID(i) == SSID[j])
         {
            APknown = true;
            SSIDIndex = j;
         } //if
      }   //for

      // If the current AP is known and has a stronger signal than the others that have been checked
      // then store it in the variables that will be used to connect to the AP later
      if ((APknown == true) && (WiFi.SSID(i).toInt() > StrongestSignal))
      {
         _apSsid = SSID[SSIDIndex].c_str();
         _apPassword = Password[SSIDIndex].c_str();
         StrongestSignal = WiFi.SSID(i).toInt();
      } //if
   } //for
   return _apSsid;
}  //aaNetwork::lookForAP()

/**
 * @brief Return the SSID of the Access Point the we are using.
 * @return String WiFi.SSID() Name of the AP  
===================================================================================================*/
String aaNetwork::getAccessPointName()
{
   return WiFi.SSID();
} //aaNetwork::getAccessPointName()

/**
 * @brief Return the MAC of the Access Point of our WiFi radio transmitter.
 * @return String WiFi.macAddress() MAC address of WiFi radio  
===================================================================================================*/
String aaNetwork::getMacAddress()
{
   return WiFi.macAddress();
} //aaNetwork::getMACaddress()

/**
 * @brief Return the IP address that was assigned to us by the DHCP service on the local router.
 * @return IPAddress WiFi.localIP() IPv4 address assigned by APs DHCP service.    
===================================================================================================*/
IPAddress aaNetwork::getIpAddress()
{
   return WiFi.localIP();
} //aaNetwork::getIpAddress()

/**
 * @brief Return the robot name which is both unique and predictable.
 * @return String HOST_NAME_PREFIX  + _convert.noColonMAC(getMacAddress()).   
===================================================================================================*/
String aaNetwork::getUniqueName()
{
   return HOST_NAME_PREFIX  + _convert.noColonMAC(getMacAddress());
} //aaNetwork::getUniqueName()

/**
 * @brief Manage the process of connecting to the WiFi network.
 * @details Scan for a suitable Access Point and if one is found then connect to it using the 
 * init_wifi() method. This method connects to the Access Point, Starts up a webserver that serves
 * up a web page that allows you to configure network settings withut recompiling as well as 
 * handling Over The Air updates using websockets.
 * @return bool where true means a connection was made and false means no connection was made.
===================================================================================================*/
void aaNetwork::_connectToWifi()
{
   WiFi.begin(_apSsid, _apPassword); // Connect too strongest AP found
   Serial.print("<aaNetwork::connect> Attempting to connect to AP SSID ");
   Serial.print(_apSsid);
   while(WiFi.waitForConnectResult() != WL_CONNECTED) 
   {
      delay(500);
      Serial.print(".");
   } //while
   Serial.println("");
   Serial.print("<aaNetwork::connect> Connected to AP SSID ");
   Serial.print(_apSsid);
   Serial.print(" with status ");
   Serial.println(WiFi.status());
} //aaNetwork::_connectToWifi()

/**
 * @brief Manage the process of connecting to the WiFi network.
 * @details Scan for a suitable Access Point and if one is found then connect to it using the 
 * init_wifi() method. This method connects to the Access Point, Starts up a webserver that serves
 * up a web page that allows you to configure network settings withut recompiling as well as 
 * handling Over The Air updates using websockets.
 * @return bool where true means a connection was made and false means no connection was made.
 *
 * WiFi Library statuses 
 * Constants 	         Value
 * ===================  ========
 * WL_NO_SHIELD 	      255
 * WL_IDLE_STATUS 	   0
 * WL_NO_SSID_AVAIL 	   1
 * WL_SCAN_COMPLETED    2
 * WL_CONNECTED 	      3
 * WL_CONNECT_FAILED    4
 * WL_CONNECTION_LOST   5
 * WL_DISCONNECTED 	   6
===================================================================================================*/
void aaNetwork::connect()
{
   // Look for best Access Point to connect to
   _lookForAP(); // Scan the 2.4Ghz band for known Access Points and select the one with the strongest signal 
   if((String)_apSsid == "unknown") // If a suitable Access point is found 
   {
      Serial.println("<aaNetwork::connect> No known Access Point SSID was detected. Cannot connect to WiFi at this time.");
   } //if
   else
   {
      WiFi.mode(WIFI_STA);
      _hostName = getUniqueName().c_str(); // Host name becomes Twipe2 + MAC address without colons
      WiFi.softAP(_hostName); //Assign unique name for robot that the network sees
//      WiFi.onEvent()
      _connectToWifi();
   } //else
} //aaNetwork::connect()

/**
 * @brief Returns the status of the WiFi connection.
 * @return bool WiFi.isCOnnected(), true if there is a connection and false if there is not.
===================================================================================================*/
bool aaNetwork::connectStatus()
{
   return WiFi.isConnected();
} // aaNetwork::connectStatus()

/**
 * @brief Send detailed network configuration information to the console.
 * @details The ESP32-D0WDQ6 chip has dual Tensilica LX6 micro controllers. All WiFi logic runs on 
 * the PRO_CPU (core0) aka the processor core. This firmware runs on the APP_CPU (core 1) aka the 
 * application core.     
===================================================================================================*/
void aaNetwork::cfgToConsole()
{
   Serial.println("<aaNetwork::cfgToConsole> Network settings:");  
   Serial.print("<aaNetwork::cfgToConsole> ... Access Point Name = "); Serial.println(getAccessPointName()); 
   Serial.print("<aaNetwork::cfgToConsole> ... Robot MAC address: "); Serial.println(getMacAddress());
   Serial.print("<aaNetwork::cfgToConsole> ... Robot IP address: "); Serial.println(getIpAddress());
   Serial.print("<aaNetwork::cfgToConsole> ... Robot Host Name: "); Serial.println(getUniqueName()); 
} //aaNetwork::cfgToConsole()
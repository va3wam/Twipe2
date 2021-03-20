#ifndef aaNetwork_h // Start of precompiler check to avoid dupicate inclusion of this code block.
#define aaNetwork_h // Precompiler macro used for precompiler check.

#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <WiFi.h> // Required to connect to WiFi network. Comes with Platform.io.
#include <aaFormat.h> // Collection of handy format conversion functions.
#include <known_networks.h> // Defines Access points and passwords that the robot can scan for and connect to.

enum signalStrength 
{
    amazing = -30,
    veryGood = -67,
    okay = -70,
    notGood = -80,
    unusable = -90,      
}; //enum

class aaNetwork // Define aaNetwork class
{
   public:
      aaNetwork(); // Default class constructor.
      aaNetwork(const char *ssid, const char *password); // Second form of class constructor.
      ~aaNetwork(); // Class destructor.
      const char* connectionStatus(wl_status_t status); // Provide human readable text for wifi connection status codes. 
      void cfgToConsole(); // Send wifi connection details to console
      char* getSSID(void); // Retireve Access Point SSID.
      char* getPSWD(void); // Retrieve Access Point password.
      void connect(); // Connect to Wifi
      long rfSignalStrength(int8_t points); // Collect an average WiFi signal strength 
      String evalSignal(int16_t signalStrength); // Return human readable assessment of signal strength.
   private:
      const char* _lookForAP(); // Scan 2.4GHz radio spectrum for known Access Point.
      const char* _translateEncryptionType(wifi_auth_mode_t encryptionType); // Provide human readable wifi encryption method
      String _getUniqueName(); // Construct a name that is sure to be unique on the network 
      static void _wiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info); // Event handler for wifi
      const char* _unknownAP = "unknown"; // Comparitor used to check if a valid AP was found.
      const char* _ssid; // SSID of Access Point selected to connect to over Wifi. 
      const char* _password; // Password of Access Point selected to connect to over Wifi.
      aaFormat _convert; // Accept various variable type/formats and return a different variable type/format.
      String _hostNamePrefix = "Twipe2"; // Prefix added to MAC address to ensure unique ID.
      int8_t _SSIDIndex = 0; // Contains the SSID index number from the known list of APs
}; //class aaNetwork

#endif // End of precompiler protected code block
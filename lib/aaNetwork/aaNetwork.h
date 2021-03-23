#ifndef aaNetwork_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define aaNetwork_h // Precompiler macro used for precompiler check.

#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <WiFi.h> // Required to connect to WiFi network. Comes with Platform.io.
#include <aaFormat.h> // Collection of handy format conversion functions.
#include <known_networks.h> // Defines Access points and passwords that the robot can scan for and connect to.

// Avoid magic numbers and make code more readable with these constants.
enum signalStrength // English translation of dB readings for WiFi signal strength.
{
    amazing = -30,
    veryGood = -67,
    okay = -70,
    notGood = -80,
    unusable = -90,      
}; //enum
static const int8_t HOST_NAME_SIZE = 20; // Max size of unique network name of this device on the network. 
static const char* HOST_NAME_PREFIX = "Twipe2"; // Prefix of unique name of this device on the network.

class aaNetwork // Define aaNetwork class
{
   public:
      aaNetwork(); // Default class constructor.
      aaNetwork(const char *ssid, const char *password); // Second form of class constructor.
      ~aaNetwork(); // Class destructor.
      void getUniqueName(char *ptrNameArray); // Construct a name that is sure to be unique on the network
      const char* connectionStatus(wl_status_t status); // Provide human readable text for wifi connection status codes. 
      void cfgToConsole(); // Send wifi connection details to console
      char* getSSID(void); // Retireve Access Point SSID.
      char* getPSWD(void); // Retrieve Access Point password.
      void connect(); // Connect to Wifi.
      long rfSignalStrength(int8_t points); // Collect an average WiFi signal strength 
      const char* evalSignal(int16_t signalStrength); // Return human readable assessment of signal strength.
   private:
      const char* _lookForAP(); // Scan 2.4GHz radio spectrum for known Access Point.
      const char* _translateEncryptionType(wifi_auth_mode_t encryptionType); // Provide human readable wifi encryption method
 
      static void _wiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info); // Event handler for wifi
      const char* _unknownAP = "unknown"; // Comparitor used to check if a valid AP was found.
      const char* _ssid; // SSID of Access Point selected to connect to over Wifi. 
      const char* _password; // Password of Access Point selected to connect to over Wifi.
      aaFormat _convert; // Accept various variable type/formats and return a different variable type/format.
      int8_t _SSIDIndex = 0; // Contains the SSID index number from the known list of APs.
      char _uniqueName[HOST_NAME_SIZE]; // Character array that holds unique name for Wifi network purposes. 
      char *_uniqueNamePtr = &_uniqueName[0]; // Pointer to first address position of unique name character array. 
}; //class aaNetwork

#endif // End of precompiler protected code block
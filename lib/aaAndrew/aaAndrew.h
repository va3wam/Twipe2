/************************************************************************************
 * @file aaAndrew.h  
 ************************************************************************************/

#ifndef aaAndrew_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define aaAndrew_h // Precompiler macro used for precompiler check.

/************************************************************************************
 * @section aaAndrewIncludes Included libraries
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io
#include <Preferences.h> // Required for saving variables into Flash memory
#include <Update.h> // Library used to update firmware
#include <WiFiClient.h> // Required for communicating with web browser
#include <WebServer.h> // Required for hosting an HTTP server on the ESP32
#include <ESPmDNS.h> // Required for local name resolution and redirecting of incoming cient requests

// Define aaAndrew class
class aaAndrew // Indicate that we are extending LiquidCrystal_I2C class with our class 
{
   public:
      aaAndrew(); // Default constructor for this class.
      ~aaAndrew(); // Class destructor.
      bool start(const char* HOST_NAME); // Set up web server and OTA service.
   private:
}; //class aaAndrew

#endif // End of precompiler protected code block
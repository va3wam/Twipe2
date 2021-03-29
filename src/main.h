/************************************************************************************
 * @file main.h  
 ************************************************************************************/
#ifndef main_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define main_h // Precompiler macro used for precompiler check.

/************************************************************************************
 * @section mainIncludes Included libraries.
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <aaChip.h> // Core (CPU) details that the code running on.
#include <aaNetwork.h> // Required for handling Wifi functions. 
#include <aaWebService.h> // Realtime web-based network config and OTA code updates.
#include <aaFlash.h> // Use Flash memory to store values that persist past reboot.

/************************************************************************************
 * @section mainConstants Define constant values. 
 ************************************************************************************/
const char* HOST_NAME_PREFIX = "Twipe2"; // Prefix for our unique network name.
const char* WEB_APP_TITLE = "Twipe2"; // App name for web page titles.
IPAddress brokerIP; // IP address of the MQTT broker.

/************************************************************************************
 * @section mainInstantiate Instantiated objects.
 ************************************************************************************/
aaChip appCpu; // Access information about the ESP32 application microprocessor (Core1).
//aaFormat convert; // Assortment of handy conversion functions.
aaNetwork network(HOST_NAME_PREFIX); // WiFi session management.
aaWebService localWebService(WEB_APP_TITLE); // Webserver hosted by microcontroller.
aaFlash flash; // Non-volatile memory management. 

/************************************************************************************
 * @section mainGlobalVar Declare global variables.
 ************************************************************************************/
bool isWebServer; // True is web server running.

/************************************************************************************
 * @section mainDeclare Declare functions.
 ************************************************************************************/
// Declare functions.
void setupSerial(); // Initialize the serial output.
void showCfgDetails(); // Show the environment details of this application.
void startWebServer(); // Start up the local web server service.
void setup(); // Arduino mandatory function #1. Runs once at boot. 
void loop(); // Arduino mandatory function #2. Runs continually.

#endif // End of precompiler protected code block
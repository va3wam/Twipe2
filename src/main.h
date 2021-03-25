/************************************************************************************
 * @file main.h  
 ************************************************************************************/
#ifndef main_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define main_h // Precompiler macro used for precompiler check.

/************************************************************************************
 * @section mainIncludes Included libraries
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <aaChip.h> // Core (CPU) details that the code running on.
#include <aaNetwork.h> // Required for handling Wifi functions. 
#include <aaAndrew.h> // Realtime web-based network config and OTA code updates.

/************************************************************************************
 * @section mainInstantiate Instantiated objects
 ************************************************************************************/
aaChip appCpu; // Access information about the ESP32 application microprocessor (Core1).
//aaFormat convert; // Assortment of handy conversion functions.
aaNetwork network; // WiFi session management.
aaAndrew webServer; // Webserver hosted by microcontroller. 

/************************************************************************************
 * @section mainDeclare Declare functions
 ************************************************************************************/
// Declare functions.
void setupSerial(); // Initialize the serial output.
void showCfgDetails(); // Show the environment details of this application.
void setup(); // Arduino mandatory function #1. Runs once at boot. 
void loop(); // Arduino mandatory function #2. Runs continually.

#endif // End of precompiler protected code block
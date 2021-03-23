#ifndef aaDebug_h

#define aaDebug_h

/* This is the old way of doing things. It requires recompile to change debug levels and uses pre-compiler macros to replace Arduno
   syntax. Thi is not iin line with our new best pratices. This entire approach needs to be revisited.

#define DEBUG true // Turn debug tracing on/off
#define DMP_TRACE false // Set to TRUE or FALSE to toggle DMP memory read/write activity

// Create debug macros that mirror the standard c++ print functions. Use the pre-processor variable 
#if DEBUG == true
   #define AADP_PRINT(x) Serial.print(x)
   #define AADP_PRINTLN(x) Serial.println(x)
   #define AADP_PRINTF(x, y) Serial.printf(x, y)   // allow more concise debug output
   // print 2 things, like a label followed by a variable: AMDP_PRINT2(" Wifi return code: ", Wifi.returnCode)
   #define AADP_PRINT2(x,y) Serial.print(x); Serial.print(y)
   #define AADP_PRINT2LN(x,y) Serial.print(x); Serial.println(y)
#else // Map macros to "do nothing" commands so that when is not TRUE these commands do nothing
   #define AADP_PRINT(x)
   #define AADP_PRINTLN(x)
   #define AADP_PRINTF(x, y)
   #define AADP_PRINT2(x,y) 
   #define AADP_PRINT2LN(x,y)
#endif
*/

#endif
/*************************************************************************************************************************************
 * @file aaDebug.cpp
 * @author theAgingApprentice
 * @brief Contains varibles, objects and macros used to handle output from traditional Serial.print statements. 
 * @details Redirect output to different streams as well as control what level of debug output to use.
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
 * 2021-03-17 Old Squire Program created.
 *************************************************************************************************************************************/
#ifndef aaDebug_h
#define aaDebug_h
/* Old way of doing this required recompile to change debug levels
// Precompiler directives for debug output 
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
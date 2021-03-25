/** 
 * @file aaAndrew.cpp
 *
 * @page Network configuration and OTA code updates using a web interface. 
 * 
 * @section intro_section Introduction
 * 
 * Turn the microcntroller into a webserver that fcilitates the update of
 * network specific variables such as the MQTT broker IP address as well as
 * letting the user select a binary image which will be loaded into memory
 * via HTTP.
 * 
 * @section dependencies Dependencies
 *
 * This code depends on the following external code sources. 
 * @ref aaAndrewIncludes   
 *   
 * @section author Author 
 * 
 * Written as Aging Apprentices by:
 * @authors Doug Elliott, Old Squire
 * 
 * @copyright Copyright (c) 2021 the Aging Apprentice
 * 
 * @section license License
 * 
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
 * @section history Edit History
 * 
 * YYYY-MM-DD Dev        Description
 * ---------- ---------- ------------------------------------------------------------
 * 2021-03-24 Old Squire Code base created.
 ************************************************************************************/
#include <aaAndrew.h> // Header file for linking.

/**
 * @brief This is the default constructor for this class.
===================================================================================================*/
aaAndrew::aaAndrew() 
{
   Serial.println("<aaAndrew::aaAndrew> aaNetwork default constructor running.");
} //aaAndrew::aaAndrew()

/**
 * @brief This is the destructor for this class.
===================================================================================================*/
aaAndrew::~aaAndrew() 
{
   Serial.println("<aaAndrew::aaAndrew> aaNetwork destructor running.");
} //aaAndrew::aaAndrew()

/**
 * @brief Manage the process of connecting to the WiFi network.
 * @details Scan for a suitable Access Point and if one is found then connect to it using the 
 * init_wifi() method. This method connects to the Access Point, Starts up a webserver that serves
 * up a web page that allows you to configure network settings withut recompiling as well as 
 * handling Over The Air updates using websockets.
 * @return bool where true means a conneciton was made and false means no connectioon was made.
===================================================================================================*/
bool aaAndrew::start(const char* HOST_NAME)
{
   Serial.print("<aaAndrew::start> Host name is ");
   Serial.println(HOST_NAME);
   return true;
} //aaAndrew::start()
/************************************************************************************
 * @file libTemplate.cpp
 * @author theAgingApprentice
 * @brief Put brief description here with only one period at the end. 
 * @details Put detailed description here. Can have multiple periods and can also span
 * multiple lines.
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
 * 2021-03-29 Old Squire Program created.
 ************************************************************************************/
#include <libTemplate.h> // Header file for linking.

/**
 * @brief This is the default constructor for this class.
 * @param const char* Argument description.
 * =================================================================================*/
libTemplate::libTemplate(const char* var1) 
{
   // Serial.print does not work in constructor. Do not use.
} //libTemplate::libTemplate()

/**
 * @brief This is the second form of the constructor for this class.
 * @param const char* Argument description.
 * @param const char* Argument description.
 * =================================================================================*/
libTemplate::libTemplate(const char* var1,  const char* var2)
{
   // Serial.print does not work in destructor. Do not use.
} //libTemplate::libTemplate()

/**
 * @brief This is the destructor for this class.
 * =================================================================================*/
libTemplate::~libTemplate() 
{
   Serial.println("<libTemplate::libTemplate> aaNetwork destructor running.");
} //libTemplate::~libTemplate()

/**
 * @brief Explain briefly what this is.
 * @details Explain more details.
 * @param uint8_t var1 Explain what this argument is for.
 * @param uint8_t var2 Explain what this argument is for.
 * @return boolean value.     
 * =================================================================================*/
bool libTemplate::exampleFunction(uint8_t var1, uint8_t var2)
{
   Serial.println("<libTemplate::exampleFunction> Put variables particuar "); 
   return true; 
} //libTemplate::exampleFunction()
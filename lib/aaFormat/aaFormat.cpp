/*************************************************************************************************************************************
 * @file aaFormat.cpp
 * @author theAgingApprentice
 * @brief A collection of handy formatting functions. 
 * @details Converts datatypes in ways that makes it possib;e to use the output of one library as input for another.
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
 * 2021-02-25 Old Squire Program created
 *************************************************************************************************************************************/
#include <aaFormat.h> // Header file for linking.

/**
 * @brief This is the constructor for this class.
===================================================================================================*/
aaFormat::aaFormat()
{
   
} //aaFormat::aaFormat()

/** 
 * @brief Strips the colons off the MAC address of this device
 * @param String containing a MAC address with colons (:) embedded in it
 * @return String with MAC address containing no colons
 * =============================================================================== */
String aaFormat::noColonMAC(String macAddress)
{
//   Serial.println("<aaFormat::noColonMAC> Removing colons from MAC address");
   macAddress.remove(2, 1);        // Remove first colon from MAC address
   macAddress.remove(4, 1);        // Remove second colon from MAC address
   macAddress.remove(6, 1);        // Remove third colon from MAC address
   macAddress.remove(8, 1);        // Remove forth colon from MAC address
   macAddress.remove(10, 1);       // Remove fifth colon from MAC address
   return macAddress;
}  //aaFormat::noColonMAC()

/** 
 * @brief Converts a string to upper case
 * @details See https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
 * @param String any valid string
 * @return String converted to all caps
 * =============================================================================== */
String aaFormat::StringToUpper(String strToConvert) // convert the argument string to upper case
{
    std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);
    return strToConvert;
} //aaFormat::StringToUpper()

/** 
 * @brief Converts an IP address to a string
 * @param IPAddress any valid IP address 
 * @return String containing an IP address
 * =============================================================================== */
String aaFormat::ipToString(IPAddress ip)
{
   String s = "";
   for (int i = 0; i < 4; i++)
   {
      s += i ? "." + String(ip[i]) : String(ip[i]);
   } //for
//   Serial.print("<ipToString> IP Address = ");
//   Serial.println(s);
   return s;
}  //aaFormat::ipToString()

/** 
 * @brief Converts character array (ASCII) to byte array
 * @details Used to convert MAC addresses and IP addresses
 * @param const char* str - Character array containing ASCII string to convert
 * @param char sep - Character seperator ("-" for MAC address and "." for IP address)
 * @param byte* bytes - Pointer to byte array where we are to put the converted values
 * @param int8_t int maxBytes - length of array (6 for MAC address and 4 for IP address)
 * @param int8_t base Numbering base system (16 for MAC address and 10 for IP address)
 * =============================================================================== */
void aaFormat::_parseBytes(const char* str, char sep, byte* bytes, int8_t maxBytes, int8_t base) 
{
    for (int i = 0; i < maxBytes; i++) 
    {
        bytes[i] = strtoul(str, NULL, base); // Convert byte
        str = strchr(str, sep); // Find next separator
        if (str == NULL || *str == '\0') 
        {
            break; // No more separators, exit
        } //if
        str++; // Point to next character after separator
    } //for
} //parseBytes()

/** 
 * @brief Convert char array containing IP address to byte array
 * @param const char* str - Character array containing ASCII string to convert
 * @param byte* bytes - Pointer to byte array where we are to put the converted values
 * =============================================================================== */
void aaFormat::ipToByteArray(const char* str, byte* bytes) 
{
   int8_t ipv4NumBytes = 4; // IPv4 has 4 byte address
   int8_t baseNumberingSystem = 10; // IPv4 uses base 10 for its bytes
   char byteSeperator = '.'; // IP address bytes are seperated with a period
   _parseBytes(str, byteSeperator, bytes, ipv4NumBytes, baseNumberingSystem);
} //ipToByteArray()

/** 
 * @brief Convert char array containing MAC address to byte array
 * @param const char* str - Character array containing ASCII string to convert
 * @param byte* bytes - Pointer to byte array where we are to put the converted values
 * =============================================================================== */
void aaFormat::macToByteArray(const char* str, byte* bytes) 
{
   int8_t macNumBytes = 6; // MAC addresses have 6 byte addresses
   int8_t baseNumberingSystem = 16; // MAC addresses use base 16 for their bytes
   char byteSeperator = ':'; // MAC address bytes are seperated with a dash
   _parseBytes(str, byteSeperator, bytes, macNumBytes, baseNumberingSystem);
} //macToByteArray()
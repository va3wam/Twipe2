/************************************************************************************
 * @file libTemplate.h  
 ************************************************************************************/
#ifndef libTemplate_h // Start of precompiler check to avoid dupicate inclusion of this code block.
#define libTemplate_h // Precompiler macro used for precompiler check.

/************************************************************************************
 * @section mainIncludes Included libraries.
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io

/************************************************************************************
 * @class Describe the class here.
 * @brief Write a brief description in one sentence that ends with a period.
 * @details Write a longer explanation of the class if needed. Can be multiple 
 * sentences. Can also be multiple lines.   
 ************************************************************************************/
class libTemplate // Indicate that we are extending LiquidCrystal_I2C class with our class 
{
   public:
      libTemplate(const char* var1); // Default constructor for this class.
      libTemplate(const char* var1, const char* var2); // Second form of class constructor.
      ~libTemplate(); // Class destructor.
      bool exampleFunction(uint8_t var1, uint8_t var2); // This is how yoou define a function
   private:
}; //class libTemplate

#endif // End of precompiler protected code block
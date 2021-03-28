/************************************************************************************
 * @file libTemplate.h  
 ************************************************************************************/
#ifndef libTemplate_h // Start of precompiler check to avoid dupicate inclusion of this code block.
#define libTemplate_h // Precompiler macro used for precompiler check.

#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io

// Define libTemplate class
class libTemplate // Indicate that we are extending LiquidCrystal_I2C class with our class 
{
   public:
      libTemplate(); // Default constructor for this class.
      libTemplate(const char* var1); // Second form of class constructor.
      ~libTemplate(); // Class destructor.
      bool exampleFunction(uint8_t var1, uint8_t var2); // This is how yoou define a function
   private:
}; //class libTemplate

#endif // End of precompiler protected code block
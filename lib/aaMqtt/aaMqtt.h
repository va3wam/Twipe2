/************************************************************************************
 * @file aaMqtt.h  
 ************************************************************************************/
#ifndef aaMqtt_h // Start of precompiler check to avoid dupicate inclusion of this code block.
#define aaMqtt_h // Precompiler macro used for precompiler check.

/************************************************************************************
 * @section mainIncludes Included libraries.
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <WiFi.h> // Required to connect to WiFi network. Comes with Platform.io.
#include <AsyncMqttClient.h> // MQTT. https://github.com/marvinroger/async-mqtt-clientFupOLED().
#include "freertos/FreeRTOS.h" // OS threads. Comes with Platform.io.
#include "freertos/timers.h" // Software Timers. Comes with Platform.io.

/************************************************************************************
 * @class Describe the class here.
 * @brief Write a brief description in one sentence that ends with a period.
 * @details Write a longer explanation of the class if needed. Can be multiple 
 * sentences. Can also be multiple lines.   
 ************************************************************************************/
class aaMqtt // Indicate that we are extending LiquidCrystal_I2C class with our class 
{
   public:
      aaMqtt(); // Default constructor for this class.
      ~aaMqtt(); // Class destructor.
      static void connect(IPAddress address, const char* uniqueName); // Connect to MQTT broker.
      static void onMqttConnect(bool sessionPresent);
      static void onMqttDisconnect(AsyncMqttClientDisconnectReason reason); 
      static void onMqttSubscribe(uint16_t packetId, uint8_t qos);
      static void onMqttUnsubscribe(uint16_t packetId);
      static void publishMQTT(String topic, String msg);
      static void publishEvent(int evtId, int evtSev, String evtMsg);
      static void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
      static void onMqttPublish(uint16_t packetId);
   private:
}; //class aaMqtt

#endif // End of precompiler protected code block
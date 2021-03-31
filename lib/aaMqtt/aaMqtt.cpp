/************************************************************************************
 * @file aaMqtt.cpp
 * @mainpage Handle MQTT pub/sub mesaging.
 * @details Manage MQTT messaging to/from the application using pub/sub logic and
 * a tree structure prefixed with a name unique to this application. 
 * @author theAgingApprentice
 * @brief Put brief description here with only one period at the end. 
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
 * @section mqttHistory Edit History 
 * YYYY-MM-DD Dev        Description
 * ---------- ---------- ------------------------------------------------------------
 * 2021-03-29 Old Squire Program created.
 ************************************************************************************/
#include <aaMqtt.h> // Header file for linking.

static TimerHandle_t mqttReconnectTimer; // Instantiate OS software timer.
static const char* _uniqueName; // Unique name to prefix all topics with.
static IPAddress _brokerIP; // IP address of broker.
static uint16_t BROKER_PORT = 1883; // Port used by MQTT broker. 
static AsyncMqttClient mqttClient; // Instantiate MQTT object.
static const char*  cmdTopicMQTT = "NOTHING"; // Full path to incoming command topic from MQTT broker.
static uint8_t MQTT_QOS = 1; // use Quality of Service level 1 or 0? (0 has less overhead).

/**
 * @brief This is the default constructor for this class.
 * @param const char* Argument description.
 ===================================================================================================*/
aaMqtt::aaMqtt() 
{

} //aaMqtt::aaMqtt()

/**
 * @brief This is the destructor for this class.
 ===================================================================================================*/
aaMqtt::~aaMqtt() 
{
   
} //aaMqtt::~aaMqtt()

/**
 * @brief Connect to MQTT broker.
=================================================================================================== */
void aaMqtt::connect(IPAddress address, const char* uniqueName)
{
   _brokerIP = address;
   _uniqueName = uniqueName; // Prefix for all MQTT topic tree names.
   Serial.print("<aaMqtt::connect> Connecting as ");
   Serial.print(_uniqueName);
   Serial.print(" to MQTT broker at IP address ");
   Serial.print(_brokerIP);
   Serial.println(" ...");
   mqttClient.onConnect(onMqttConnect); // Define connection event.
   mqttClient.onDisconnect(onMqttDisconnect); // Define disconnect event.
   mqttClient.onSubscribe(onMqttSubscribe); // Define subscribe event.
   mqttClient.onUnsubscribe(onMqttUnsubscribe); // Define unsubscribe event.
   mqttClient.onMessage(onMqttMessage); // Define recieve message event.
   mqttClient.onPublish(onMqttPublish); // Define publish message event.
   mqttClient.setServer(_brokerIP, BROKER_PORT); // Set IP and port for broker service.  
   mqttClient.connect(); // Connect to broker.
} //aaMqtt::connect()

/**
 * @brief Handle CONNACK from the MQTT broker
 * @param sessionPresent persistent session available flag contained in CONNACK message from broker.
 * # CONNACK Message
 * The CONNACK message contains two data entries:
 * 1. The session present flag
 * 2. A connect acknowledge flag
 * 
 * ## Session Present Flag
 * The session present flag tells the client whether the broker already has a persistent session 
 * available from previous interactions with the client. When a client connects with Clean Session set 
 * to true, the session present flag is always false because there is no session available. If a client 
 * connects with Clean Session set to false, there are two possibilities: If session information is 
 * available for the client Id. and the broker has stored session information, the session present flag 
 * is true. Otherwise, if the broker does not have any session information for the client ID, the session 
 * present flag is false. This flag was added in MQTT 3.1.1 to help clients determine whether they need 
 * to subscribe to topics or if the topics are still stored in a persistent session.
 *
 * ## Connect Acknowledge Flag
 * The second flag in the CONNACK message is the connect acknowledge flag. This flag contains a return 
 * code that tells the client whether the connection attempt was successful. Here are the return codes 
 * at a glance:
 *
 * | Return Code | Return Code Response |  
 * |:-----------:|:------------------------------------------------------|
 * |  0  | Connection accepted |
 * |  1  | Connection refused, unacceptable protocol version |
 * |  2  | Connection refused, identifier rejected |
 * |  3  | Connection refused, server unavailable |
 * |  4  | Connection refused, bad user name or password |
 * |  5  | Connection refused, not authorized |
 =================================================================================================== */
void aaMqtt::onMqttConnect(bool sessionPresent)
{
   Serial.println("<onMqttConnect> Connected to MQTT");
   Serial.print("<onMqttConnect> Session present: ");
   Serial.println(sessionPresent);
//   uint16_t packetIdSub = mqttClient.subscribe((char *)cmdTopicMQTT.c_str(), MQTTQos); // QOS can be 0,1 or 2. controlled by MQTTQos parameter
   char buf[30];
   const char* topic = "/commands";
   strcpy(buf, _uniqueName);
   strcat(buf, topic);   
   cmdTopicMQTT = buf;   
   uint16_t packetIdSub = mqttClient.subscribe(cmdTopicMQTT, MQTT_QOS); // QOS can be 0,1 or 2. controlled by MQTTQos parameter
   Serial.print("<onMqttConnect> Subscribing to "); Serial.print(cmdTopicMQTT);
   Serial.print(" at a QOS of "); Serial.print(MQTT_QOS);
   Serial.print(" with a packetId of "); Serial.println(packetIdSub);
} //aaMqtt::onMqttConnect()

/**
 * @brief Handle disconnecting from an MQTT broker
 * @param reason Reason for disconnect
=================================================================================================== */
void aaMqtt::onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
   Serial.println("<onMqttDisconnect> Disconnected from MQTT");
   if (WiFi.isConnected())
   {
      xTimerStart(mqttReconnectTimer, 0); // Activate mqtt timer (which only runs 1 time)
   } //if
} //aaMqtt::onMqttDisconnect()

/**
 * @brief Handle SUBACK from MQTT broker
 * @param packetId Unique identifier of the message
 * @param qos SUBACK return code
 * # Suback Message
 * To confirm each subscription, the broker sends a SUBACK acknowledgement message to the client. This message contains the packet 
 * identifier of the original Subscribe message (to clearly identify the message) and a list of return codes.
 * ## Packet Identifier 
 * The packet identifier is a unique identifier used to identify a message. It is the same as in the SUBSCRIBE message.
 *
 * ##Return Code 
 * The broker sends one return code for each topic/QoS-pair that it receives in the SUBSCRIBE message. For example, if the SUBSCRIBE 
 * message has five subscriptions, the SUBACK message contains five return codes. The return code acknowledges each topic and shows 
 * the QoS level that is granted by the broker. If the broker refuses a subscription, the SUBACK message conains a failure return code 
 * for that specific topic. For example, if the client has insufficient permission to subscribe to the topic or the topic is malformed.
 *
 * # Table of SUBACK return codes
 * | Return Code | Return Code Response |  
 * |:-----------:|:----------------------------------|
 * |  0  |  Success - Maximum QoS 0 |
 * |  1  |  Success - Maximum QoS 1 |
 * |  2  |  Success - Maximum QoS 2 |
 * | 128 |  Failure |
=================================================================================================== */
void aaMqtt::onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
   Serial.println("<onMqttSubscribe> Subscribe acknowledged by broker.");
   Serial.print("<onMqttSubscribe>  PacketId: ");  Serial.println(packetId);
   Serial.print("<onMqttSubscribe>  QOS: ");       Serial.println(qos);
} //aaMqtt::onMqttSubscribe

/**
 * @brief Handle UNSUBACK message from MQTT broker
 * @param packetId Unique identifier of the message. This is the same packet identifier that is in the UNSUBSCRIBE message.
 * # UNSUBACK Message
 * To confirm the unsubscribe, the broker sends an UNSUBACK acknowledgement message to the client. This message contains only the 
 * packet identifier of the original UNSUBSCRIBE message (to clearly identify the message). After receiving the UNSUBACK from the 
 * broker, the client can assume that the subscriptions in the UNSUBSCRIBE message are deleted.
=================================================================================================== */
void aaMqtt::onMqttUnsubscribe(uint16_t packetId)
{
   // skipping adding this tiny bit to MQTT CPU tally
   Serial.println("Unsubscribe acknowledged.");
   Serial.print("  packetId: ");
   Serial.println(packetId);
} //aaMqtt::onMqttUnsubscribe()

/**
 * @brief Publish a message to the specified MQTT broker topic tree
 * @param topic The topic tree to publish the messge to
 * @param msg The message to send
 * # MQTT Published Messages
 * TWIPe issues a number of messages to the MQTT broker. Each message goes to it's own topic tree. These messages and their 
 * respective topic trees are outlined in the table below. Note hat the robot name is made up of the prefix twipe followed by the 
 * MAC address of the ESP32. This acts as a unique identifier of the robot and is used to ensure that each robot has its own 
 * unique data tree structure on the MQTT broker. THis design allows for multipple twipe robots to share the same MQTT broker.
 * ## Table of Published Messages 
 * | Topic                  | Topic Tree                       | Details                                                             |
 * |:-----------------------|:---------------------------------|:--------------------------------------------------------------------|
 * | Balance telemetry      | {robot name}/telemetry/balance   | Angle of IMU orientation in degrees                                 |
 * | Robot Metadata         | {robot name}/metadata            | See metadata table for a full list of the data points being tracked |
=================================================================================================== */
void aaMqtt::publishMQTT(String topic, String msg)
{
   String message = String(millis() ) + "," + msg; // prepend timestamp to message
   String mqttPrefix = String(_uniqueName) + String(topic);  // prepend robot name to MQTT topic
   mqttClient.publish((char *)mqttPrefix.c_str(), MQTT_QOS, false, (char *)message.c_str()); // QOS 0-2, retain t/f
   Serial.print("<aaMqtt::publishMQTT> Publish : ");
   Serial.print(mqttPrefix); Serial.print(",");
   Serial.println(message);
} //aaMqtt::publishMQTT()

/**
 * @brief Publishes messages to the health event topic on the MQTT broker.
 * @param int Event ID.
 * @param int Event severity?
 * @param String Event message.
 =================================================================================================== */
void aaMqtt::publishEvent(int evtId, int evtSev, String evtMsg)
{  
   publishMQTT("/hthEvt",String(evtId) +","+ String(evtSev) +","+String(evtMsg));
} //aaMqtt::publishEvent()

/**
 * @brief Handle incoming messages from MQTT broker
 * @details All messaging comes here and get seperated by select statement.
 * @param topic Which topic this message if about
 * @param payload The content of the message sent from the MQTT broker
 * @param properties A structure of flags with details from the message's packet header 
 * @param len Payload length. If unset or set to 0, the payload will be considered as a string and use 
 * strlen(payload) to calculte
 * @param index The message ID. If unset or set to 0, the message ID will be automtaically assigned
 * @param total Seems to be the same as len 
 * 
 * @note Property Flags
 * The MQTT message has a header containing the following flags.
 * ## QOS Flag
 * Two bits that show the QOS level of the message. Valid values are 1, 2 and 3
 * ## Retain Flag
 * Boolean value showing whether the message is saved by the broker as the last known good value for a specified topic. When a new 
 * client subscribes to a topic, they receive the last message that is retained on that topic. 
 * ## DUP flag 
 * Boolean value indicates that the message is a duplicate and was resent because the intended recipient (client or broker) did not 
 * acknowledge the original message. This is only relevant for QoS greater than 0.
 =================================================================================================== */
void aaMqtt::onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
   Serial.println("<onMqttMessage> Received message.");
   Serial.print("<onMqttMessage>  topic: ");
   Serial.println(topic);
   Serial.print("<onMqttMessage>  qos: ");
   Serial.println(properties.qos);
   Serial.print("<onMqttMessage>  dup: ");
   Serial.println(properties.dup);
   Serial.print("<onMqttMessage>  retain: ");
   Serial.println(properties.retain);
   Serial.print("<onMqttMessage>  len: ");
   Serial.println(len);
   Serial.print("<onMqttMessage>  index: ");
   Serial.println(index);
   Serial.print("<onMqttMessage>  total: ");
   Serial.println(total);
   Serial.print("<onMqttMessage>  payload: ");
   Serial.println(payload);
   String tmp = String(payload).substring(0, len);
   Serial.print("<onMqttMessage> Message to process = ");
   Serial.println(tmp);
} //aaMqtt::onMqttMessage()

/**
 * @brief Handle the reciept of a PUBACK message message from MQTT broker
 * @param packetId Unique identifier of the message.
 =================================================================================================== */
void aaMqtt::onMqttPublish(uint16_t packetId)
{

} //aaMqtt::onMqttPublish()

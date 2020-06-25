#ifndef ARDUINO_CREDENTIALS_H
#define ARDUINO_CREDENTIALS_H

/* WiFi Credentials to connect Internet */
#define STA_SSID "octo"
#define STA_PASS "12345678"

/* Provide MQTT broker credentials as denoted in maqiatto.com. */
#define MQTT_BROKER       "maqiatto.com"
#define MQTT_BROKER_PORT  1883
#define MQTT_USERNAME     "cgayan10@gmail.com"
#define MQTT_KEY          "pet123"


/* Provide topic as it is denoted in your topic list. 
 * For example mine is : cadominna@gmail.com/topic1
 * To add topics, see https://www.maqiatto.com/configure
 */
#define TOPIC    "cgayan10@gmail.com/petpointer"

#endif /* ARDUINO_CREDENTIALS_H */

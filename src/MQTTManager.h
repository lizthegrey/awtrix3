#ifndef MQTTManager_h
#define MQTTManager_h

#include <Arduino.h>
#include <map>

class MQTTManager_
{
private:
    MQTTManager_() = default;

public:
    static MQTTManager_ &getInstance();

    // startTask spawns a dedicated FreeRTOS task pinned to core 0 that runs
    // setup() (which performs the blocking TLS handshake) and then ticks the
    // MQTT loop. Keeps the main loop on core 1 responsive to HTTP requests
    // even while MQTT is mid-handshake (~10 s for AWS IoT Core's RSA-4096
    // cert chain on ESP32).
    void startTask();

    // isFirstConnectSettled reports whether the MQTT task has completed its
    // initial setup() call — connection succeeded OR failed. Used by main
    // setup() to block briefly so the rest of the OS doesn't start running
    // while MQTT is mid-handshake (which causes display/CPU contention).
    bool isFirstConnectSettled();

    void setup();
    void tick();
    void rawPublish(const char *prefix, const char *topic, const char *payload);
    void publish(const char *topic, const char *payload);
    void setCurrentApp(String);
    void sendStats();
    void sendButton(byte, bool);
    void setIndicatorState(uint8_t indicator, bool state, uint32_t color);
    void beginPublish(const char *topic, unsigned int plength, boolean retained);
    void writePayload(const char *data, const uint16_t length);
    void endPublish();
    bool subscribe(const char* topic);
    bool isConnected();
    String getValueForTopic(const String &topic);

};
extern MQTTManager_ &MQTTManager;

#endif
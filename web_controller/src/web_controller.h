#ifndef WEB_CONTROLLER_H
#define WEB_CONTROLLER_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <EEPROM.h>


struct Settings {
  int joystickRange1;
  int joystickRange2;
  String slider1Name;
  int slider1Range;
  String slider2Name;
  int slider2Range;
  int buttonTypes[10];
  String buttonNames[10];
};

class WebController {
  public:
    WebController(const char* ssid, const char* password);
    void begin();
    void loop();

    bool getButtonState(int index);
    int getSliderValue(int index);
    int getJoystickValue(int index, int axis);


  private:
    const char* ssid;
    const char* password;
    AsyncWebServer server;
    AsyncWebSocket ws;
    Settings settings;
    bool buttonStates[10];
    int sliderValues[2];
    int joystickValues[2][2];


    void setupWiFi();
    void setupWebSocket();
    void onWebSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len);
    void saveSettingsToEEPROM();
    void loadSettingsFromEEPROM();
    void writeStringToEEPROM(int addr, String str);
    String readStringFromEEPROM(int addr);
};

#endif

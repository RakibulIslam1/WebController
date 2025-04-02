#include "web_controller.h"

WebController::WebController(const char* ssid, const char* password)
  : ssid(ssid), password(password), server(80), ws("/ws") {
  memset(buttonStates, true, sizeof(buttonStates));
  memset(sliderValues, 0, sizeof(sliderValues));
  memset(joystickValues, 0, sizeof(joystickValues));
}


void WebController::begin() {

  setupWiFi();
  setupWebSocket();

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed! Formatting...");
    return;
  } else {
    Serial.println("SPIFFS Mounted Successfully!");
  }

  EEPROM.begin(1024);
  loadSettingsFromEEPROM();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/controller.html", "text/html");
  });

  server.on("/setting.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/setting.html", "text/html");
  });

  server.on("/controller.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/controller.html", "text/html");
  });

  server.addHandler(&ws);
  server.begin();
  for (int i = 0; i < 10; i++) {
    if (settings.buttonTypes[i] == 0 ) {
      buttonStates[i] = true;  
    } else {
      buttonStates[i] = false; 
    }
  }
}


void WebController::loop() {
  ws.cleanupClients();
}

void WebController::setupWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
}


void WebController::setupWebSocket() {
  ws.onEvent([this](AsyncWebSocket * server, AsyncWebSocketClient * client,
  AwsEventType type, void* arg, uint8_t* data, size_t len) {
    this->onWebSocketEvent(server, client, type, arg, data, len);
  });
}


void WebController::onWebSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket Client Connected");
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("WebSocket Client Disconnected");
  } else if (type == WS_EVT_DATA) {
    String message = "";
    for (size_t i = 0; i < len; i++) {
      message += (char)data[i];
    }
    //    Serial.println("Received: " + message);
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, message);
    if (!error) {
      const char* type = doc["type"];
      if (strcmp(type, "button") == 0) {
        String buttonId = doc["buttonId"];
        String state = doc["state"];

        //      Serial.print("Button ID: ");
        //      Serial.print(buttonId);
        //      Serial.print(" - State: ");
        //      Serial.println(state);
        int buttonIndex = buttonId.substring(6).toInt() - 1;
        if (state == "ON") {
          buttonStates[buttonIndex] = true;
        } else {
          buttonStates[buttonIndex] = false;
        }
      }
      else if (strcmp(type, "slider") == 0) {
        int sliderId = doc["sliderId"];
        int value = doc["value"];
        //      Serial.print("Slider ID: ");
        //      Serial.print(sliderId);
        //      Serial.print(" - Value: ");
        //      Serial.println(value);

        sliderValues[sliderId - 1] = value;
      }
      else if (strcmp(type, "joystick") == 0) {
        String joystickId = doc["joystickId"];
        int x = doc["x"];
        int y = doc["y"];
        //      Serial.print("Joystick ID: ");
        //      Serial.print(joystickId);
        //      Serial.print(" - X: ");
        //      Serial.print(x);
        //      Serial.print(" - Y: ");
        //      Serial.println(y);
        int joystickIndex = joystickId.substring(joystickId.length() - 1).toInt() - 1;
        joystickValues[joystickIndex][0] = x;
        joystickValues[joystickIndex][1] = y;
      }
      else if (strcmp(type, "save_settings") == 0) {
        JsonObject data = doc["data"];
        settings.joystickRange1 = data["joystickRange1"];
        settings.joystickRange2 = data["joystickRange2"];
        settings.slider1Name = data["slider1Name"].as<String>();
        settings.slider1Range = data["slider1Range"];
        settings.slider2Name = data["slider2Name"].as<String>();
        settings.slider2Range = data["slider2Range"];
        for (int i = 0; i < 10; i++) {
          settings.buttonTypes[i] = data[("button" + String(i + 1) + "Type")];
        }
        for (int i = 0; i < 10; i++) {
          settings.buttonNames[i] = data[String("button" + String(i + 1) + "Name")].as<String>();
        }

        saveSettingsToEEPROM();
        //      Serial.println("Settings saved to EEPROM.");
      }
      else if (strcmp(type, "request_settings") == 0) {
        loadSettingsFromEEPROM();
        DynamicJsonDocument response(1024);
        response["type"] = "settings_data";
        response["data"]["joystickRange1"] = settings.joystickRange1;
        response["data"]["joystickRange2"] = settings.joystickRange2;
        response["data"]["slider1Name"] = settings.slider1Name;
        response["data"]["slider1Range"] = settings.slider1Range;
        response["data"]["slider2Name"] = settings.slider2Name;
        response["data"]["slider2Range"] = settings.slider2Range;
        for (int i = 0; i < 10; i++) {
          response["data"][("button" + String(i + 1) + "Type")] = settings.buttonTypes[i];
        }
        for (int i = 0; i < 10; i++) {
          response["data"][String("button" + String(i + 1) + "Name")] = settings.buttonNames[i];
        }
        String jsonResponse;
        serializeJson(response, jsonResponse);
        client->text(jsonResponse);
        //      Serial.println("Sent settings to client");
      }
    }
  }
}

void WebController::saveSettingsToEEPROM() {
  EEPROM.write(0, settings.joystickRange1 / 4);
  EEPROM.write(4, settings.joystickRange2 / 4);
  writeStringToEEPROM(8, settings.slider1Name);
  EEPROM.write(28, settings.slider1Range / 4);
  writeStringToEEPROM(32, settings.slider2Name);
  EEPROM.write(52, settings.slider2Range / 4);

  for (int i = 0; i < 10; i++) {
    EEPROM.write(60 + i, settings.buttonTypes[i]);
    writeStringToEEPROM(80 + i * 20, settings.buttonNames[i]);
  }

  EEPROM.commit();
}

void WebController::loadSettingsFromEEPROM() {
  settings.joystickRange1 = EEPROM.read(0) * 4;
  settings.joystickRange2 = EEPROM.read(4) * 4;
  settings.slider1Name = readStringFromEEPROM(8);
  settings.slider1Range = EEPROM.read(28) * 4;
  settings.slider2Name = readStringFromEEPROM(32);
  settings.slider2Range = EEPROM.read(52) * 4;

  for (int i = 0; i < 10; i++) {
    settings.buttonTypes[i] = EEPROM.read(60 + i);
    settings.buttonNames[i] = readStringFromEEPROM(80 + i * 20);
  }
}

void WebController::writeStringToEEPROM(int addr, String str) {
  for (int i = 0; i < str.length(); i++) {
    EEPROM.write(addr + i, str[i]);
  }
  EEPROM.write(addr + str.length(), '\0');
}

String WebController::readStringFromEEPROM(int addr) {
  String str = "";
  char ch = EEPROM.read(addr);
  while (ch != '\0' && str.length() < 100) {
    str += ch;
    ch = EEPROM.read(addr + str.length());
  }
  return str;
}
bool WebController::getButtonState(int index) {
  if (index >= 0 && index < 10) return buttonStates[index];
  return false;
}

int WebController::getSliderValue(int index) {
  if (index >= 0 && index < 2) return sliderValues[index];
  return 0;
}
int WebController::getJoystickValue(int index, int axis) {
  if (index >= 0 && index < 2 && axis >= 0 && axis < 2)
    return joystickValues[index][axis];
  return 0;
}

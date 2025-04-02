# My Library for ESP32 Web Server and JSON Handling

This is a library for controlling an ESP32-based web server with support for reading/writing to the file system and handling JSON data. It uses the following libraries to support Wi-Fi connectivity, web server functionality, file system management, and EEPROM handling.

## License
This project is licensed under the **Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0)**. See the [LICENSE](LICENSE) file for details.
![CC BY-NC 4.0](https://licensebuttons.net/l/by-nc/4.0/88x31.png)

## Dependencies

This library requires the following libraries to work correctly:

- [WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/WiFi) - For Wi-Fi connectivity on ESP32.
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) - For setting up an asynchronous web server on the ESP32.
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) - For asynchronous TCP support required by ESPAsyncWebServer.
- [FS](https://github.com/esp8266/Arduino/tree/master/libraries/FS) - For file system operations on ESP32.
- [SPIFFS](https://github.com/esp8266/Arduino/tree/master/libraries/SPIFFS) - For managing files in SPIFFS (Serial Peripheral Interface Flash File System).
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) - For handling JSON data.
- [EEPROM](https://github.com/esp8266/Arduino/tree/master/libraries/EEPROM) - For reading and writing to the EEPROM on ESP32.

## Installation Instructions

To use this library, you will need to install the following dependencies. You can do so via the **Arduino IDE** or **PlatformIO**.

### Using the Arduino IDE:

1. Open **Arduino IDE**.
2. Go to **Sketch > Include Library > Manage Libraries**.
3. In the **Library Manager**, search for each of the following libraries and click **Install**:
   - WiFi
   - ESPAsyncWebServer
   - AsyncTCP
   - FS
   - SPIFFS
   - ArduinoJson
   - EEPROM

### Using PlatformIO:

If you're using **PlatformIO**, add the following dependencies in your `platformio.ini` file:

```ini
[env:esp32]
platform = espressif32
framework = arduino
lib_deps =
  WiFi
  ESPAsyncWebServer
  AsyncTCP
  FS
  SPIFFS
  ArduinoJson
  EEPROM

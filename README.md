# My Library for ESP32 Web Server based controller

This is a library for controlling an ESP32-based web server with support for reading/writing to the file system and handling JSON data. It provides a customizable controller interface, allowing you to configure buttons, sliders, and joysticks, and save settings both in local storage and EEPROM. It supports multi-touch input, allowing multiple joysticks to work simultaneously.

## Features
- **Button Types**: You can select between different button types, including **Push Buttons** and **Toggle Switches**. The user can change the button name and type directly from the settings interface.
- **Slider Configuration**: Sliders can be named and their range can be customized, offering flexibility for controlling various parameters.
- **Joystick Configuration**: Joysticks' ranges can be adjusted to suit different applications. The controller supports multi-touch, allowing multiple joysticks to work at the same time.
- **Settings Management**: All user settings (button names, types, slider ranges, joystick ranges) can be modified in the settings interface. These settings are saved in both **local storage** and the **EEPROM** of the ESP32, ensuring that the settings persist even after a device reset.
- **Device Independence**: Once settings are saved to EEPROM, they are available on any device using the project. This allows for easy configuration across multiple devices.

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

## Project Structure

The library requires the following file structure for proper operation:

- **controller.html**: The main interface for controlling the ESP32 via the web server. It contains buttons, sliders, and joysticks.
- **settings.html**: The settings interface where users can customize the button names, types, slider ranges, joystick ranges, and other parameters.

These files should be placed in the `/data` folder of your Arduino project. When the project is uploaded to the ESP32, these HTML files will be served from the ESP32's file system.

## Settings Management

- **Local Storage**: Settings are first saved to the user's local storage on the device (e.g., browser). This allows the settings to persist across page reloads.
- **EEPROM**: Additionally, settings are saved to the EEPROM on the ESP32. This ensures that even after a power cycle, the settings remain intact, allowing for easy use across different devices.
- **First-Time Setup**: The first time the ESP32 is connected, settings are loaded from the EEPROM if available, or default settings are used. If settings are changed, they are saved back to both local storage and EEPROM to persist across devices.

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


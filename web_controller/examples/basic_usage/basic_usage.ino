/**
 * WebController Joystick & Sliders Example
 * 
 * This example demonstrates how to use the WebController library 
 * to read joystick positions, button states, and slider values.
 * 
 * Components:
 * - ESP32
 * - WebSocket-based WebController
 * 
 * Author: Rakibul Islam
 * License: CC BY-NC 4.0
 */

#include "web_controller.h"

// WiFi Credentials
const char* ssid = "BDOSN4";
const char* password = "Bdosn2023@";

// Create the WebController object with WiFi credentials
WebController webController(ssid, password);

void setup() {
    Serial.begin(115200);
    webController.begin(); // Initialize the WebController
}

void loop() {
    webController.loop(); // Handle WebSocket communication

    // Read joystick values
    int joystick1X = webController.getJoystickValue(0, 0);
    int joystick1Y = webController.getJoystickValue(0, 1);
    int joystick2X = webController.getJoystickValue(1, 0);
    int joystick2Y = webController.getJoystickValue(1, 1);

    Serial.print("Joystick 1: X="); Serial.print(joystick1X);
    Serial.print(" Y="); Serial.println(joystick1Y);

    Serial.print("Joystick 2: X="); Serial.print(joystick2X);
    Serial.print(" Y="); Serial.println(joystick2Y);

    // Read button states
    for (int i = 0; i < 10; i++) {
        Serial.print("Button "); Serial.print(i + 1);
        Serial.print(": "); Serial.println(webController.getButtonState(i) ? "ON" : "OFF");
    }

    // Read slider values
    for (int i = 0; i < 2; i++) {
        Serial.print("Slider "); Serial.print(i + 1);
        Serial.print(": "); Serial.println(webController.getSliderValue(i));
    }

    delay(500); // Adjust delay as needed
}

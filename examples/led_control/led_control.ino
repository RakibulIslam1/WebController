/**
 * WebController LED Control Example
 * 
 * This example demonstrates how to use the WebController library 
 * to control an LED using a button from the WebSocket-based controller.
 * 
 * Components:
 * - ESP32
 * - LED connected to pin 2
 * 
 * Author: Rakibul Islam
 * License: CC BY-NC 4.0
 */

#include "web_controller.h"

#define LED_PIN 2

const char* ssid = "YOUR SSID";       // Your WiFi SSID
const char* password = "YOUR PASSWORD"; // Your WiFi Password

// Create the WebController object with WiFi credentials
WebController webController(ssid, password);

void setup() {
    Serial.begin(115200);
    webController.begin(); // Initialize the WebController
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    webController.loop(); // Handle WebSocket communication
    
    // Get the status of button 0 from the web controller
    bool buttonState = webController.getButtonState(0);

    // Control the LED based on button state
    digitalWrite(LED_PIN, buttonState ? HIGH : LOW);
}

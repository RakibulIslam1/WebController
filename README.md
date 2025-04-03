# Library for ESP32 Web Server based controller

This is a library for an ESP32 web server based controller that anyone can use for their project. It supports 10 buttons, 2 sliders, and 2 joysticks. It provides a customizable controller interface, allowing you to configure buttons, sliders, and joysticks, and save settings both in local storage and EEPROM. It supports multi-touch input, allowing multiple joysticks to work simultaneously.

![cntroller face](https://i.imgur.com/K4Y7zn1.jpeg)


## 🚀 Features  

### 🎛️ Customizable Buttons  
- Supports **Push Buttons** and **Toggle Switches**.  
- Easily modify **button names and types** from the settings interface.  

### 🎚️ Flexible Sliders  
- Customize **slider names and ranges** to match your project requirements.  

### 🎮 Advanced Joystick Support  
- Adjust **joystick range settings** for better precision.  
- Supports **multi-touch**, enabling both joysticks to work simultaneously.  

### ⚙️ Smart Settings Management  
- Modify **button names, types, slider ranges, and joystick ranges** through an intuitive settings menu.  
- Settings are stored in **local storage** and **ESP32’s EEPROM**, ensuring persistence even after resets.  

### 📱 Device-Independent Configuration  
- Once saved in **EEPROM**, settings remain intact across all devices using the controller—**no need to reconfigure for each device!**  


### 🖥️ Full-Screen Mode for App-Like Experience  
- A **Full-Screen Button** is available at the **top left** of the interface.  
- When activated, the controller enters **full-screen mode**, making it feel like a native app.  
- Enhances **usability and immersive experience** for touchscreen devices.  


## 📂 Project File Structure  

Your Arduino project should be structured as follows:  /YourProjectName │── /data │ ├── controller.html │ ├── settings.html │── YourProjectName.ino │── OtherRequiredFiles.ino

Ensure that the `data` folder contains `controller.html` and `settings.html` before uploading files to SPIFFS.
- **controller.html**: The main interface for controlling the ESP32 via the web server. It contains buttons, sliders, and joysticks.
- **settings.html**: The settings interface where users can customize the button names, types, slider ranges, joystick ranges, and other parameters.
### 📸 Screenshot  
Here is a visual representation of the project structure:  
![file structure](https://i.imgur.com/AL3KFws.gif)


## 📂 SPIFFS Data Upload Setup(For storing the html file in esp32)

To upload website files stored in the **data** folder to ESP32’s SPIFFS, follow these steps:

### 1️⃣ Download the ESP32FS Tool  
📥 **[Download ESP32FS](https://drive.google.com/drive/folders/11EEOcLqq2jrCHOm5m8uCgVdsFf61-r1m?usp=sharing)**

### 2️⃣ Install the Tool in Arduino  
- **Check if the `tools` folder exists**:  
  - Navigate to: `Documents/Arduino/`
  - If there is no `tools` folder, **create one**.
- **Paste the downloaded `ESP32FS` folder** inside `tools`:  
  ```
  Documents/Arduino/tools/ESP32FS/tool/esp32fs.jar
  ```
- The file structure should be like this-
  ![file structure](https://i.imgur.com/fV7ENEP.png)

### 3️⃣ Restart Arduino IDE  
- Close and reopen Arduino IDE.  
- Now, you should see **"ESP32 Sketch Data Upload"** under the **Tools** menu.

### 4️⃣ Upload SPIFFS Data  
- Open your project in **Arduino IDE**.
- Click **"ESP32 Sketch Data Upload"** in the Tools menu.
- Wait for the upload to complete.
### You will see the uploader tool like this :-
 ![Tools](https://i.imgur.com/f3jr4NZ.png)
### The debug message should be like this :-
![message](https://i.imgur.com/4FxtePx.png)

✅ Now, your website files in the **data** folder are stored in ESP32’s SPIFFS! 🚀



## ⚙️ Settings Management  

### 🔹 Local Storage  
- Settings are first saved in the **browser’s local storage**.  
- This ensures settings remain intact even after refreshing the page.  

### 🔹 EEPROM (ESP32 Memory)  
- All settings are stored in the **ESP32's EEPROM**, preserving them even after a power cycle.  
- This allows you to use the controller on multiple devices without reconfiguring.  

### 🔹 First-Time Setup  
- When the ESP32 is connected for the first time:  
  - It attempts to load settings from EEPROM.  
  - If no saved settings are found, default values are used.  
  - Any changes made are saved both in **local storage** and **EEPROM** for persistence.  

## 📸 Settings Interface Preview  

| Slider Configuration | Button Configuration | Theme Settings |
|----------------------|----------------------|----------------|
| ![Slider settings](https://i.imgur.com/n12yPsc.jpeg) | ![Button Settings](https://i.imgur.com/S7hRldQ.jpeg) | ![Theme Settings](https://i.imgur.com/nFLCo8y.jpeg) |




## Dependencies

This library requires the following libraries to work correctly:

- [WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/WiFi) - For Wi-Fi connectivity on ESP32.
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) - For setting up an asynchronous web server on the ESP32.
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) - For asynchronous TCP support required by ESPAsyncWebServer.
- [FS](https://github.com/esp8266/Arduino/tree/master/libraries/FS) - For file system operations on ESP32.
- [SPIFFS](https://github.com/esp8266/Arduino/tree/master/libraries/SPIFFS) - For managing files in SPIFFS (Serial Peripheral Interface Flash File System).
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) - For handling JSON data.
- [EEPROM](https://github.com/esp8266/Arduino/tree/master/libraries/EEPROM) - For reading and writing to the EEPROM on ESP32.
## 📥 Installation Instructions

### Installing the Main Library:

To use the main library in your project, follow these steps:

1. Download the library from the [GitHub repository](https://github.com/your-repo-url).
2. Go to **Sketch > Include Library > Add .ZIP Library** in the Arduino IDE.
3. Select the downloaded `.zip` file and click **Open** to add the library to your project.




### To use this library, you will need to install the following dependencies. 

1. Open **Arduino IDE**.
2. Go to **Sketch > Include Library > Manage Libraries**.
3. In the **Library Manager**, search for each of the following libraries and click **Install**:
   - **WiFi**: For connecting the ESP32 to a Wi-Fi network.
   - **ESPAsyncWebServer**: For handling web server functionalities asynchronously.
   - **AsyncTCP**: A required library for `ESPAsyncWebServer` to function correctly.
   - **FS**: Filesystem support for the ESP32.
   - **SPIFFS**: SPI Flash File System for the ESP32 to store and serve files.
   - **ArduinoJson**: For working with JSON data, useful in web applications.
   - **EEPROM**: For reading and writing data to the EEPROM on the ESP32.


Once you have completed these steps, you are ready to start using the library in your ESP32 project!

## 📦 EEPROM Usage Restriction

If you plan to use **EEPROM** in your project, please note the following restrictions:

- The **EEPROM** address range **0 to 110** is reserved for the library’s internal use.
- You **must not** use this range for your own data.
- The remaining **EEPROM** addresses (from **111 onward**) are available for you to use freely.

Ensure that you avoid using addresses **0 to 110** in your EEPROM operations to prevent conflicts with the library’s settings and functionality.

## 💡 Example: WebController LED Control

This example demonstrates controlling an LED on pin 2 of the ESP32 using a button from this WebSocket-based controller.

### How to Access the Example:

1. Open **Arduino IDE**.
2. Go to **File > Examples > WebController > led_control**.
3. Upload the code to your ESP32.

### How It Works:

- The ESP32 connects to WiFi and listens for button presses from the web interface.
- The LED on **pin 2** is controlled as follows:
  - If the button is configured as a **push button** in the settings, it will turn **ON** when pressed and **OFF** when released.
  - If the button is configured as a **toggle button**, pressing it will **toggle** the LED state (ON/OFF), keeping the state until the button is pressed again.
    
### How to Get the IP Address:

1. Open **Serial Monitor** in the **Arduino IDE** (Tools > Serial Monitor).
2. Make sure **Autoscroll** is turned off.
3. Press the **EN (Enable)** button on the ESP32 to reset it.
4. Once the ESP32 connects to WiFi, the **IP address** will be displayed on the Serial Monitor.
5. Copy the displayed IP address.
6. Open your browser and paste the IP address into the URL bar to access the WebController interface.

### Video Demonstration:

Below is a Video showing how the button controls the LED:

![LED Control Demo](https://i.imgur.com/KOoxMIB.gif)


## 🛡️ License  

This project is licensed under the **Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0)**.  

You are free to:  
✔️ Share — Copy and redistribute the material in any medium or format.  
✔️ Adapt — Remix, transform, and build upon the material.  

**Under the following terms:**  
⚠️ **Attribution** — You must give appropriate credit and indicate if changes were made.  
🚫 **NonCommercial** — You may not use the material for **commercial purposes**.  

For full license details, see the [LICENSE](LICENSE) file.  

![CC BY-NC 4.0](https://licensebuttons.net/l/by-nc/4.0/88x31.png)  

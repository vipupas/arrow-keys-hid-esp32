## 🕹️ I created a custom Arrow Keys controller using:

    4 push buttons (⬆️⬇️⬅️➡️)

    ESP32 with Bluetooth HID to emulate keyboard inputs

    An OLED display to show real-time button press status

###🔧 Once paired with a computer via Bluetooth, this device works just like arrow keys on a keyboard — perfect for accessibility devices, DIY gaming setups, or just exploring the power of microcontrollers.

###💡 It was a great hands-on experience with Bluetooth HID profiles, real-time display via OLED, and understanding human-machine interfaces.

## Hardware Required :
#### Esp32 dev module
#### 4 push buttons
#### oled display 1.3 inches I2C (optional)
#### wires
#### breadboard


## Software Required :
#### Arduino ide { with the setup for esp32 }
- (Make sure you can use the ESP32 with the Arduino IDE. [Instructions can be found here.](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions))
- esp32 board manager version 2.0.11
  
## Procedure :
1. make sure you choose esp32 board manager version 2.0.11 .
2. special thank you T-vk for this library ```BleKeyboard.h``` .
   - [Download the latest release of this library from the release page.](https://github.com/T-vK/ESP32-BLE-Keyboard/releases)
   - In the Arduino IDE go to "Sketch" -> "Include Library" -> "Add .ZIP Library..." and select the file you just downloaded.
3. [make ready with library for oled display from here](https://randomnerdtutorials.com/esp32-ssd1306-oled-display-arduino-ide)
4. after all of this upload the code .


##Simulation Link:
https://wokwi.com/projects/438261816773655553


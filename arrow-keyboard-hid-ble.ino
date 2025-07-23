#include <BleKeyboard.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

bool wasConnected = false;  // track previous state

// --- OLED Setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- BLE Keyboard ---
BleKeyboard bleKeyboard;

// --- Button Pins ---
const int UP_BUTTON = 4;
const int DOWN_BUTTON = 23;
const int LEFT_BUTTON = 14;
const int RIGHT_BUTTON = 19;

// --- Button States ---
bool upPressed = false;
bool downPressed = false;
bool leftPressed = false;
bool rightPressed = false;

// --- Debounce ---
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// --- Display State ---
String lastArrow = "";

void showArrow(String dir) {
  if (dir != lastArrow) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.print("Arrow:");
    display.setCursor(0, 45);
    display.print(dir);
    display.display();
    lastArrow = dir;
  }
}

void setup() {
  Serial.begin(115200);
  // display.println("Starting ESP32 Arrow Keys...");
  Serial.println("Starting ESP32 Arrow Keys...");

  // OLED init
  Wire.begin(21, 22); // SDA = 21, SCL = 22
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  // display.println("Starting ESP32 Arrow Keys...");
  display.println("Arrow Keys");
  display.display();
  delay(1000);

  // Button init
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);

  // BLE init
  bleKeyboard.begin();
  // display.println("Waiting for BLE connection...");
  Serial.println("Waiting for BLE connection...");
}

void loop() {
  if (bleKeyboard.isConnected()) {
    // If just connected now
    if (!wasConnected) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 20);
      display.println("Connected");
      display.display();
      Serial.println("BLE Connected!");
      wasConnected = true;
      delay(500);  // brief delay to show "Connected" before key presses
    }

    // Arrow key handling (same as before)
    bool upState = !digitalRead(UP_BUTTON);
    bool downState = !digitalRead(DOWN_BUTTON);
    bool leftState = !digitalRead(LEFT_BUTTON);
    bool rightState = !digitalRead(RIGHT_BUTTON);

    if (upState && !upPressed) {
      bleKeyboard.press(KEY_UP_ARROW);
      upPressed = true;
      Serial.println("UP pressed");
      showArrow("UP");
      delay(debounceDelay);
    } else if (!upState && upPressed) {
      bleKeyboard.release(KEY_UP_ARROW);
      upPressed = false;
      Serial.println("UP released");
    }

    if (downState && !downPressed) {
      bleKeyboard.press(KEY_DOWN_ARROW);
      downPressed = true;
      Serial.println("DOWN pressed");
      showArrow("DOWN");
      delay(debounceDelay);
    } else if (!downState && downPressed) {
      bleKeyboard.release(KEY_DOWN_ARROW);
      downPressed = false;
      Serial.println("DOWN released");
    }

    if (leftState && !leftPressed) {
      bleKeyboard.press(KEY_LEFT_ARROW);
      leftPressed = true;
      Serial.println("LEFT pressed");
      showArrow("LEFT");
      delay(debounceDelay);
    } else if (!leftState && leftPressed) {
      bleKeyboard.release(KEY_LEFT_ARROW);
      leftPressed = false;
      Serial.println("LEFT released");
    }

    if (rightState && !rightPressed) {
      bleKeyboard.press(KEY_RIGHT_ARROW);
      rightPressed = true;
      Serial.println("RIGHT pressed");
      showArrow("RIGHT");
      delay(debounceDelay);
    } else if (!rightState && rightPressed) {
      bleKeyboard.release(KEY_RIGHT_ARROW);
      rightPressed = false;
      Serial.println("RIGHT released");
    }

  } else {
    // If just disconnected
    if (wasConnected) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 20);
      display.println("Waiting...");
      display.display();
      Serial.println("BLE Disconnected");
      wasConnected = false;
    }
  }

  delay(10);
}

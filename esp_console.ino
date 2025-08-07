#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <pitches.h>
#include <Sprite.h>

#define DISP_H 64
#define DISP_W 128
#define DISP_ADDR 0x3c
#define BTN_RGHT 7 
#define BTN_LEFT 20
#define BTN_SLCT 10
#define BUZZ 21

const uint8_t rocket_img[] PROGMEM = {
  0x01, 0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x07, 0xC0, 0x0F, 0xE0, 0x1F, 0xF0, 0x03, 0x80
};

const uint8_t enmy_img[] PROGMEM = {
  0x0F, 0xF0, 0x1F, 0xF8, 0x31, 0x8C, 0x75, 0xAE, 0x71, 0x8E, 0x3F, 0xFC, 0x1F, 0xF8, 0x0C, 0x30
};

Sprite rocket(16, 8, 0, 0, rocket_img);
Sprite enemy(16, 8, 20, 10, enmy_img);

Adafruit_SSD1306 display(DISP_W, DISP_H, &Wire, -1);

void setup() {
  pinMode(BTN_LEFT, INPUT);
  pinMode(BTN_RGHT, INPUT);
  pinMode(BTN_SLCT, INPUT);
  pinMode(BUZZ, OUTPUT);
  if (!display.begin(SSD1306_SWITCHCAPVCC, DISP_ADDR)) {}
  display.clearDisplay();
  display.drawBitmap(rocket.x, rocket.y, rocket.bit_map, rocket.width, rocket.height, WHITE);
  display.drawBitmap(enemy.x, enemy.y, enemy.bit_map, enemy.width, enemy.height, WHITE);
  display.display();
}

void loop() {

}

void play_space() {

}


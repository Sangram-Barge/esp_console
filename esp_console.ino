#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Sprite.h>


#define DISP_H 64
#define DISP_W 128
#define DISP_ADDR 0x3c
#define BTN_RGHT 5 
#define BTN_LEFT 21
#define BTN_SLCT 1
#define BUZZ 6

const uint8_t rocket_img[] PROGMEM = {
  0x01, 0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x07, 0xC0, 0x0F, 0xE0, 0x1F, 0xF0, 0x03, 0x80
};

const uint8_t enmy_img[] PROGMEM = {
  0x0F, 0xF0, 0x1F, 0xF8, 0x31, 0x8C, 0x75, 0xAE, 0x71, 0x8E, 0x3F, 0xFC, 0x1F, 0xF8, 0x0C, 0x30
};

const uint8_t bullet_img[] PROGMEM = {
  0x20, 0x70, 0x70, 0x70
};

Sprite rocket(16, 8, DISP_W/2, DISP_H-20, rocket_img);
Sprite enemy(16, 8, 20, 10, enmy_img);

Adafruit_SSD1306 display(DISP_W, DISP_H, &Wire, -1);
const int enemy_cnt = 20;
Sprite enemies[enemy_cnt];

void setup() {
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RGHT, INPUT_PULLUP);
  pinMode(BTN_SLCT, INPUT_PULLUP);
  pinMode(BUZZ, OUTPUT);
  randomSeed(analogRead(A0));
  if (!display.begin(SSD1306_SWITCHCAPVCC, DISP_ADDR)) {}
  display.clearDisplay();
  create_enemies();
  display.display();
}

int btn_pressed(int btn) {
  int is_pressed = !digitalRead(btn);
  if (is_pressed) delay(5);
  return is_pressed;
}

void update_space_display() {
  display.drawBitmap(rocket.x, rocket.y, rocket.bit_map, rocket.width, rocket.height, WHITE);
  for(int i = 0; i < enemy_cnt; i++) display.drawBitmap(
    enemies[i].x, enemies[i].y,
    enemies[i].bit_map,
    enemies[i].width, enemies[i].height,
    WHITE
  );
  display.display();
}

void create_enemies() {
  for (int i = 0; i < enemy_cnt; i++) {
    enemies[i].width = 16;
    enemies[i].height = 8;
    enemies[i].x = random(0, DISP_W);
    enemies[i].y = random(-DISP_H * 4, 0);
    enemies[i].bit_map = enmy_img;
    enemies[i].isDead = false;
  }
}

void play_space() {
  int rocket_speed = 4;
  display.clearDisplay();
  if (btn_pressed(BTN_LEFT) && !(rocket.x < 0)) rocket.move_x(-rocket_speed);
  if (btn_pressed(BTN_RGHT) && !(rocket.x > DISP_W - rocket.width)) rocket.move_x(rocket_speed);
  for (int i = 0; i < enemy_cnt; i++) {
    enemies[i].y++;
  }
  update_space_display();
  delay(20);
}

void loop() {
  play_space();
}




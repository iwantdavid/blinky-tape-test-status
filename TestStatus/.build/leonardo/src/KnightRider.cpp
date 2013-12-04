#include <Arduino.h>
void setup();
void pulse(int wait_time);
void solid_color(char color);
void set_rgb(int r, int g, int b);
void loop();
#line 1 "src/KnightRider.ino"
#include <FastSPI_LED2.h>
#include <Animation.h>

#define LED_COUNT 60
struct CRGB leds[LED_COUNT];

#define PIN_BUTTON 10
#define PIN_IO_A   7
#define PIN_IO_B   11
#define PIN_SIGNAL 13
#define PIN_INPUT  10

bool pulsing = false;

void setup()
{
  LEDS.addLeds<WS2811, PIN_SIGNAL, GRB>(leds, LED_COUNT); // this configures the BlinkyBoard - leave as is.
  LEDS.showColor(CRGB(0, 0, 0));
  LEDS.setBrightness(0); // Limit max current draw to 1A
  LEDS.show();
}


void pulse(int wait_time) {
  // let's fade up by scaling the brightness - in general, brightness shouldn't go above 93, so the strip won't draw too much power.
  // Oh, and 93 is plenty bright!
  // now let's fade down by scaling the brightness
  for(int scale = 93; scale > 0; scale--) {
    LEDS.setBrightness(scale);
    LEDS.show();
    delay(wait_time);
  }
  for(int scale = 0; scale < 93; scale++) {
    LEDS.setBrightness(scale);
    LEDS.show();
    delay(wait_time);
  }
}

void solid_color(char color) {
  switch(color) {
    case 'r':
      set_rgb(254, 0, 0);
      break;
    case 'g':
      set_rgb(0, 254, 0);
      break;
    case 'y':
      set_rgb(254, 254, 0);
      break;
    case 'w':
      set_rgb(254, 254, 254);
      break;
  }
}

void set_rgb(int r, int g, int b) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB(r,g,b);
  }

  LEDS.setBrightness(93);
  LEDS.show();
}

void loop() {
  if(Serial.available() > 2) {
    char mode  = Serial.read();
    char color = Serial.read();
    Serial.read(); // EOF char?

    solid_color(color);
    pulsing = (mode == 'p');
  }

  if(pulsing) {
    pulse(5);
  }
}

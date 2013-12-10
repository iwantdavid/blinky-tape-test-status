#include <FastSPI_LED2.h>
#include <Animation.h>

#define LED_COUNT 60
struct CRGB leds[LED_COUNT];

#define PIN_BUTTON 10
#define PIN_IO_A   7
#define PIN_IO_B   11
#define PIN_SIGNAL 13
#define PIN_INPUT  10

int pulse_interval;
char mColor;

void setup()
{
  pulse_interval = 0;
  mColor = 't';

  LEDS.addLeds<WS2811, PIN_SIGNAL, GRB>(leds, LED_COUNT); // this configures the BlinkyBoard - leave as is.
  LEDS.showColor(CRGB(0, 0, 0));
  LEDS.setBrightness(93); // Limit max current draw to 1A
  LEDS.show();
}

bool is_color(char character) {
  return (character == 'r' || character == 'g' || character == 'b' || character == 'y' || character == 'w');
}

void pulse() {
  if (pulse_interval < 0) {
    LEDS.setBrightness(93);
    return;
  }

  int now = (millis() / pulse_interval) % 186;
  LEDS.setBrightness(abs(93 - now));
  LEDS.show();
}

void rainbow() {
  int now = millis() / 50;
  int r = now;
  int g = now + 84;
  int b = now + 84 + 84;

  for (uint8_t i = 0; i < LED_COUNT; i++) {
    leds[i].r = (r + i) % 254;
    leds[i].g = (g + i) % 254;
    leds[i].b = (b + i) % 254;
  }
  LEDS.show();
}

void set_color(char character) {
  switch(character) {
    case 'r':
    case 'g':
    case 'b':
    case 'y':
    case 'w':
    case 't':
    case 'x':
      mColor = character;
      return;
    }
}

void color() {
  switch(mColor) {
    case 'r':
      set_rgb(254, 0, 0);
      return;
    case 'g':
      set_rgb(0, 254, 0);
      return;
    case 'b':
      set_rgb(0, 0, 254);
      return;
    case 'y':
      set_rgb(254, 254, 0);
      return;
    case 'w':
      set_rgb(254, 254, 254);
      return;
    case 't':
      test_sequence();
      return;
    case 'x':
      rainbow();
      return;
  }
}

void set_pulse_interval(char mode) {
  switch(mode) {
    case 'f':
      pulse_interval = 2;
      return;
    case 'p':
      pulse_interval = 5;
      return;
    case 's':
      pulse_interval = 0;
      return;
  }
}

void set_rgb(int r, int g, int b) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB(r,g,b);
  }
  LEDS.show();
}

void test_sequence() {
  int interval = 254 / LED_COUNT;
  for(int i=0; i < LED_COUNT; i += 1) {
    leds[i] = CRGB(254 - (i * interval), 0, (i * interval));
  }
  LEDS.show();
}

void loop() {
  while(Serial.available() > 0) {
    char character = Serial.read();
    set_color(character);
    set_pulse_interval(character);
  }

  color();
  pulse();
}

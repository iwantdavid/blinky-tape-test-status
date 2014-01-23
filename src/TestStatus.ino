#include <FastSPI_LED2.h>
#include <Animation.h>

#define LED_COUNT 60
struct CRGB leds[LED_COUNT];

#define PIN_BUTTON 10
#define PIN_IO_A   7
#define PIN_IO_B   11
#define PIN_SIGNAL 13
#define PIN_INPUT  10

int mPulseInterval;
char mColor;
int mBrightness;
int mTimer;

void setup()
{
  mPulseInterval = 0;
  mColor = ' ';
  mTimer = 30;
  mBrightness = 93;
  timer();

  LEDS.addLeds<WS2811, PIN_SIGNAL, GRB>(leds, LED_COUNT); // this configures the BlinkyBoard - leave as is.
  LEDS.showColor(CRGB(0, 0, 0));
  LEDS.setBrightness(mBrightness); // Limit max current draw to 1A
  LEDS.show();
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

bool is_color(char character) {
  return (character == 'r' || character == 'g' || character == 'b' || character == 'y' || character == 'w');
}

void pulse() {
  if (mPulseInterval <= 0) {
    LEDS.setBrightness(mBrightness);
    return;
  }

  int now = (millis() / mPulseInterval) % (93 * 2);
  int phase = 93 - now;
  LEDS.setBrightness(abs(phase * mBrightness / 93));
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

void set_brightness(char character) {
  if (character < 48 || 57 < character) {
    return;
  }

  mBrightness = (character - 48) * 10;
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

void set_pulse_interval(char mode) {
  switch(mode) {
    case 'f':
      mPulseInterval = 2;
      return;
    case 'k':
      mPulseInterval = 1;
      return;
    case 'p':
      mPulseInterval = 4;
      return;
    case 's':
      mPulseInterval = 0;
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

void set_timer(char character) {
  switch(character) {
    case 'u':
      mTimer = 30;
      return;
    case 'i':
      mTimer = 2;
      return;
  }
}

void timer() {
  int now = millis() / 600;
  switch(mTimer) {
    case 30:
      mColor = ' ';
      for (uint8_t i = 0; i < LED_COUNT; i++) {
        if (i < now) {
          leds[i].r = 254;
          leds[i].g = 254;
          leds[i].b = 254;
        } else {
          leds[i].r = 0;
          leds[i].g = 0;
          leds[i].b = 0;
        }
      }
      LEDS.show();
      return;
  }
}

void loop() {
  while(Serial.available() > 0) {
    char character = Serial.read();
    set_brightness(character);
    set_color(character);
    set_pulse_interval(character);
    set_timer(character);
  }

  color();
  pulse();
  timer();
}

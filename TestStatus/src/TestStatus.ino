#include <FastSPI_LED2.h>
#include <Animation.h>

#define LED_COUNT 60
struct CRGB leds[LED_COUNT];

#define PIN_BUTTON 10
#define PIN_IO_A   7
#define PIN_IO_B   11
#define PIN_SIGNAL 13
#define PIN_INPUT  10

long last_time;
int pulse_interval;

void setup()
{
  last_time = millis();
  pulse_interval = 0;

  LEDS.addLeds<WS2811, PIN_SIGNAL, GRB>(leds, LED_COUNT); // this configures the BlinkyBoard - leave as is.
  LEDS.showColor(CRGB(0, 0, 0));
  LEDS.setBrightness(93); // Limit max current draw to 1A
  LEDS.show();
  test_sequence();
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

int parse_pulse_interval(char mode) {
  switch(mode) {
    case 'f':
      return 2;
    case 'p':
      return 5;
    case 'x':
      return -1;
    default:
      return 0;
  }
}

void rainbow() {
  static uint8_t i = 0;
  static int j = 0;
  static int f = 0;
  static int k = 0;
  static int count;

  static int pixelIndex;

  for (uint8_t i = 0; i < LED_COUNT; i++) {
    leds[i].r = 64*(1+sin(i/2.0 + j/4.0       ));
    leds[i].g = 64*(1+sin(i/1.0 + f/9.0  + 2.1));
    leds[i].b = 64*(1+sin(i/3.0 + k/14.0 + 4.2));

    if ((millis() - last_time > 15) && pixelIndex <= LED_COUNT + 1) {
      last_time = millis();
      count = LED_COUNT - pixelIndex;
      pixelIndex++;
    }

    // why is this per LED?
    for (int x = count; x >= 0; x--) {
      leds[x] = CRGB(0, 0, 0);
    }

  }
  LEDS.show();

  j = j + 1;
  f = f + 1;
  k = k + 2;
}

void solid_color(char color) {
  switch(color) {
    case 'r':
      set_rgb(254, 0, 0);
      break;
    case 'g':
      set_rgb(0, 254, 0);
      break;
    case 'b':
      set_rgb(0, 0, 254);
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

void test_sequence() {
  for(int i=0; i < LED_COUNT; i += 1) {
    leds[i] = CRGB(0, 0, 254);
  }
  LEDS.show();
}

void loop() {
  if(Serial.available() > 2) {
    char mode  = Serial.read();
    char color = Serial.read();
    Serial.read(); // EOF char?

    solid_color(color);
    pulse_interval = parse_pulse_interval(mode);
  }

  if(pulse_interval > 0) {
    pulse(pulse_interval);
  } else if (pulse_interval < 0) {
    rainbow();
  }
}

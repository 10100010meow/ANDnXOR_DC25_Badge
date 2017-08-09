#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define LED_PIN         0
#define NUM_LEDS        5
#define BRIGHTNESS      10

const uint8_t PROGMEM gamma8[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

uint8_t bounce_order[] = {0, 4, 3, 2, 1, 1, 2, 3, 4, 0};
#define BOUNCE_COUNT      10
#define ANIM_TIME         30000

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);



//ROYGBIV
uint32_t roygbiv[] = {
  leds.Color(255, 0, 0), leds.Color(255, 165, 0), leds.Color(255, 255, 0),
  leds.Color(0, 255, 0), leds.Color(0, 0, 255), leds.Color(75, 0, 130),
  leds.Color(238, 130, 238)
};

void setup() {
  leds.begin();
  leds.setBrightness(BRIGHTNESS);
  leds.show();

  pinMode(LED_PIN, OUTPUT);

  randomSeed(analogRead(3));
}


void loop() {
  anim_sparkle();
  anim_bounce();
  anim_snake();
  anim_rainbow();
}

void anim_bounce() {
  float hue = ((float)random(100)) / 100.0;
  uint32_t end_time = millis() + ANIM_TIME;
  while (millis() < end_time) {
    for (uint8_t i = 0; i < BOUNCE_COUNT; i++) {
      clearLEDs();
      setColorHSV(bounce_order[i], hue, 1, 1);
      leds.show();
      delay(100);
    }
  }
}

void anim_sparkle() {

  clearLEDs();

  uint32_t end_time = millis() + ANIM_TIME;
  while (millis() < end_time) {
    uint8_t i = random(NUM_LEDS);
    setColor(i, 255, 255, 255);
    leds.show();
    delay(100);
    setColorHSV(i, (float)random(100) / 100.0, 1, 1);
    leds.show();
    delay(100);
  }
}

void anim_snake() {
  float hue = 0;
  int i = 0;
  uint32_t color;

  clearLEDs();

  uint32_t end_time = millis() + ANIM_TIME;
  while (millis() < end_time) {
    setColorHSV(i, hue, 1, 1);
    leds.show();
    delay(50);

    setColorHSV(i, hue, 1, 1);
    leds.show();

    //wrap around
    i = (i + 1) % NUM_LEDS;
    hue += .03;
    if (hue >= 1) hue -= 1;
    delay(50);
  }
}

void anim_rainbow() {
  float hue = 0;

  uint32_t end_time = millis() + ANIM_TIME;
  while (millis() < end_time) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      setColorHSV(i, hue, 1, 1);
    }
    leds.show();

    //Increment row and color and loop around
    hue += .005;
    if (hue >= 1) hue = 0;

    delay(40);
  }
}

void clearLEDs() {
  //  Serial.println("clearLEDs()");
  for (int i = 0; i < NUM_LEDS; i++) {
    setColor(i, 0, 0, 0);
  }
}

/**
   Set a pixel to an HSV value
*/
void setColorHSV(uint8_t index, float H, float S, float V) {
  float h = H * 6;
  uint8_t i = floor(h);
  float a = V * (1 - S);
  float b = V * (1 - S * (h - i));
  float c = V * (1 - (S * (1 - (h - i))));
  float rf, gf, bf;

  switch (i) {
    case 0:
      rf = V * 255;
      gf = c * 255;
      bf = a * 255;
      break;
    case 1:
      rf = b * 255;
      gf = V * 255;
      bf = a * 255;
      break;
    case 2:
      rf = a * 255;
      gf = V * 255;
      bf = c * 255;
      break;
    case 3:
      rf = a * 255;
      gf = b * 255;
      bf = V * 255;
      break;
    case 4:
      rf = c * 255;
      gf = a * 255;
      bf = V * 255;
      break;
    case 5:
      rf = V * 255;
      gf = a * 255;
      bf = b * 255;
      break;
  }

  uint8_t R = rf;
  uint8_t G = gf;
  uint8_t B = bf;

  setColor(index, R, G, B);
}

void setColor(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
  leds.setPixelColor(index,
                     pgm_read_byte(&gamma8[r]),
                     pgm_read_byte(&gamma8[g]),
                     pgm_read_byte(&gamma8[b]));
}

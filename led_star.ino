#include <FastLED.h>
#include "local_config.h"

const int NUM_LEDS = h_num_led;
const int DATA_PIN = h_data_pin;
const int BUTTON_PIN = h_button_input_pin;

CRGB leds[NUM_LEDS];

unsigned short current_mode = 0;
unsigned short current_led = 0;

void setup() {
  Serial.begin(115200);

  FastLED.addLeds<WS2813, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.println("FastLED activated!");

  pinMode(BUTTON_PIN, INPUT);
}

//*****************************************************

void loop() {
  boolean buttonState = digitalRead(BUTTON_PIN);

  Serial.println(buttonState);

  if(buttonState == HIGH) {
    if (current_mode >= 6) {
      current_mode = 0;
    }
    else {
      current_mode = current_mode + 1;
    }
    current_led = 0;
    Serial.println("Changing mode!!");
  }

  switch (current_mode)
  {
  case 0:
    star_light();
    break;

  case 1:
    dim_star_light();
    break;

  case 2:
    light_blue_light();
    break;

  case 3:
    dim_light_blue_light();
    break;

  case 4:
    star_snake();
    break;

  case 5:
    rainbow();
    break;

  case 6:
    blink_star();
    break;
  
  default:
    Serial.println("Error: Current mode is not a mode!");
    break;
  }
  
  FastLED.show();
  delay(400);
}

void star_light() {
  single_color(CRGB(252, 210, 2));
}

void dim_star_light() {
  single_color(CRGB(68, 57, 1));
}

void light_blue_light() {
  single_color(CRGB(4, 219, 247));
}

void dim_light_blue_light() {
  single_color(CRGB(0, 51, 58));
}

void single_color(CRGB color) {
  if(current_led <= NUM_LEDS) {
    leds[current_led] = color;
    current_led = current_led + 1;
  }
}

void christmas_tree() {}

void rainbow() {
  fill_rainbow(leds, NUM_LEDS, 0, 255 / NUM_LEDS);
}

void blink_star() {
  if (current_led == 0)
  {
    fill_solid(leds, NUM_LEDS, CRGB(252, 210, 2));
    current_led = 255;
  }
  else {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    current_led = 0;
  }
}

void star_snake() {
  if(current_led <= NUM_LEDS) {
    leds[current_led] = CRGB(252, 210, 2);
    current_led = current_led + 1;
  }
  else {
    current_led = 0;
    fill_solid(leds, NUM_LEDS, CRGB::Black);
  }
}

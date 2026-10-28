// Smart Backpack Posture / Force Sensor Code
// Circuit Playground Express
// Dual FSR + Dual NeoPixels + DRV2605 Haptic Motor

#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "Adafruit_DRV2605.h"

// -------------------- Hardware Pins --------------------
const int PIN_FSR_LEFT  = A3;
const int PIN_FSR_RIGHT = A2;

const int PIN_LED_LEFT  = A7;
const int PIN_LED_RIGHT = A6;

const int NUM_LEDS = 3;

// -------------------- NeoPixels --------------------
Adafruit_NeoPixel leftPixels(NUM_LEDS, PIN_LED_LEFT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rightPixels(NUM_LEDS, PIN_LED_RIGHT, NEO_GRB + NEO_KHZ800);

// -------------------- Haptic Driver --------------------
Adafruit_DRV2605 hapticMotor;

// -------------------- Constants --------------------
const int IMBALANCE_THRESHOLD = 15;

void setup() {

  Serial.begin(115200);

  // Initialize NeoPixels
  leftPixels.begin();
  rightPixels.begin();

  // Reduce brightness to 80% (20% lower)
  leftPixels.setBrightness(204);    // 204/255 ≈ 80%
  rightPixels.setBrightness(204);

  leftPixels.clear();
  rightPixels.clear();

  leftPixels.show();
  rightPixels.show();

  // Initialize I2C and DRV2605
  Wire.begin();

  if (!hapticMotor.begin()) {
    Serial.println("DRV2605 not detected.");
    while (1);
  }

  hapticMotor.selectLibrary(1);
  hapticMotor.setMode(DRV2605_MODE_INTTRIG);

  Serial.println("Smart Backpack Ready");
}

// ----------------------------------------------------
// Update LED strip based on force
// ----------------------------------------------------
void updateBackpackStrap(Adafruit_NeoPixel &strip, int weightValue) {

  strip.clear();

  if (weightValue > 320) {
    // Heavy load -> Green
    strip.setPixelColor(0, strip.Color(0, 255, 0));
  }
  else if (weightValue >= 300 && weightValue <= 320) {
    // Medium load -> Yellow
    strip.setPixelColor(0, strip.Color(255, 255, 0));
    strip.setPixelColor(1, strip.Color(255, 255, 0));
  }
  else {
    // Light load -> Red
    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.setPixelColor(1, strip.Color(255, 0, 0));
    strip.setPixelColor(2, strip.Color(255, 0, 0));
  }

  strip.show();
}

void loop() {

  // Read force sensors
  int leftWeight = analogRead(PIN_FSR_LEFT);

  // Right sensor calibration
  int rightWeight = analogRead(PIN_FSR_RIGHT) * 0.8;

  // Calculate absolute difference
  int weightDifference = abs(leftWeight - rightWeight);

  // Serial Monitor output
  Serial.print("Left: ");
  Serial.print(leftWeight);
  Serial.print(" | Right: ");
  Serial.print(rightWeight);
  Serial.print(" | Difference: ");
  Serial.println(weightDifference);

  // Update LED strips
  updateBackpackStrap(leftPixels, leftWeight);
  updateBackpackStrap(rightPixels, rightWeight);

  // Continuous haptic feedback whenever imbalance exceeds threshold
  if (weightDifference > IMBALANCE_THRESHOLD) {

    // Strong Buzz effect
    hapticMotor.setWaveform(0, 14);
    hapticMotor.setWaveform(1, 0);
    hapticMotor.go();

    // Replay the effect continuously while imbalance remains
    delay(100);

  } else {

    // Small delay for stable readings
    delay(20);

  }
}



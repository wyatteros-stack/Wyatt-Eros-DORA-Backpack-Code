**Contributors:**

    Justin Cho (main writer)
    Wyatt Eros (FRS debugging and general debugging)
    Neethika Vjay

**D.O.R.A. — Smart Backpack**

This is the code for D.O.R.A. (Data-Optimized Rebalancing Apparatus), a backpack system that uses force sensors to detect uneven loading and gives the wearer visual and haptic feedback.

**How It Works**

Two FSRs measure the force on the left and right backpack straps. The Circuit Playground Express compares the readings, shows the force on each strap using NeoPixels, vibrates when the difference between the two sides gets too large, and 
prints the sensor readings to the Serial Monitor for testing and calibration.

**Hardware**

Adafruit Circuit Playground Express

2× Force Sensitive Resistors

2× 3-pixel NeoPixel strips

Adafruit DRV2605 haptic driver

Haptic vibration motor

**Pin Configuration**

Left FSR:  A3

Right FSR:  A2

Left NeoPixels:  A7

Right NeoPixels:  A6

DRV2605:  I2C

**FSR Scaling**

The two FSRs did not give the same readings under the same load, so I calibrated the right sensor by scaling its reading by 0.75. The left sensor is used as-is.

    int leftWeight = analogRead(PIN_FSR_LEFT);
    int rightWeight = analogRead(PIN_FSR_RIGHT) * 0.75;

I then compare the two scaled readings:

    int weightDifference = abs(leftWeight - rightWeight);

If the difference is greater than 25, the haptic motor turns on.

**LED Feedback**

The number and color of LEDs changes based on the force measured by each strap:

Below 310: 3 red LEDs

310–330: 2 yellow LEDs

Above 330: 1 green LED

These values were determined through testing with the backpack.

**Libraries**

Adafruit_NeoPixel

Wire

Adafruit_DRV2605

The code is written in Arduino C++ for the Adafruit Circuit Playground Express.

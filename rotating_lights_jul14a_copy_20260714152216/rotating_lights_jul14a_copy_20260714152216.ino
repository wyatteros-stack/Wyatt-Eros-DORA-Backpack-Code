#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>

int r=255;
int b=255;
int g=255;
int rotations=0;

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  CircuitPlayground.clearPixels();
  
  while (rotations < 3){
    
    for(int i=0; i<=9; ++i){
      CircuitPlayground.setPixelColor(i, r, g, b);  
      delay(100);
      CircuitPlayground.clearPixels();
    }
    for(int i=9; i>=0; --i){
      CircuitPlayground.setPixelColor(i, r, g, b);  
      delay(100);
      CircuitPlayground.clearPixels();
    }
   rotations += 1;
  }

    for(int i=0; i<=9; ++i){
      CircuitPlayground.setPixelColor(i, 100, 0, 100);
    }
    delay(1000);
    CircuitPlayground.clearPixels();
}

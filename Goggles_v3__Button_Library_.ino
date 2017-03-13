#include <FastLED.h>
#include <Button.h>
#define NUM_LEDS 32
#define DATA_PIN 11
#define COLOR_ORDER GRB
#define divisor 3
#define brightness 20
    
struct CRGB leds[NUM_LEDS];

int brainwave = 0;
int brainwaves[] = {1000, 800, 166, 125, 100, 77, 56, 40, 25, 14, 4};

Button freqButton = Button(1,PULLUP);
int freqMode = 0;

Button colorButton = Button(0,PULLUP);
int colorMode = 0;


CRGBPalette16 myPalette;



void setup() {

  // put your setup code here, to run once:
  FastLED.addLeds<WS2812, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);


    myPalette = CRGBPalette16( 
    CRGB::Red,    CRGB::Red,  CRGB::Black, 
    CRGB::Red, CRGB::Green, CRGB::Blue, 
    CRGB::MediumVioletRed,  CRGB::Magenta, CRGB::Lime,  
    CRGB::LightSkyBlue,  CRGB::LightSalmon,  CRGB::LightCoral,
    CRGB::HotPink, CRGB::GreenYellow, CRGB::FireBrick,  CRGB::DarkOrange );
}

void loop() {

   FastLED.setBrightness(brightness);

if (freqButton.uniquePress())
  {
  freqMode++;
    if (freqMode > 10)
    {
      freqMode = 0;
    }
    brainwave = brainwaves[freqMode];
  }


if (colorButton.uniquePress())
  {
  colorMode = colorMode+3;

    if (colorMode > 10)
    {
      colorMode = 0;
    }
  }



        // Use this instead if "Red" is too bright:    fill_solid(leds, NUM_LEDS, CHSV(0,255,100));
     fill_solid(leds, NUM_LEDS, myPalette[colorMode]);
     FastLED.show();
     delay(brainwave);

     fill_solid(leds, NUM_LEDS, myPalette[colorMode+1]); 
     FastLED.show();
     delay(brainwave);   

     fill_solid(leds, NUM_LEDS, myPalette[colorMode+2]); 
     FastLED.show();
     delay(brainwave);
     /*
  for (int colorStep=0; colorStep<256; colorStep = colorStep+2)
    {
      int h = colorStep;
      int s = 255;
      int v = 150;

        fill_solid(leds, NUM_LEDS, CHSV(h,s,v));
    FastLED.show();
    }*/
}


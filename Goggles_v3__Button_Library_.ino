#include <FastLED.h>
#include <Button.h>
#define NUM_LEDS 32
#define DATA_PIN 11
#define COLOR_ORDER GRB
#define divisor 3
#define brightness 10
    
struct CRGB leds[NUM_LEDS];

int brainwave = 0;
int brainwaves[] = {1000, 800, 166, 125, 100, 77, 56, 40, 25, 14, 4};

Button freqButton = Button(1,PULLUP);
int freqMode = 0;

Button colorButton = Button(0,PULLUP);
int colorMode = 0;

// Define an offset for the left and right eye LED strips
int rightEye = 0;
int leftEye = 0+(NUM_LEDS/2);

CRGBPalette16 myPalette;


void setup() {

    FastLED.addLeds<WS2812, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);


    myPalette = CRGBPalette16( 
    CRGB::Red,    CRGB::Red,  CRGB::Black, 
    CRGB::Red, CRGB::Green, CRGB::Blue, 
    CRGB::MediumVioletRed,  CRGB::Orange, CRGB::Lime,  
    CRGB::LightSkyBlue,  CRGB::LightSalmon,  CRGB::LightCoral,
    CRGB::HotPink, CRGB::GreenYellow, CRGB::FireBrick,  CRGB::DarkOrange );
    
}

void loop() 
{
  checkButtons();


    for(int i=0; i<3; i++)
      {
        blinkColors(i);
      }

 /*   for(int i=0; i<3; i++)
      {
        chaseColors(i);
      }


    for(int i=0; i<256; i++)
      {
        fadeColors(i);
      }
*/
}



void blinkColors(int y)
{
       fill_solid(leds, NUM_LEDS, myPalette[colorMode+y]);
       FastLED.show();
       delay(brainwave);
}



void checkButtons()
{
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

}



void fadeColors(int i)
{
        int h = i;
        int s = 255;
        int v = 150;
  
        fill_solid(leds, NUM_LEDS, CHSV(h,s,v));
        FastLED.show();
}


void chaseColors(int i)
{
      for(int dot=0; dot < NUM_LEDS/2; dot++)
     {
  
        leds[leftEye+dot] = myPalette[colorMode+i];
          
        if(i<2)
            {
              leds[rightEye+dot] = myPalette[colorMode+i+1];
            }
        else
            {
              leds[rightEye+dot] = myPalette[colorMode+i-2];
            }
        
        FastLED.show();
        leds[leftEye+dot] = CRGB::Black;
        leds[rightEye+dot] = CRGB::Black;
       
        delay(brainwave/NUM_LEDS);
     }
}





/* 
   *  This is an alternate of the blinkColor code to run in the main loop
   *  
       fill_solid(leds, NUM_LEDS, myPalette[colorMode]);
       FastLED.show();
       delay(brainwave);
  
       fill_solid(leds, NUM_LEDS, myPalette[colorMode+1]); 
       FastLED.show();
       delay(brainwave);   
  
       fill_solid(leds, NUM_LEDS, myPalette[colorMode+2]); 
       FastLED.show();
       delay(brainwave);
    */   




  /*
  // This is an alternate of the Chase RGB Code to run in the main loop
        
  for(int colorCycle=0; colorCycle<3; colorCycle++)
  {

    for(int dot=0; dot < NUM_LEDS/2; dot++)
     {
  
        leds[leftEye+dot] = myPalette[colorMode+colorCycle];
  
        //Below is inelegant.  left=0 then right=1, left=1 then right=2, but if left=2 then right=0
        //Can I do that in less code?
        
        
        if(colorCycle<2)
            {
              leds[rightEye+dot] = myPalette[colorMode+colorCycle+1];
            }
        else
            {
              leds[rightEye+dot] = myPalette[colorMode+colorCycle-2];
            }
        
        FastLED.show();
        leds[leftEye+dot] = CRGB::Black;
        leds[rightEye+dot] = CRGB::Black;
       
        delay(brainwave/NUM_LEDS);
      }
   
    }
  */


   /*
   // Alternative Fade RGB Code
    for (int colorStep=0; colorStep<256; colorStep = colorStep+2)
      {
        int h = colorStep;
        int s = 255;
        int v = 150;
  
          fill_solid(leds, NUM_LEDS, CHSV(h,s,v));
      FastLED.show();
      }*/
  

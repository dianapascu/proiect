#include <Wire.h>
#include "RTClib.h"
#include <Time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>


 #define PIN 6
 
// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
 
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(12, 12, PIN,
  NEO_MATRIX_TOP   + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS  + NEO_MATRIX_ZIGZAG,
  NEO_GRB          + NEO_KHZ800);
  
RTC_DS1307 rtc; // obiectul clasei RTC_DS1307

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(255, 255, 0),matrix.Color(0, 0, 255), matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)};


int ESTE[]          = {0, 1, 2, 3, 144, 144, 144, 144, 144, 144, 144, 144};
int ORA[]           = {5, 6, 7, 144, 144, 144, 144, 144, 144, 144, 144, 144};
int UNU[]           = {9, 10, 11, 144, 144, 144, 144, 144, 144, 144, 144, 144};



void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
  
    delay(200);
  
    Wire.begin();

        if (! rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        while (1);
    }

//    if (rtc.lostPower()) //Sets the initial date for the RTC
//    {
//        Serial.println("RTC lost power, lets set the time!");
//        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//    }

  rtc.adjust(DateTime(2017, 6, 5, 1, 10, 10));

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(255);
  matrix.setTextColor(colors[0]);
  rainbow();


}

void loop() {
  // put your main code here, to run repeatedly:

    DateTime currentTime = rtc.now();
    Serial.print("Este ora : ");
    Serial.print(currentTime.hour());
    

    if( currentTime.hour() == 1)
    {
      turnOnPixels(ESTE,colors[2]);
      turnOnPixels(ORA,colors[1]);
      turnOnPixels(UNU,colors[0]);
    }
      matrix.show();
      delay(500);
       matrix.fillScreen(0);
  
}



void turnOnPixels(int pixels[],int color)
{
    int x = 0;
    int y = 0;
    for(int index = 0; index < 12; index++)
    {
      if(pixels[index] != 144)
      {
        x = pixels[index]%12;
        y = pixels[index]/12;
        if ( y%2 == 1 ) {
          x = 12 -x -1;
        }
        matrix.drawPixel(x,y, color);
      }
    }
}

void rainbow(){

  for ( int i=0; i<143;i++) {
    turnOnPixels(i,random(0,255));
    matrix.show();
    delay(10);
    matrix.fillScreen(0);
  }
}




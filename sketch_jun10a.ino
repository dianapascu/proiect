#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "RTClib.h"
#include <Time.h>

#define PIN 6
#define DST 2 // numarul pinului
#define DEBUG 1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800); // numarul de leduri, numarul pinului
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
RTC_DS1307 rtc; // obiectul clasei RTC_DS1307

uint32_t color;
boolean startup = true;


///*
// * Brightness
// */
//#define dayBrightness 200;
//#define nightBrightness 55;
// 
///*------------------------------------------------------------------------*/
//int brightnessOfClock = dayBrightness;
//
///*------------------------------------------------------------------------*/


int counter = 0;

/*
* Potentiometer pins
*/
int red = A0;
int green = A1;
int blue = A2;
int brightness = A3;  

/*
    0                    11
    E S T E  O R A  U N U
    12                   23
    U N S P R E Z E C E 
    24                   35
    D O U A S P R E Z E C E
    36                   47
    T R E I S A P T E O P T
    48                   59
    P A T R U S A S E  S I
    60                   71
    C I N C I N O U A  S I
    72                   83
    F A R A S I U N Z E C E
    84                   95
    S F E R T  F I X
    96                   107
    S I  J U M A T A T E 
    108                  119
    D O U A Z E C I 
    120                  131
    T R E I Z E C I  S I
    132                  143
    C I N C I  M I N U T E            
*/

int ESTE[]          = {0, 1, 2, 3, 144, 144, 144, 144, 144, 144, 144, 144};
int ORA[]           = {5, 6, 7, 144, 144, 144, 144, 144, 144, 144, 144, 144};
int UNU[]           = {9, 10, 11, 144, 144, 144, 144, 144, 144, 144, 144, 144};
int UNSPREZECE[]    = {23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 144, 144};
int ORA_ZECE[]      = {17, 16, 15, 14, 144, 144, 144, 144, 144, 144, 144, 144};
int DOUASPREZECE[]  = {24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
int DOUA[]          = {24, 25, 26, 27, 144, 144, 144, 144, 144, 144, 144, 144};
int TREI[]          = {47, 46, 45, 44, 144, 144, 144, 144, 144, 144, 144, 144};
int SAPTE[]         = {43, 42, 41, 40, 39, 144, 144, 144, 144, 144, 144, 144};
int OPT[]           = {38, 37, 36, 144, 144, 144, 144, 144, 144, 144, 144, 144};
int PATRU[]         = {48, 49, 50, 51, 52, 144, 144, 144, 144, 144, 144, 144};
int SASE[]          = {53, 54, 55, 56, 144, 144, 144, 144, 144, 144, 144, 144};
int ORA_CINCI[]     = {71, 70, 69, 68, 67, 144, 144, 144, 144, 144, 144, 144}; 
int NOUA[]          = {66, 65, 64, 63, 144, 144, 144, 144, 144, 144, 144, 144};
int SI_1[]          = {61, 60, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144};
int FARA[]          = {72, 73, 74, 75, 144, 144, 144, 144, 144, 144, 144, 144};
int SI_2[]          = {76, 77, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144};
int UN[]            = {78, 79, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144};
int ZECE_MIN[]      = {80, 81, 82, 83, 144, 144, 144, 144, 144, 144, 144, 144};
int FIX[]           = {95, 94, 93, 144, 144, 144, 144, 144, 144, 144, 144, 144};
int SFERT[]         = {89, 88, 87, 86, 85, 144, 144, 144, 144, 144, 144, 144};
int SI_3[]          = {96, 97, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144};
int JUMATATE[]      = {99, 100, 101, 102, 103, 104, 105, 106, 144, 144, 144, 144};
int DOUAZECI[]      = {119, 118, 117, 116, 115, 114, 113, 112, 144, 144, 144, 144};
int TREIZECI[]      = {120, 121, 122, 123, 124, 125, 126, 127, 144, 144, 144, 144};
int SI_4[]          = {129, 130, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144};
int CINCI_MIN[]     = {143, 142, 141, 140, 139, 144, 144, 144, 144, 144, 144, 144};
int MINUTE[]        = {137, 136, 135, 134, 133, 132, 144, 144, 144, 144, 144, 144};

/**
 * Setup for the program
 */
 /*------------------------------------------------------------------------*/

void setup()
{
    Serial.begin(9600);
    
    delay(200);
 
    Wire.begin();
    pinMode(DST, INPUT); // numarul pinului al carui mod vreau sa il setez
                         // INPUT este modul -> o sa se primeasca un semnal pe pinul mentionat, adica DST
    delay(3000);
    

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

  rtc.adjust(DateTime(2017, 6, 5, 9, 59, 10));
   
    strip.begin();
//        getColor();
    //startupTest();
//    getBrightness();
//    resetPixels();
//    turnOnPixels(FIX);
//    strip.show();
//    delay(1000);
//    while(1){
//      Serial.print("ceva");}
    
}

/*------------------------------------------------------------------------*/

/**
 * Main loop of the program
 */
void loop()
{
    DateTime currentTime = rtc.now();
    if (digitalRead(DST) == 1) // citesc digital read de pe pinul 2 = DST (1 sau 0) // 1= buton apasat; //0= butonul nu este apasat // este pentru a da ceasul cu o ora inainte
    {
      currentTime = currentTime + TimeSpan(0,1,0,0); // nr de zile, nr de ore, nr de min, nr de sec
    }
    
    getColor();
    startupTest();
    getBrightness();
    resetPixels();

    displayWords(currentTime);
    
    strip.show();
    counter++;

    delay(990);
}

void startupTest()
{
    if (startup)
    {
      for(int index = 0; index < 144; index++)
      {
        strip.setBrightness(255);
        delay(40);
        strip.setPixelColor(index, strip.Color(random(0, 255),random(0, 255),random(0, 255)));
        strip.setPixelColor(index-5, strip.Color(0,0,0));
        strip.show();
      }
      for(int index = 144; index > -5; index--)
      {
        strip.setBrightness(255);
        delay(40);
        strip.setPixelColor(index, strip.Color(random(0, 255),random(0, 255),random(0, 255)));
        strip.setPixelColor(index+5, strip.Color(0,0,0));
        strip.show();
      }
    }
    startup = false;
}


/**
 * Gets the color based on user input through three potentiometer
 */
void getColor()
{
    color = strip.Color(map(analogRead(red), 0, 1023, 0, 255),
                        map(analogRead(green), 0, 1023, 0, 255),
                        map(analogRead(blue), 0, 1023, 0, 255));
}

/**
 * Gets the brightness based on user input through a potentiometer
 */
void getBrightness()
{
    strip.setBrightness(map(analogRead(brightness), 0, 1023, 0, 255));
}


/**
 * Sets the correct pixels to light up based on the time
 */
void displayWords(DateTime currentTime)
{
    
    displayHours(currentTime.hour(), currentTime.minute());
    displayMinutes(currentTime.minute());
    
    
    delay(10);
    
    Serial.print(" -> ");
    Serial.print(currentTime.hour(), DEC);
    Serial.print(" : ");
    Serial.println(currentTime.minute(), DEC);
}

/**
 * Determines what hours to display
 */
void displayHours(int hour, int minute)
{
    turnOnPixels(ESTE);
    Serial.println("");
    Serial.print("ESTE");

   if (hour % 12 == 1)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA);
            turnOnPixels(DOUA);
            Serial.print(" ORA DOUA");
        }
        
        else
        {
            turnOnPixels(ORA);
            turnOnPixels(UNU);
            Serial.print(" ORA UNU");
        }
    }
    
    if (hour % 12 == 2)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA);
            turnOnPixels(TREI);
            Serial.print(" ORA TREI");
        }
        
        else
        {
            turnOnPixels(ORA);
            turnOnPixels(DOUA);
            Serial.print(" ORA DOUA");
        }
    }
    
    if (hour % 12 == 3)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA);
            turnOnPixels(PATRU);
            Serial.print(" ORA PATRU");
        }
        
        else
        {
            turnOnPixels(ORA);
            turnOnPixels(TREI);
            Serial.print(" ORA TREI");
        }
    }
    
    if (hour % 12 == 4)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA);
            turnOnPixels(ORA_CINCI);
            Serial.print(" ORA CINCI");
        }
        
        else
        {
            turnOnPixels(ORA);
            turnOnPixels(PATRU);
            Serial.print(" ORA PATRU");
        }
    }
    if (hour % 12 == 5)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA);
            turnOnPixels(SASE);
            Serial.print(" ORA SASE");
        }
        
        else
        {
            turnOnPixels(ORA);
            turnOnPixels(ORA_CINCI);
            Serial.print(" ORA CINCI");
        }
    }
    
    if (hour % 12 == 6)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA);
            turnOnPixels(SAPTE);
            Serial.print(" ORA SAPTE");
        }
        
        else
        {
            turnOnPixels(ORA);
            turnOnPixels(SASE);
            Serial.print(" ORA SASE");
        }
    }
    
    if (hour % 12 == 7)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA);
            turnOnPixels(OPT);
            Serial.print(" ORA OPT");
        }
        
        else
        {
            turnOnPixels(ORA);
            turnOnPixels(SAPTE);
            Serial.print(" ORA SAPTE");
        }
    }
    if (hour % 12 == 8)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA);
            turnOnPixels(NOUA);
            Serial.print(" ORA NOUA");
        }
        
        else
        {
            turnOnPixels(ORA);
            turnOnPixels(OPT);
            Serial.print(" ORA OPT");
        }
    }
    
    if (hour % 12 == 9)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA);
            turnOnPixels(ORA_ZECE);
            Serial.print(" ORA ZECE");
        }
        
        else
        {
            turnOnPixels(ORA);
            turnOnPixels(NOUA);
            Serial.print(" ORA NOUA");
        }
    }
    
    if (hour % 12 == 10)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA);
            turnOnPixels(UNSPREZECE);
            Serial.print(" ORA UNSPREZECE");
        }
        
        else
        {
            turnOnPixels(ORA);
            turnOnPixels(ORA_ZECE);
            Serial.print(" ORA ZECE");
        }
    }
    
    if (hour % 12 == 11)
    {
        if (minute <= 32)
        {
            turnOnPixels(ORA);
            turnOnPixels(UNSPREZECE);
            Serial.print(" ORA UNSPREZECE");
        }
        
        else
        {
             turnOnPixels(ORA);
             turnOnPixels(DOUASPREZECE);
             Serial.print(" ORA DOUASPREZECE");
         }
     }
     
    if (hour % 12 == 0)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA);
            turnOnPixels(UNU);
            Serial.print(" ORA UNU");
        }
        
        else
        {      
             turnOnPixels(ORA);
             turnOnPixels(DOUASPREZECE);
             Serial.print(" ORA DOUASPREZECE");
        }
    }
}

/**
 * Determines what minutes to display
 */
void displayMinutes(int minute)
{ 
  //int hour;
    if (minute > 2 && minute < 8)
    {    
        turnOnPixels(SI_4);
        turnOnPixels(CINCI_MIN);
        turnOnPixels(MINUTE);
        Serial.print(" SI CINCI MINUTE");
    }
    
    if (minute > 7 && minute < 13)
    {
        turnOnPixels(SI_2);
        turnOnPixels(ZECE_MIN);
         turnOnPixels(MINUTE);
        Serial.print(" SI ZECE MINUTE");
    }
    
    if (minute > 12 && minute < 18)
    {
        turnOnPixels(SI_1);
        turnOnPixels(UN);
        turnOnPixels(SFERT);
        Serial.print(" SI UN SFERT");
    }
    
    if (minute > 17 && minute < 23)
    {
        turnOnPixels(SI_3);
        turnOnPixels(DOUAZECI);
        Serial.print(" SI DOUAZECI");
    }
    
    if (minute > 22 && minute < 28)
    {
        turnOnPixels(SI_3);
        turnOnPixels(DOUAZECI);
        turnOnPixels(SI_4);
        turnOnPixels(CINCI_MIN);
        Serial.print(" SI DOUAZECI SI CINCI");
    }
    
    if (minute > 27 && minute < 33)
    {
        turnOnPixels(SI_3);
        turnOnPixels(JUMATATE);
        Serial.print(" SI JUMATATE");
    }
    
    if (minute > 32 && minute < 38)
    {
        turnOnPixels(SI_3);
        turnOnPixels(TREIZECI);
        turnOnPixels(SI_4);
        turnOnPixels(CINCI_MIN);
        Serial.print(" SI TREIZECI SI CINCI");
    }
    
    if (minute > 37 && minute < 43)
    {
        turnOnPixels(FARA);
        turnOnPixels(DOUAZECI);
        Serial.print(" FARA DOUAZECI");
    }
    
    if (minute > 42 && minute < 48)
    {
        turnOnPixels(FARA);
        turnOnPixels(UN);
        turnOnPixels(SFERT);
        Serial.print(" FARA UN SFERT");
    }
    
    if (minute > 47 && minute < 53)
    {
        turnOnPixels(FARA);
        turnOnPixels(ZECE_MIN);
        turnOnPixels(MINUTE);
        Serial.print(" FARA ZECE");
    }
    
    if (minute > 52 && minute < 58)
    {
        turnOnPixels(FARA);
        turnOnPixels(CINCI_MIN);
        turnOnPixels(MINUTE);
        Serial.print(" FARA CINCI MINUTE");
    }
//
//    if(minute >57 && minute <3)
//    {
//              turnOnPixels(FARA);
//        turnOnPixels(CINCI_MIN);
//        turnOnPixels(MINUTE);
//        
//      }

//    if (hour == 10){
//      if(minute == 58){
//        turnOnPixels(FIX);
//        turnOnPixels(ORA_ZECE);
//      }
//      else {
//        turnOnPixels(FARA);
//        }
//    }
   
//    else if (minute == 59)
//    {
//        turnOnPixels(FIX);
//        Serial.print(" FIX");
//    }
//    if (minute > 0 && minute < 3)
//    {
//        turnOnPixels(FIX);
//        Serial.print(" FIX");
//    }

//    if (minute > 57 && minute < 59)
//    {
//        turnOnPixels(fix_bogdan);
//        turnOnPixels(MINUTE);
//        Serial.print(" FIX true");
//    }
   
}

/**
 * Turn on each pixel individually
 */
void resetPixels()
{
    for(int index = 0; index < 144; index++)
    {
        strip.setPixelColor(index, strip.Color(0,0,0));
    }
}

/**
 * Turn on each pixel individually
 */
void turnOnPixels(int pixels[])
{
    for(int index = 0; index < 12; index++)
    {
      if(pixels[index] != 144)
      {
        strip.setPixelColor(pixels[index], color);
      }
    }
}

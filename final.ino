#include <Wire.h>
#include "RTClib.h"
#include <Time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#define PIN 2
#define settime 4 // numarul pinului
#define setPlus 5
#define setMinus 6 
#define DEBUG 1
#define ONE_WIRE_BUS 3 // Data wire is plugged into pin 3 on the Arduino
#define trigPin 8
#define echoPin 7

 
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
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


boolean startup = true;
uint32_t color;
int x    = matrix.width();
int pass = 0;

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(255, 255, 0),matrix.Color(0, 0, 255), matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)};



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
    84                   9






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



void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
  
    delay(200);
  
    Wire.begin();
        
    pinMode(settime, INPUT); // numarul pinului al carui mod vreau sa il setez
                                                // INPUT este modul -> o sa se primeasca un semnal pe pinul mentionat, adica DST
    pinMode(setPlus, INPUT);
    pinMode(setMinus, INPUT);
    

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

  rtc.adjust(DateTime(2017, 6, 5, 1, 2, 10));

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(255);
  matrix.setTextColor(colors[1]);
  
  //startupTest();
 // rainbow();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


}

void loop() {
  color=colors[1];
  // put your main code here, to run repeatedly:

    DateTime currentTime = rtc.now();
    if (digitalRead(settime) == 0) // citesc digital read de pe pinul 2 = DST (1 sau 0) // 1= buton apasat; //0= butonul nu este apasat // este pentru a da ceasul cu o ora inainte
    {
      if(digitalRead(setPlus) == 1) {
      currentTime = currentTime + TimeSpan(0,0,1,0); // nr de zile, nr de ore, nr de min, nr de sec
     }
      if(digitalRead(setMinus) == 1) {
        currentTime = currentTime + TimeSpan(0,0,-1,0);
      }
    }

    if (digitalRead(settime) == 1) // citesc digital read de pe pinul 2 = DST (1 sau 0) // 1= buton apasat; //0= butonul nu este apasat // este pentru a da ceasul cu o ora inainte
    {
      if(digitalRead(setPlus) == 1) {
      currentTime = currentTime + TimeSpan(0,1,0,0); // nr de zile, nr de ore, nr de min, nr de sec
     }
      if(digitalRead(setMinus) == 1) {
        currentTime = currentTime + TimeSpan(0,-1,0,0);
      }
    }
//    Serial.print("Este ora : ");
//    Serial.print(currentTime.hour());

//    if( currentTime.hour() == 1)
//    {
//      turnOnPixels(ESTE,colors[2]);
//      turnOnPixels(ORA,colors[1]);
//      turnOnPixels(UNU,colors[0]);
//    }

    getColor();
    //startupTest();
    if (sensorContact() < 30 ) {
      printTemperature();
    }
    else {
     displayWords(currentTime);
    }
 
    
    matrix.show();
    delay(500);
    matrix.fillScreen(0);
//    if(1) {
//      turnOnTemperature(5);
//      //turnOntext("la multi ani");
//    }
  
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
    Serial.print(currentTime.minute(), DEC);
    Serial.print(" : ");
    Serial.println(currentTime.second(), DEC);
    
}

/**
 * Determines what hours to display
 */
void displayHours(int hour, int minute)
{
    turnOnPixels(ESTE, color);
    Serial.println("");
    Serial.print("ESTE");

   if (hour % 12 == 1)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA, color);
            turnOnPixels(DOUA, color);
            Serial.print(" ORA DOUA");
        }
        
        else
        {
            turnOnPixels(ORA, color);
            turnOnPixels(UNU, color);
            Serial.print(" ORA UNU");
        }
    }
        
    if (hour % 12 == 2)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA, color);
            turnOnPixels(TREI, color);
            Serial.print(" ORA TREI");
        }
        
        else
        {
            turnOnPixels(ORA, color);
            turnOnPixels(DOUA, color);
            Serial.print(" ORA DOUA");
        }
    }
    
    if (hour % 12 == 3)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA, color);
            turnOnPixels(PATRU, color);
            Serial.print(" ORA PATRU");
        }
        
        else
        {
            turnOnPixels(ORA, color);
            turnOnPixels(TREI, color);
            Serial.print(" ORA TREI");
        }
    }
    
    if (hour % 12 == 4)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA, color);
            turnOnPixels(ORA_CINCI, color);
            Serial.print(" ORA CINCI");
        }
        
        else
        {
            turnOnPixels(ORA, color);
            turnOnPixels(PATRU, color);
            Serial.print(" ORA PATRU");
        }
    }
    if (hour % 12 == 5)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA, color);
            turnOnPixels(SASE, color);
            Serial.print(" ORA SASE");
        }
        
        else
        {
            turnOnPixels(ORA, color);
            turnOnPixels(ORA_CINCI, color);
            Serial.print(" ORA CINCI");
        }
    }
    
    if (hour % 12 == 6)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA, color);
            turnOnPixels(SAPTE, color);
            Serial.print(" ORA SAPTE");
        }
        
        else
        {
            turnOnPixels(ORA, color);
            turnOnPixels(SASE, color);
            Serial.print(" ORA SASE");
        }
    }
    
    if (hour % 12 == 7)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA, color);
            turnOnPixels(OPT, color);
            Serial.print(" ORA OPT");
        }
        
        else
        {
            turnOnPixels(ORA, color);
            turnOnPixels(SAPTE, color);
            Serial.print(" ORA SAPTE");
        }
    }
    if (hour % 12 == 8)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA, color);
            turnOnPixels(NOUA, color);
            Serial.print(" ORA NOUA");
        }
        
        else
        {
            turnOnPixels(ORA, color);
            turnOnPixels(OPT, color);
            Serial.print(" ORA OPT");
        }
    }
    
    if (hour % 12 == 9)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA, color);
            turnOnPixels(ORA_ZECE, color);
            Serial.print(" ORA ZECE");
        }
        
        else
        {
            turnOnPixels(ORA, color);
            turnOnPixels(NOUA, color);
            Serial.print(" ORA NOUA");
        }
    }
    
    if (hour % 12 == 10)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA, color);
            turnOnPixels(UNSPREZECE, color);
            Serial.print(" ORA UNSPREZECE");
        }
        
        else
        {
            turnOnPixels(ORA, color);
            turnOnPixels(ORA_ZECE, color);
            Serial.print(" ORA ZECE");
        }
    }
    
    if (hour % 12 == 11)
    {
        if (minute <= 32)
        {
            turnOnPixels(ORA, color);
            turnOnPixels(UNSPREZECE, color);
            Serial.print(" ORA UNSPREZECE");
        }
        
        else
        {
             turnOnPixels(ORA, color);
             turnOnPixels(DOUASPREZECE, color);
             Serial.print(" ORA DOUASPREZECE");
         }
     }
     
    if (hour % 12 == 0)
    {
        if (minute > 32)
        {
            turnOnPixels(ORA, color);
            turnOnPixels(UNU, color);
            Serial.print(" ORA UNU");
        }
        
        else
        {      
             turnOnPixels(ORA, color);
             turnOnPixels(DOUASPREZECE, color);
             Serial.print(" ORA DOUASPREZECE");
        }
    }
   
}


/**
 * Determines what minutes to display
 */
void displayMinutes(int minute)
{ 

    if (minute > 2 && minute < 8)
    {    
        turnOnPixels(SI_4, color);
        turnOnPixels(CINCI_MIN, color);
        turnOnPixels(MINUTE, color);
        Serial.print(" SI CINCI MINUTE");
    }
    
    if (minute > 7 && minute < 13)
    {
        turnOnPixels(SI_2, color);
        turnOnPixels(ZECE_MIN, color);
         turnOnPixels(MINUTE, color);
        Serial.print(" SI ZECE MINUTE");
    }
        
    if (minute > 12 && minute < 18)
    {
        turnOnPixels(SI_1, color);
        turnOnPixels(UN, color);
        turnOnPixels(SFERT, color);
        Serial.print(" SI UN SFERT");
    }
    
    if (minute > 17 && minute < 23)
    {
        turnOnPixels(SI_3, color);
        turnOnPixels(DOUAZECI, color);
        Serial.print(" SI DOUAZECI");
    }
    
    if (minute > 22 && minute < 28)
    {
        turnOnPixels(SI_3, color);
        turnOnPixels(DOUAZECI, color);
        turnOnPixels(SI_4, color);
        turnOnPixels(CINCI_MIN, color);
        Serial.print(" SI DOUAZECI SI CINCI");
    }
    
    if (minute > 27 && minute < 33)
    {
        turnOnPixels(SI_3, color);
        turnOnPixels(JUMATATE, color);
        Serial.print(" SI JUMATATE");
    }
    
    if (minute > 32 && minute < 38)
    {
        turnOnPixels(SI_3, color);
        turnOnPixels(TREIZECI, color);
        turnOnPixels(SI_4, color);
        turnOnPixels(CINCI_MIN, color);
        Serial.print(" SI TREIZECI SI CINCI");
    }
    
    if (minute > 37 && minute < 43)
    {
        turnOnPixels(FARA, color);
        turnOnPixels(DOUAZECI, color);
        Serial.print(" FARA DOUAZECI");
    }
    
    if (minute > 42 && minute < 48)
    {
        turnOnPixels(FARA, color);
        turnOnPixels(UN, color);
        turnOnPixels(SFERT, color);
        Serial.print(" FARA UN SFERT");
    }
    
    if (minute > 47 && minute < 53)
    {
        turnOnPixels(FARA, color);
        turnOnPixels(ZECE_MIN, color);
        turnOnPixels(MINUTE, color);
        Serial.print(" FARA ZECE");
    }
    
    if (minute > 52 && minute < 58)
    {
        turnOnPixels(FARA, color);
        turnOnPixels(CINCI_MIN, color);
        turnOnPixels(MINUTE, color);
        Serial.print(" FARA CINCI MINUTE");
    }

    
    if(minute >= 58 && minute <=59)
    {
        turnOnPixels(FIX, color);
        Serial.print(" FIX");
        
      }
      
    if(minute >= 0 && minute <=2)
    {
        turnOnPixels(FIX, color);
        Serial.print(" FIX");
        
      }
 
}


void startupTest()
{
    if (startup)
    {
      for(int index = 0; index < 144; index++)
      {
        matrix.setBrightness(255);
        delay(40);
        matrix.setPixelColor(index, matrix.Color(random(0, 255),random(0, 255),random(0, 255)));
        matrix.setPixelColor(index-5, matrix.Color(0,0,0));
        matrix.show();
      }
      
      for(int index = 144; index >= -5; index--)
      {
        matrix.setBrightness(255);
        delay(40);
        matrix.setPixelColor(index, matrix.Color(random(0, 255),random(0, 255),random(0, 255)));
        matrix.setPixelColor(index+5, matrix.Color(0,0,0));
        matrix.show();
      }
    }
    startup = false;
}

/**
 * Gets the color based on user input through three potentiometer
 */
void getColor()
{
    color = matrix.Color(map(analogRead(red), 0, 1023, 0, 255),
                         map(analogRead(green), 0, 1023, 0, 255),
                         map(analogRead(blue), 0, 1023, 0, 255));
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
        matrix.drawPixel(x, y, color);
      }
    }
}


void turnOnTemperature(int x)
{
  String mesaj = String(x);
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(mesaj);
  
  if(--x < -220) {
    x = matrix.width();
    
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  
  matrix.show();
  delay(500);
  
}

//void turnOnText(string x[])
//{
//  String mesaj = String(x);
//  matrix.fillScreen(0);
//  matrix.setCursor(x, 0);
//  matrix.print(mesaj);
//  if(--x < -220) {
//    x = matrix.width();
//    if(++pass >= 3) pass = 0;
//    matrix.setTextColor(colors[pass]);
//  }
//  matrix.show();
//  delay(500);
//  
//}


//void rainbow(){
//
//  for ( int i=0; i<144;i++) {
//    turnOnPixels(i,random(0,255));
//    matrix.show();
//    delay(10);
//    matrix.fillScreen(0);
//  }
//}

int getTemperature(){
  
  sensors.requestTemperatures(); // initi  
  Serial.print("Temperature is: ");
  float temp = sensors.getTempCByIndex(0);
  Serial.println(temp); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  int temperature;
  temperature = (int) temp;
  return temperature;
  
}

void printTemperature() {

    String text = String(getTemperature());
  matrix.setTextSize(1);
  matrix.setCursor(1, 4);
  matrix.fillScreen(0);
  matrix.print(text);

  delay(1000);
}

long sensorContact() {
  
  long duration, distance;
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  return distance;
}



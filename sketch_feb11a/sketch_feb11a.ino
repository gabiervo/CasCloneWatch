#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <SPI.h>

#define WHITE SSD1306_WHITE
#define BLACK SSD1306_BLACK

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const int btn1 = 0;
const int btn2 = 1;
const int btn3 = 2;
const int btn4 = 3;

class clockModule{
  public:
    unsigned long mil;
    unsigned long lastMil = 0;

    uint8_t monthLengths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    //order: hours, minutes, seconds
    uint8_t smallUnits[3];

    //order: days, months, years
    uint8_t largeUnits[3];

  clockModule(){}


  void checkLeapYear(){
    if(largeUnits[2] % 4 == 0){
      monthLengths[2] = 29;
    }
    else{
      monthLengths[2] = 28;
    }
  }
  
  void largeUnitsProcess(){
    largeUnits[0] += 1;
    if(largeUnits[0] > monthLengths[largeUnits[1]]){
      //days are 1 indexed just because
      largeUnits[0] = 1;
      largeUnits[1] += 1;
      //months are zero indexed
      if(largeUnits[1] == 12){
        largeUnits[1] = 0;
        largeUnits[2] += 1; 
        checkLeapYear();      
      }
      
    }
  }
  
  void generalUnitsProcess(){
    mil = millis();
    if(mil - lastMil >= 1000){
      lastMil = millis();
      smallUnits[2] += 1;
      if(smallUnits[2] == 60){
        smallUnits[2] = 0;
        smallUnits[1] += 1;
        if(smallUnits[1] == 60){
          smallUnits[1] = 0;
          smallUnits[0] += 1;

          if(smallUnits[0] == 24){
            smallUnits[0] = 0;
            largeUnitsProcess();
          }
        }
          
      }
        
    }
  }

  String returnCurrTime(){
  return (String){String(this->smallUnits[0]) + "\t" + String(this->smallUnits[1]) + "\t" + String(this->smallUnits[2]) };  
  }
};

clockModule myClock;

void setup() {
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.fillScreen(WHITE);
  oled.display();

  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);

  Serial.begin(9600);

  myClock.smallUnits[1] = 59;
  myClock.smallUnits[0] = 23;
  
  myClock.largeUnits[0] = 31;
  myClock.largeUnits[1] = 0;
}

void loop() {
  myClock.generalUnitsProcess();
  Serial.println( myClock.returnCurrTime() );
  Serial.println( String(myClock.largeUnits[0]) + "   " + String(myClock.largeUnits[1]));
}




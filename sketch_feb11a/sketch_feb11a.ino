#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <SPI.h>

#define WHITE SSD1306_WHITE
#define BLACK SSD1306_BLACK

class Module{
  private:
    using func_ptr = void (*)();
    func_ptr func;
  public:
    String moduleName;
    
  

};

const int btn1 = 0;
const int btn2 = 1;
const int btn3 = 2;
const int btn4 = 3;

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void setup() {
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.fillScreen(WHITE);
  oled.display();

  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);

}

void loop() {
  
}
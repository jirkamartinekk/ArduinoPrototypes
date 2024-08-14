#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
         
  display.setCursor(0,0);             
  display.println(F("Running script!"));
  for(int i = 0; i < 84; i++){
    int procentage = map(i, 0, 82, 0, 100);
    int random_delay = random(50, 300);
    int j = 1;

    display.fillRect(100, 10, 20, 10, SSD1306_BLACK); //fill background with black colour
    display.setCursor(100,10);
    display.print(procentage);
    display.println(F("%"));
    display.setCursor(i,10);
    display.println(F("-"));

    //sdsdsdsdsd

    display.display();

    delay(random_delay);

    i++;
  }


  delay(1000);
}

void loop() {

  //sth...

}
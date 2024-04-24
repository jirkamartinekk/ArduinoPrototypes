#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define RECT_HEIGHT 8 // Výška doplňujícího obdélníku
#define RECT_Y 19     // Y-ová pozice obdélníku

// Inicializace OLED displeje
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int previousWidth = 0; // Předchozí šířka obdélníku na displeji
int threshold = 1;   // Práh pro detekci změny

void setup() {
  // Inicializace displeje
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 inicializace selhala!"));
    for (;;);
  }
  Serial.begin(9600);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  int resistorValue = analogRead(A2);
  // Mapování hodnoty na šířku obdélníku
  int currentWidth = map(resistorValue, 0, 1023, 0, SCREEN_WIDTH);
  int percentageToShow = map(resistorValue, 0, 1023, 0, 100);

  Serial.println(resistorValue);
  Serial.println(currentWidth);

  // Kontrola, zda došlo ke změně nad určeným prahem
  if (abs(currentWidth - previousWidth) > threshold) {
    // Aktualizace šířky obdélníku na displeji
    display.clearDisplay();
    if(percentageToShow < 10){
      display.setCursor(60, 5);
      display.println(percentageToShow);
      display.setCursor(69, 5);
      display.println("%");
    }else if(percentageToShow < 100){
      display.setCursor(60, 5);
      display.println(percentageToShow);
      display.setCursor(74, 5);
      display.println("%");      
    }else{
      display.setCursor(55, 5);
      display.println(percentageToShow);
      display.setCursor(75, 5);
      display.println("%");
    }

    display.fillRect(0, RECT_Y, currentWidth, RECT_HEIGHT, WHITE);
    display.display();

    // Uložení aktuální šířky do předchozí šířky
    previousWidth = currentWidth;
  }

  // Krátké zpoždění pro snížení zátěže procesoru
  delay(85);
}

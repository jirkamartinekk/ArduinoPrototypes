#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1
#define BME280_I2C_ADDRESS 0x76

#define SENSOR_CO_PIN A0

Adafruit_BME280 bme;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define SEALEVELPRESSURE_HPA (1013.25)

void setup() {
  bool status_bme, status_mq5, status_display, status_GP2Y1010AU0F;

  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  pinMode(SENSOR_CO_PIN, INPUT);
  //status_bme = bme.begin(BME280_I2C_ADDRESS);

  display.clearDisplay();
  display.setTextColor(WHITE);

    //booting_diplay();

  delay(5000);

}

void loop() {




}

void booting_diplay(){
  int i = 1;

  for(i; i<=5; i++){
    display.clearDisplay();
    display.setCursor(34, 28);
    display.print("Booting");
    display.display();
    delay(1000);
    display.clearDisplay();
    display.setCursor(34, 28);
    display.print("Booting.");
    display.display();
    delay(1000);
    display.clearDisplay();
    display.setCursor(34, 28);
    display.print("Booting..");
    display.display();
    delay(1000);
    display.clearDisplay();
    display.setCursor(34, 28);
    display.print("Booting...");
    display.display();
    delay(1000);
  }

  display.clearDisplay();
}

void get_data_sensor_CO(){
  float sensor_CO_value;

  sensor_CO_value = analogRead(SENSOR_CO_PIN);

  return sensor_CO_value;
}

void get_data_sensor_bme280(){
  float temperature, humidity, atmospheric_pressure;

  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  atmospheric_pressure = bme.readPressure();

  return temperature, humidity, atmospheric_pressure;
}

void get_data_sensor_GP2Y1010AU0F(){
  float ;

}
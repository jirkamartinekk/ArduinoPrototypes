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

#define SENSOR_GAS_PIN 34

Adafruit_BME280 bme;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int sensor_gas_value;
bool status_bme;

// Definice struktury bme280Data na začátku kódu
struct bme280Data {
  float temperature;
  float humidity;
  float atmospheric_pressure;
};

struct sensorStatus{
  bool status_bme;
  bool status_gas;
  bool status_display;
  bool wifi;
};

bme280Data data;
sensorStatus component_status;

void setup() {

  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generování napětí pro displej z 3.3V
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  pinMode(SENSOR_GAS_PIN, INPUT);
  status_bme = bme.begin(BME280_I2C_ADDRESS);

  display.clearDisplay();
  display.setTextColor(WHITE);

  booting_diplay();
}

void loop() {
  data = get_data_sensor_bme280(); // Uložení dat do globální proměnné
  sensor_gas_value = get_data_sensor_gas();
  showTerminal();
  showDisplay();

  //delay(300000);
  delay(10000);
}

void booting_diplay(){
  int i = 1;
  display.setTextSize(2);

  for(i; i<=3; i++){
    display.clearDisplay();
    display.setCursor(5, 22);
    display.print("Booting");
    display.display();
    delay(1000);
    display.clearDisplay();
    display.setCursor(5, 22);
    display.print("Booting.");
    display.display();
    delay(1000);
    display.clearDisplay();
    display.setCursor(5, 22);
    display.print("Booting..");
    display.display();
    delay(1000);
    display.clearDisplay();
    display.setCursor(5, 22);
    display.print("Booting...");
    display.display();
    delay(1000);
  }

  display.clearDisplay();
  display.setCursor(39, 22);
  display.print("Done!");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
}

void showDisplay(){
  display.setTextSize(1);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Teplota: ");
  display.print(data.temperature);
  display.print((char)247);
  display.println("C");
  display.setCursor(0, 10);
  display.print("Vlhkost: ");
  display.print(data.humidity);
  display.println("%");
  display.setCursor(0, 20);
  display.print("Tlak:    ");
  display.print(data.atmospheric_pressure / 100.0F);
  display.println("hPa");
  display.setCursor(0, 30);
  display.print("Castice: ");
  display.print(sensor_gas_value);
  display.println("ppm");

  display.setCursor(0, 45);
  display.println("version 1.0");
  if(component_status.wifi){
    display.println("WiFi connected");
  }else{
    display.println("WiFi disconnected");
  }


  display.display();
}

void showTerminal(){
  Serial.print("Teplota: ");
  Serial.print(data.temperature);
  Serial.println("°C");

  Serial.print("Vlhkost: ");
  Serial.print(data.humidity);
  Serial.println("%");

  Serial.print("Tlak: ");
  Serial.print(data.atmospheric_pressure / 100.0F);
  Serial.println("hPa");

  Serial.print("Koncentrace částic: ");
  Serial.print(sensor_gas_value);
  Serial.println("ppm");
}

int get_data_sensor_gas(){
  int sensor_gas_value;

  sensor_gas_value = analogRead(SENSOR_GAS_PIN);

  return sensor_gas_value;
}

bme280Data get_data_sensor_bme280() {
  bme280Data data;

  data.temperature = bme.readTemperature();
  data.humidity = bme.readHumidity();
  data.atmospheric_pressure = bme.readPressure();

  return data;
}

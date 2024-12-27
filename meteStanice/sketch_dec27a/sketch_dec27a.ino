// Optický senzor kvality ovzduší Sharp GP2Y1010AU0F

// proměnné pro nastavení propojovacích pinů
int mericiPin = A0;
int ledPin = 3;

// konstanty pro přesné měření
const int casMereni = 280;
const int casUstaleni = 40;
const int casSpanku = 9680;

// proměnné pro uložení výsledků měření
float napetiAnalog = 0;
float napetiPrepocet = 0;
float prasnost = 0;

void setup() {
  // komunikace přes sériovou linku rychlostí 9600 baud
  Serial.begin(9600);
  // nastavení ledPin jako výstupní
  pinMode(ledPin,OUTPUT);
}
  
float prumerMereni(int vzorky) {
  float suma = 0;
  for (int i = 0; i < vzorky; i++) {
    digitalWrite(ledPin, LOW);
    delayMicroseconds(casMereni);
    suma += analogRead(mericiPin);
    delayMicroseconds(casUstaleni);
    digitalWrite(ledPin, HIGH);
    delayMicroseconds(casSpanku);
  }
  return suma / vzorky;
}

void loop() {
  napetiAnalog = prumerMereni(10); // Průměr 10 vzorků
  napetiPrepocet = napetiAnalog * (5.0 / 1024.0);
  prasnost = (0.17 * napetiPrepocet - 0.1) * 1000;
  Serial.print("Napeti ze senzoru: ");
  Serial.print(napetiPrepocet);
  Serial.print(" V -> Koncentrace prachu: ");
  Serial.print(prasnost);
  Serial.println(" ug/m3");
  delay(1000);
}

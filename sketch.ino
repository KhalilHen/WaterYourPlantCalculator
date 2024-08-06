#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2   // what pin we're connected to
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);





float humidity;
float temperature; 
int chk;

 LiquidCrystal_I2C lcd(0x27, 16, 2);


#define LDR_PIN 2

int lightValue;
const float GAMMA = 0.7;
const float RL10 = 50;


int redPin = 3;
int greenPin = 4;
void setup() {
Serial.begin(9600);
  dht.begin();

  // put your setup code here, to run once:
  pinMode(LDR_PIN, INPUT);

  lcd.init();
    lcd.backlight();

    pinMode(redPin, OUTPUT);
        pinMode(greenPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
// humidity = dht.readHumidity();
// temperature = dht.readTemperature();

  int analogValue = analogRead(A0);
  float voltage = analogValue / 1024. * 5;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));



  Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Temp: ");
    Serial.print(temperature);
    Serial.println(" Celsius");

handleMoistureValue(); 

//Not working yet
 lightValue =  digitalRead(LDR_PIN);

  lcd.print("Room: ");
  if (lux < 600 && humidity ) {

  greenColor();

  } else {
    lcd.print("Dark  ");
  }



  lcd.setCursor(0, 1);
  lcd.print("Lux: ");
  lcd.print(lux);
  lcd.print("          ");
// If indoor plant
// 100-200 Lux

// If



// delay(5000);

//  greenColor();

// delay(2000);
// Later add a clock to check if daytime then activate this
dayTimeCheck();



     lcd.setCursor(0, 0);
     lcd.print("Humidity:");
     lcd.setCursor(10,0);
    lcd.print( humidity);
 delay(2000);

}


void dayTimeCheck() {

    if ((humidity >= 40 && humidity <= 60) && temperature >= 18) {

greenColor();


}


}


void handleMoistureValue() {

if (humidity > 30 && humidity < 60)
{
 greenColor();

}
else {
redColor();
}

}


//Color functions
//RED = Give water

 void redColor() {

  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
}
//Green is plant has enough water

 void greenColor() {

    digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
}
//Yellow special situation  still thinking of a use case

 void yellowColor() {

  
    digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
}

#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2   // what pin we're connected to
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);



#define LDR_PIN 7


float humidity;
float temperature; 
int chk;

 LiquidCrystal_I2C lcd(0x27, 16, 2);


int lightValue;

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
humidity = dht.readHumidity();
temperature = dht.readTemperature();


  Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Temp: ");
    Serial.print(temperature);
    Serial.println(" Celsius");

handleMoistureValue(); 

//Not working yet
 lightValue =  digitalRead(LDR_PIN);

 if(lightValue < 600 ) {

    greenColor();
    Serial.print("light:");
    Serial.print(lightValue);
 }

// If indoor plant
// 100-200 Lux

// If



// delay(5000);

//  greenColor();

// delay(2000);





     lcd.setCursor(0, 0);
     lcd.print("Humidity:");
     lcd.setCursor(10,0);
    lcd.print( humidity);
 delay(2000);

// Adjust this to a interval
 delay(5000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Temperature:");
 lcd.setCursor(10,0);
 lcd.print(temperature);

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

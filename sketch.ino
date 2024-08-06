#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2   // what pin we're connected to
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


  bool humidityCheck;
bool temperatureCheck;
bool  lightCheck;



// For night
bool  LightNightDayCheck;
bool temperatureNightCheck;



float humidity;
float temperature; 
int chk;
float lux;



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
humidity = dht.readHumidity();
temperature = dht.readTemperature();

  int analogValue = analogRead(A0);
  float voltage = analogValue / 1024. * 5;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));


 lightValue =  digitalRead(LDR_PIN);


  Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Temp: ");
    Serial.print(temperature);
    Serial.println(" Celsius");
  Serial.print(lux);
//Not working yet

 
 







 nightTimeCheck();
// Later add a clock to check if daytime then activate this
// dayTimeCheck();



     lcd.setCursor(0, 0);
     lcd.print("Humidity:");
     lcd.setCursor(10,0);
    lcd.print( humidity);
 delay(2000);

}


void dayTimeCheck() {



checkMoisture();
  handleDayTimeTemperature();
  handleDayTimeLight();
  if(temperatureCheck == true && humidityCheck == true   && lightCheck == true ) {


greenColor();

  } 
//   else if(temperatureCheck ==  || humidityCheck == null) { 
  
//     // Yellow stands for there wen't something wrong  
//     yellowColor();
// Serial.println("There wen't someting wrong");
//   }
 else{

  redColor();
 }

}



//This one also for in the night
boolean  checkMoisture() { 
  if (humidity >= 40 && humidity <= 60) {

     humidityCheck = true;
  }
  else {
   humidityCheck = false;
  }
}

boolean  handleDayTimeTemperature() {

   if(temperature >= 18 &&  temperature  <=  24) {

     temperatureCheck = true;
   }

  //  else if(temperature == null) {

  //   temperatureCheck =

  //  }
   else {

      temperatureCheck = false; 
   }
}
//too handle the light
boolean handleDayTimeLight() {

if(lux  >= 2000 && lux <=  5000 ) {
  lightCheck = true;
}

else {
lightCheck = false;
}
}



void  handleNightTimeTemperature() {

  if(temperature >= 15 && temperature <= 20) {

    temperatureNightCheck = true;

  } 
  else {

    temperatureNightCheck = false;

  }
}
void handleNightTimeLight() {


if(lux >= 0 && lux <= 200) {
    LightNightDayCheck = true;
}
else {
    LightNightDayCheck = false;
}
}
void nightTimeCheck() {

  handleNightTimeLight();
  handleNightTimeTemperature();
   checkMoisture();
   if(temperatureNightCheck == true &&  LightNightDayCheck == true  &&   humidityCheck == true) {


    greenColor();
   } else {
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

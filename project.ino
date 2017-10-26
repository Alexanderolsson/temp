#include<UnoWiFiDevEd.h>
#include<LiquidCrystal.h>
#include<Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>



#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal lcd(12,11,6,5,4,3);
void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  Wifi.begin();
  sensors.begin();
}

void loop() {
  while(Wifi.available()){
    process(Wifi);
  }
  sensors.requestTemperatures();
  float celsius = sensors.getTempCByIndex(0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(celsius);
  lcd.print("c");
  Serial.println(celsius);
  delay(2000);
}

void process(WifiData client){
  String command = client.readStringUntil('/');
  if (command == "digital") {
    digitalCommand(client);
  }
}

void digitalCommand(WifiData client) {
  
  if (client.read() == '/') {
  }
  float celsius = sensors.getTempCByIndex(0);
  client.println("HTTP/1.1 200 OK\n");
  client.println(celsius);
  client.println(EOL);    //char terminator

}


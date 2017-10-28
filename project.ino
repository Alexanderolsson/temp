#include<UnoWiFiDevEd.h>
#include<LiquidCrystal.h>
#include<Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
//Libs som behövs

//Säger att termometern är på utgång 2
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//Koppling till display
LiquidCrystal lcd(12,11,6,5,4,3);
void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  Wifi.begin();
  sensors.begin();
}

void loop() {
  //Kollar ifall wifi finns.
  while(Wifi.available()){
    process(Wifi);
  }
  //printar ut till LCD.
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
  /*Kollar ifall någon ansluter till arduinon via websida på http://x.y.z.n/digital
  Ifall man ansluter till den IP adressen kommer functionen digitalCommand köras som visar temperaturen på sin hemsida.
  */
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


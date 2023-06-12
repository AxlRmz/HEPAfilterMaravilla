

#include "PMS.h" //Biblioteca para los sensores PMS
#include "SoftwareSerial.h"
#include "DHT.h"
#include "HardwareSerial.h"

////variables de interruptor
int strt = 0;
int estadoAC = 0;
int estadoAN = 0;

#define DHTPIN 18
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
byte received_data[4];
int  switch_pos;
// corresponde a RX, TX 
//es decir, RX del sensor se conecta al pin 3 y el TX del sensor al pin 2
//SoftwareSerial pmmserial();

HardwareSerial PMSerial(2);

PMS pms(PMSerial);
PMS::DATA data;

void setup()
{ 
 Serial.begin(9600);
 PMSerial.begin(9600);
 pinMode(21,OUTPUT);
 pinMode(22,OUTPUT);
 digitalWrite(22, LOW);
 digitalWrite(21, LOW);
 
 
 
 //Serial.println("Warming up");
 //delay(4000);
 
}
void loop() {
  
  if (pms.read(data)) {
  //Serial.println("Dust Concentration");

    
    int h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    int t = dht.readTemperature();

    Serial.print("PM1.txt=");  //"(ug/m3)"
    Serial.print("\"" + String(data.PM_AE_UG_1_0) + "\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("PM2.txt=");
    Serial.print("\"" + String(data.PM_AE_UG_2_5) + "\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("PM10.txt=");
    Serial.print("\""+ String(data.PM_AE_UG_10_0)+"\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("hum.val=");
    //Serial.print("\"");
    Serial.print(h);
    //Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);

    Serial.print("temp.val=");
    //Serial.print("\"");
    Serial.print(t);
    //Serial.print("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);



    delay(5000);
  }
  switchcontrol();
}

void switchcontrol(){
  
  //Interruptor
  String dat =Serial.readString();
  estadoAC=int(dat[0]);
  if (estadoAC && estadoAN == 0)
  {
    strt = 1 - strt;
    delay(100);
  }
  estadoAN = estadoAC;

  //Cuerpo de instrucciones
  if (strt == 1){
    digitalWrite(22, HIGH);
    digitalWrite(21,HIGH);

  } else if (strt == 0){
    digitalWrite(22, LOW);
    digitalWrite(21,LOW);
  }
  


}
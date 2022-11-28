#include <SoftwareSerial.h>

SoftwareSerial bt_serial(1,0);

void setup()
{
  bt_serial.begin(38400);

Serial.begin(9600); Serial.flush(); while(Serial.available()>0)Serial.read();

  Serial.println(String("INTRODUCIR COMANDOS AT"));

}


void loop()
{
    if ((bt_serial.available()>0)) {
      Serial.println(bt_serial.read());
    }
}

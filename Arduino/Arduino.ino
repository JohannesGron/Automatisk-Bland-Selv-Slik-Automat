#include <SoftwareSerial.h>

//A4 = RX esp8266
//A3 = TX esp8266

SoftwareSerial softSerial(17, 18);

void setup() {
  // put your setup code here, to run once:
  softSerial.begin(115200);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (softSerial.available()) {
    Serial.write(softSerial.read());
  }
}

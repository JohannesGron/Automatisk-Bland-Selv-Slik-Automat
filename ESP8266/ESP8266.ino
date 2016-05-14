#include <ESP8266WiFi.h>
#include <Wire.h>

int request(const char* url, char* buf);
void filterResponse(char* buf, int len);

bool sendOrder = true;

char idToDelete[6];
int bufIdx = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(0, 2);

  WiFi.begin("NAO", "RobotWifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

unsigned long lastUpdate = 0;

void loop() {
  if (!sendOrder) {
    while (Wire.available()) {
      Serial.write(Wire.read());
      idToDelete[bufIdx] = (char)Wire.read();
      //Serial.println((int)idToDelete[bufIdx]);
      if (idToDelete[bufIdx] == '\0') {
        char url[48];
        strcpy(url, "/joha2514/slikautomat/bestillinghentet.php?id=");
        strcat(url, idToDelete);
        Serial.println(url);
        
        char responseBuf[512];
        request(url, responseBuf);
        
        bufIdx = 0;
        sendOrder = true;
      } else {
        bufIdx++;
      }
    }
  } else {
    if (millis() - lastUpdate > 5000) {
      lastUpdate = millis();

      char responseBuf[512];
      int responseLen = request("/joha2514/slikautomat/hentbestilling.php", responseBuf);
      filterResponse(responseBuf, responseLen);

      Wire.requestFrom(8, 6);
      sendOrder = false;
    }
  }
}

int request(const char* url, char* buf) {
  WiFiClient client;
      
  if (!client.connect("webhotel.herningsholm.dk", 80)) {
    return 0;
  }

  char tmp[256];
  strcpy(tmp, "GET ");
  strcat(tmp, url);
  strcat(tmp, " HTTP/1.1\r\nHost: webhotel.herningsholm.dk\r\nConnection: close\r\n\r\n");

  client.print(tmp);
  
  unsigned long timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      client.stop();
      return 0;
    }
  }

  int i = 0;
  
  while (client.available()) {
    buf[i] = (char)client.read();
    i++;
  }

  return i;
}

void filterResponse(char* buf, int len) {
  for (int i = 2; i < len - 1; i++) {
    if (buf[i] == '\n' && buf[i - 2] == '\n') {
      Wire.beginTransmission(8);
      for (int j = i + 1; j < len; j++) {
        Wire.write(buf[j]);
      }
      Wire.write((char)'\0');
      Wire.endTransmission();

      return;
    }
  }
}


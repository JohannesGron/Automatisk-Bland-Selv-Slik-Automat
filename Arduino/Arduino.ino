#include <Wire.h>
#include <errno.h>

struct Order {
  char customer[128];
  int id;
  int mm;
  int jelly;
  int pinocchio;
};
Order currentOrder;
bool orderValid = false;

bool toOrder();

char serialBuf[512];
int idx = 0;

char id[6];
int idLen;

void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
}

void receiveEvent(int count) {  
  while (Wire.available()) {
    int c = Wire.read();
    
    serialBuf[idx] = (char)c;
    idx++;

    if (c == '\0') {
      if (toOrder()) {
        itoa(currentOrder.id, id, 10);
        idLen = strlen(id);
        orderValid = true;
        
        Serial.println(currentOrder.customer);
        Serial.println(currentOrder.id);
        Serial.println(currentOrder.mm);
        Serial.println(currentOrder.jelly);
        Serial.println(currentOrder.pinocchio);
      } else {
        orderValid = false;
        Serial.println("ingen nye ordre");
      }
      
      idx = 0;
    }
  }
}

void requestEvent() {
  if (orderValid) {
    Serial.println(idLen);
    Serial.println("id ");
    Serial.println(id);
    //Wire.write(id, idLen);
    //Wire.write("\0");
    Wire.write(65);
  } else {
    Wire.write("0\0");
  }
}

bool toOrder() {
  // http://www.cplusplus.com/reference/cstdlib/strtol/
  char *endptr;
  long int id = strtol(serialBuf, &endptr, 10);
  if (errno) {
    errno = 0;
    return false;
  }
  currentOrder.id = id;

  int idx = 0;
  while (*(endptr + 1 + idx) != ';') {
    currentOrder.customer[idx] = *(endptr + 1 + idx);
    idx++;
  }
  currentOrder.customer[idx] = '\0';

  long int pinocchio = strtol(endptr + 2 + idx, &endptr, 10);
  if (errno) {
    errno = 0;
    return false;
  }
  currentOrder.pinocchio = pinocchio;

  long int mm = strtol(endptr + 1, &endptr, 10);
  if (errno) {
    errno = 0;
    return false;
  }
  currentOrder.mm = mm;

  long int jelly = strtol(endptr + 1, &endptr, 10);
  if (errno) {
    errno = 0;
    return false;
  }
  currentOrder.jelly = jelly;
  
  return true;
}


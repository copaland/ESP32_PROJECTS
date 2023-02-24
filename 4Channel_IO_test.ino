// 4채널 ESP32 Relay 보드 v1.5
// 입력핀 출력확인 소스 입니다. 2023-02-14
//

#define NUM_PORTS  4

// Assign each GPIO to a relay
int relayGPIOs[NUM_PORTS] = {33, 32, 27, 26}; //Output pin
int inputGPIOs[NUM_PORTS] = {16, 17, 18, 19}; //Input pin
int newKey[NUM_PORTS] = {};
int oldKey[NUM_PORTS] = {};
bool swFlag[NUM_PORTS] = {0,0,0,0};

void initIO(void){
  for(int i=1; i<=NUM_PORTS; i++){
    pinMode(inputGPIOs[i-1], INPUT);
    pinMode(relayGPIOs[i-1], OUTPUT);
    digitalWrite(relayGPIOs[i-1],LOW);
    newKey[i-1] =!digitalRead(inputGPIOs[i-1]);  
  }
}

bool swCheck(void){
  for(int i=1; i<=NUM_PORTS; i++){
    oldKey[i-1] = newKey[i-1];
    newKey[i-1] =!digitalRead(inputGPIOs[i-1]);
    if((newKey[i-1] != oldKey[i-1]) && newKey[i-1]){ // if KEY pressed
      Serial.print("입력신호-");    //
      Serial.println(i+0x30);
      swFlag[i-1] = !swFlag[i-1];  //Toggle state
      //digitalWrite(relayGPIOs[i-1],swFlag[i-1]); //
    }
    delayMicroseconds(100);
  }
  return swFlag;
}

void relayOUT(bool flag){
  for(int i=1; i<=NUM_PORTS; i++){
    if(swFlag[i-1]==HIGH){ // if KEY pressed
      digitalWrite(relayGPIOs[i-1],HIGH); //
    } else {
      digitalWrite(relayGPIOs[i-1],LOW); //
    }
  }
}

void setup() {
  Serial.begin(115200);
  initIO();
}

void loop() {
  relayOUT(swCheck());
  delay(100);
}

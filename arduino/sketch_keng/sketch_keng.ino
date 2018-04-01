#include <TaskScheduler.h>
#include "http.h"
#include "wifi.h"

// Callback methods prototypes
void blink();
void checkSwitch();
Task t1(500, TASK_FOREVER, &blink);
Task t2(1000, TASK_FOREVER, &checkSwitch);
Scheduler runner;


const int doorPin1 = 12;
const int doorPin2 = 13;
const int doorPin3 = 14;
const int doorPin4 = 15;

int doorState1 = 0;
int doorState2 = 0;
int doorState3 = 0;
int doorState4 = 0;
int doorState = 10000;
int state1 = 0;
int state2 = 0;
int state3 = 0;
int state4 = 0;
int state = 0;
char stateStr[5];

void setup() {
  Serial.begin ( 9600 );
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(doorPin1, INPUT);
  pinMode(doorPin2, INPUT);
  pinMode(doorPin3, INPUT);
  pinMode(doorPin4, INPUT);
  connectWifi();
  runner.init();
  runner.addTask(t1);
  runner.addTask(t2);
  t1.enable();
  t2.enable();
}

void loop() {
  runner.execute();
  // delay(1000);
}

void blink(){
  static boolean output = HIGH;
  digitalWrite(LED_BUILTIN, output);
  output = !output;
  Serial.println(output);
}

void checkSwitch(){
  state1 = digitalRead(doorPin1);
  state2 = digitalRead(doorPin2);
  state3 = digitalRead(doorPin3);
  state4 = digitalRead(doorPin4);
  state = state1 + state2*10 + state3*100 + state4*1000 + 10000;
  Serial.print(getTime());
  Serial.print("-");
  Serial.println(stateStr);
  if(state != doorState && wifiIsConnected() == 1){
    doorState = state;
    itoa(state, stateStr, 10);
    uploadData(stateStr);
  }
}


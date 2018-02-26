
int rlyPin = 3;
int mutePin = 8;
int alarmPin = 9;
int muteBtnState = 0;
int alarmState = 0;
int prevAlarmState = 1;
int prevMuteState = 0;
int long muteTime = 300000; //in milliseconds
int long muteTimer = millis();
int long muteTimerElapsed = 0;
int muteState = 0;

void setup() {

  pinMode(rlyPin, OUTPUT);
  pinMode(mutePin, INPUT_PULLUP);
  pinMode(alarmPin, INPUT_PULLUP);
  //Serial.begin(9600);

}

void loop() {

  muteBtnState = digitalRead(mutePin);
  alarmState = digitalRead(alarmPin);
  //delay(500);
  //Serial.println(muteBtnState);

  //check if mute button was pushed
  if (muteBtnState == 1) {
    muteTimer = millis();
    setRelay(0);
    muteState = 1;
  }

  //mute state is "on" if still within mute time
  muteTimerElapsed = millis() - muteTimer;
  if (muteTimerElapsed > muteTime) {
    muteState = 0;
  }

  if (alarmState == 1 && prevAlarmState == 0) {
    muteTimer = 0;
    muteState = 0;
  };
  
  //turn on relay if alarm is active and not muted
  if (alarmState == 1 && muteState == 0) {
    setRelay(1);
  }

  if (alarmState == 0) {
    setRelay(0);
  }

  prevAlarmState = alarmState;
}

void setRelay(int state) {
  digitalWrite(rlyPin, state);
}


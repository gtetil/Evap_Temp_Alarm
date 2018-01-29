
int rlyPin = 3;
int mutePin = 8;
int alarmPin = 9;
int muteBtnState = 0;
int alarmState = 0;
int prevAlarmState = 0;
int prevMuteState = 0;
int muteTime = 3000; //in milliseconds
int muteTimer;
int muteTimerElapsed = 0;
int muteState = 0;

void setup() {

  pinMode(rlyPin, OUTPUT);
  pinMode(mutePin, INPUT_PULLUP);
  pinMode(alarmPin, INPUT_PULLUP);

}

void loop() {

  muteBtnState = !digitalRead(mutePin);
  alarmState = !digitalRead(alarmPin);

  //check if mute button was pushed
  if (muteBtnState == 1 && prevMuteState == 0) {
    muteTimer = millis();
  }

  //mute state is "on" if still within mute time
  muteTimerElapsed = millis() - muteTimer;
  if (muteTimerElapsed > muteTime) {
    muteState = 0;
  }
  else {
    muteState = 1;
  }

  //turn on relay if alarm is active and not muted
  if (alarmState == 1 && muteState == 0) {
    setRelay(1);
  }
  else {
    setRelay(0);
  }

}

void setRelay(int state) {
  digitalWrite(rlyPin, state);
}


//variables for encoder
byte encAlastleft;
int durationleft;
bool dirleft;
// variables for RPM
//static unsigned long now, lastTime, lastTime2;
int counterleft;
//int currentPos, lastPos;
//long RPM;

byte encAlastright;
int durationright;
bool dirright;
// variables for RPM
//static unsigned long now, lastTime, lastTime2;
int counterright;
//int currentPos, lastPos;
//long RPM;

void leftinitRPM(){
  pinMode(leftencoderA, INPUT);
  pinMode(leftencoderB, INPUT);
  attachInterrupt(leftencoderB, leftwheelPulse, CHANGE);
}

void rightinitRPM(){
  pinMode(rightencoderA, INPUT);
  pinMode(rightencoderB, INPUT);
  attachInterrupt(rightencoderB, rightwheelPulse, CHANGE);
}

int leftRPM(){
  static unsigned long now, then, then2;
  static int currentPos, lastPos;
  long RPM;
  now = millis();
  if(now-then >= 100){
    currentPos = counterleft;
    RPM = (currentPos-lastPos)*0.7352941176470588;
    lastPos = currentPos;
    then = now;
  }
  if((now-then2)>=500){
    Serial.print("Currrent RPM:");
    Serial.println(RPM);
    Serial.print("pulse:");
    Serial.println(durationleft);
    //Serial.print("Currrent output:");
    //Serial.println(output);
    then2 = now;
  }
  return RPM;
}

int rightRPM(){
  static unsigned long now, then, then2;
  static int currentPos, lastPos;
  long RPM;
  now = millis();
  if(now-then >= 100){
    currentPos = counterright;
    RPM = (currentPos-lastPos)*0.7352941176470588;
    lastPos = currentPos;
    then = now;
  }
  if((now-then2)>=500){
    Serial.print("Currrent RPM:");
    Serial.println(RPM);
    Serial.print("pulse:");
    Serial.println(counterright);
    //Serial.print("Currrent output:");
    //Serial.println(output);
    then2 = now;
  }
  return RPM;
}


void leftwheelPulse(){

  int lastState = digitalRead(rightencoderA);
  if((encAlastleft == LOW)&&(lastState == HIGH)){
    int val = digitalRead(leftencoderB);
    if(val == LOW && dirleft){
      dirleft = false;
    }
    else if(val == HIGH && !dirleft){
      dirleft = true;
    }
  }
  encAlastleft = lastState;

  if(!dirleft) durationleft++;
  else durationleft--;
  counterleft = durationleft;
 
}

void rightwheelPulse(){

  int lastState = digitalRead(rightencoderA);
  if((encAlastright == LOW)&&(lastState == HIGH)){
    int val = digitalRead(rightencoderB);
    if(val == LOW && dirright){
      dirright = false;
    }
    else if(val == HIGH && !dirright){
      dirright = true;
    }
  }
  encAlastright = lastState;

  if(!dirright) durationright++;
  else durationright--;
  counterright = durationright;
 
}

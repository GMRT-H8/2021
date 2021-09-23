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
  static int currentPos = 0;
  static int lastPos = 0;
  static long RPM = 0;
  now = millis();
  if(now-then >= 25){
    currentPos = counterleft;
    RPM = (currentPos-lastPos)*0.7352941176470588*4;
    lastPos = currentPos;
    then = now;
  }
  /*
  if((now-then2)>=500){
    Serial.print("Currrent RPM:");
    Serial.println(RPM);
    Serial.print("pulse:");
    Serial.println(counterleft);
    //Serial.print("Currrent output:");
    //Serial.println(output);
    then2 = now;
  }
  */
  return RPM;
  
}

int rightRPM(){
  static unsigned long now, then, then2;
  static int currentPos = 0; 
  static int lastPos = 0;
  static int RPM = 0;
  now = millis();
  if(now-then >= 25){
    currentPos = counterright;
    RPM = (currentPos-lastPos)*0.7352941176470588*4;
    lastPos = currentPos;
    then = now;
  }
  /*
  if((now-then2)>=1000){
    Serial.print("Currrent RPM:");
    Serial.println(RPM);
    Serial.print("pulse:");
    Serial.println(counterright);
    //Serial.print("Currrent output:");
    //Serial.println(output);
    then2 = now;
  }
  */
  return RPM;
}

void leftwheelPulse(){

  int lastState = digitalRead(leftencoderA);
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

  if(!dirleft) counterleft++;
  else counterleft--;
 
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

  if(!dirright) counterright++;
  else counterright--;
 
}

void servoinitRPM2(){
  pinMode(servoencoderA,INPUT);
  pinMode(servoencoderB,INPUT);
  first_stateA=digitalRead(servoencoderA);
  first_stateB=digitalRead(servoencoderB);
  //Serial.begin(115200);
}

void servowheelPulse2(){
  
  current_stateA = digitalRead(servoencoderA);
  current_stateB = digitalRead(servoencoderB);
  
  if (current_stateA != first_stateA){
    if(current_stateB != current_stateA){
      counterservo++;
    }
    else{
      counterservo--;
    }
    first_stateA = current_stateA; 
  }
   
  if (current_stateB != first_stateB){
    if(digitalRead(servoencoderA) != current_stateB){
      counterservo--;
    }
    else{
      counterservo++;
    }       
    first_stateB = current_stateB;
  }
  
          //Serial.print("Position:");
          //Serial.println(counter);
          /*
          Serial.print("encA:");
          Serial.println(digitalRead(inputA));
          Serial.print("encB:");
          Serial.println(digitalRead(inputB));
          */
    //Serial.print("test");
    delayMicroseconds(50);
}

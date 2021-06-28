
void initmotorright(byte pinA, byte pinB){
  // initialize pin mode
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  // initialize pwm
  //ledcSetup(ledChannel, freq, resolution);
  ledcSetup(0, 5000, 8);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pinA, 0);
  ledcAttachPin(pinB, 0);
}

void initmotorleft(byte pinA, byte pinB){
  //initialize pin mode
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  
  // initialize pwm
  //ledcSetup(ledChannel, freq, resolution);
  ledcSetup(0, 5000, 8);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pinB, 0);
  ledcAttachPin(pinB, 0);

}

void motorright(bool direct, int velocity){
  if(direct){
    ledcWrite(MR_A, velocity);
    ledcWrite(MR_B, 0); 
  }
  if(!direct){  
    ledcWrite(MR_A, 0);
    ledcWrite(MR_B, velocity);
  }
}

void motorleft(bool direct, int velocity){
  if(direct){
    ledcWrite(ML_A, velocity);
    ledcWrite(ML_B, 0); 
  }
  if(!direct){
    ledcWrite(ML_A, 0);
    ledcWrite(ML_B, velocity);
  }
}

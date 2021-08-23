void initmotor(){
  pinMode(MR_A, OUTPUT);
  pinMode(MR_B, OUTPUT);
  pinMode(ML_A, OUTPUT);
  pinMode(ML_B, OUTPUT);
}

void initmotorright(){
  // initialize pin mode
  // initialize pwm
  //ledcSetup(ledChannel, freq, resolution);
  ledcSetup(4, 5000, 8);
  ledcSetup(5, 5000, 8);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(MR_A, 4);
  ledcAttachPin(MR_B, 5);
  Serial.println("Rigth motor is ready to use");
}

void initmotorleft(){
  //initialize pin mode
 // pinMode(ML_A, OUTPUT);
 // pinMode(ML_B, OUTPUT);
  
  // initialize pwm
  //ledcSetup(ledChannel, freq, resolution);
  ledcSetup(2, 5000, 8);
  ledcSetup(3, 5000, 8);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ML_B, 2);
  ledcAttachPin(ML_A, 3);
  Serial.println("Left motor is ready to use");
}

void motorright(bool direct, int velocity){
  //Serial.println("nilai PWM:");
  //Serial.println(rightoutput);
  if(direct){
    //Serial.println("Motor Right CW");
    ledcWrite(4, velocity);
    ledcWrite(5, 0);
  }
  if(!direct){
    //MyPIDleft.();
    //Serial.println("Motor Right CCW");  
    ledcWrite(4, 0);
    ledcWrite(5, velocity);
  }
}

void motorleft(bool direct, int velocity){
  if(direct){
    //Serial.println("Motor Left CW");
    ledcWrite(2, velocity);
    ledcWrite(3, 0); 
  }
  if(!direct){
    //Serial.println("Motor Left CCW");
    ledcWrite(2, 0);
    ledcWrite(3, velocity);  
  }
}

void speedup(int velocity){
  velocity = velocity + 100;
  if(velocity >250){
    velocity = 250;
  }
}

void speeddown(int velocity){
  velocity = velocity - 100;
  if(velocity<0){
    velocity = 0;
  }
}

void initctrlmotorright(){
  // initialize pin mode
  // initialize pwm
  //ledcSetup(ledChannel, freq, resolution);
  ledcSetup(4, 5000, 8);
  ledcSetup(5, 5000, 8);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(MR_A, 4);
  ledcAttachPin(MR_B, 5);

  MyPIDright.SetMode(AUTOMATIC);
  
  Serial.println("Rigth motor is ready to use");
}
void initctrlmotorleft(){
  // initialize pin mode
  // initialize pwm
  //ledcSetup(ledChannel, freq, resolution);
  ledcSetup(4, 5000, 8);
  ledcSetup(5, 5000, 8);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(MR_A, 4);
  ledcAttachPin(MR_B, 5);

  MyPIDleft.SetMode(AUTOMATIC);
  
  Serial.println("Rigth motor is ready to use");
}


void ctrl_motorright(long setpoint){
    //Serial.println("XXX");
    
    if(flagdirectright){
      MyPIDright.SetControllerDirection(DIRECT);
      rightsetpoint = setpoint;
      MyPIDright.Compute();
    }
    
    if(!flagdirectright){
      MyPIDright.SetControllerDirection(REVERSE);
      rightsetpoint = -setpoint;
      MyPIDright.Compute();
    }
}

void ctrl_motorleft(long setpoint){
    //Serial.println("YYY");
    
    if(flagdirectleft){
      MyPIDleft.SetControllerDirection(DIRECT);
      leftsetpoint = setpoint;
      MyPIDleft.Compute();
    }
    
    if(!flagdirectleft){
      MyPIDleft.SetControllerDirection(REVERSE);
      leftsetpoint = -setpoint;
      MyPIDleft.Compute();
    }
}

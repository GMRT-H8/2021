
void initPS3Controller(){
  //Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("01:01:01:01:01:01");
    //Ps3.begin("02:02:02:02:02:02");

    Serial.println("Ready.");
    player = 1;
    //-------------------- Player LEDs -------------------
    Serial.print("Setting LEDs to player "); Serial.println(player, DEC);
    Ps3.setPlayer(player);
    delay(100);
}

void eventPS3Controller(){
    // move servo
    // tombol segitiga vertikal servo CW
    if( Ps3.event.button_down.triangle ){
        //Serial.println("Started pressing the triangle button");
        Serial.println("servo vertikal ke atas");                
        servo1cont(true,2);
        delay(50);
    }
    
    if( Ps3.event.button_up.triangle ){
        //Serial.println("Released the triangle button");
        Serial.println("servo vertikal stop");    
        servo1stop();
        delay(50);
    }

    // tombol x servo vertikal CCW
    if( Ps3.event.button_down.cross ){
        //Serial.println("Started pressing the cross button");
        //delay(250);
        Serial.println("servo vertikal turun");
        
        servo1cont(false,2);
        delay(50);
    }
    if( Ps3.event.button_up.cross ){
        //Serial.println("Released the cross button");
        //servo2stop();
        Serial.println("servo stop");
        
        servo1stop();
        delay(50);
    }

    
    // tombol kotak for servo horizontal buka
    if( Ps3.event.button_down.square ){
        //Serial.println("Started pressing the square button");
        Serial.println("servo horizontal ke buka");
        servo2cont(false,2);
        delay(50);
    }
    if( Ps3.event.button_up.square ){
        Serial.println("servo horizontal stop");
        servo2stop();
        delay(50);
    }
    
    // tombol bulet for servo horizontal tutup
    if( Ps3.event.button_down.circle ){
        //Serial.println("Started pressing the circle button");
        Serial.println("servo horizontal ke tutup");
        
        servo2cont(true,2);
        delay(50);
    }
    if( Ps3.event.button_up.circle ){
        //Serial.println("Released the circle button");
        //delay(250);
        Serial.println("servo horizontal stop");
        
        servo2stop();
        delay(50);
    }

    // tombol pad kanan for servo90
    if( Ps3.event.button_down.right ){
        //Serial.println("Started pressing the right button");
        if(flagxservo90==0){
          Serial.println("servo 90 derajat, flagservo:");
          Serial.print(flagxservo90);
          
          myservo3.write(180);
          flagxservo90=1;
          //delay(250);
        }
        else if(flagxservo90==1){
          Serial.println("servo 0 derajat, flagservo:");
          Serial.print(flagxservo90);
          
          myservo3.write(0);
          flagxservo90=0;
        }
        delay(50);
    }
    if( Ps3.event.button_up.right ){
        Serial.println("Released the right button");
        delay(50);
    }

    // tombol atas bawah buat atur speed motor
    // tombol atas for speed up
    if( Ps3.event.button_down.up ){
        //Serial.println("Started pressing the right button");
        velocitymotor = velocitymotor + 100;
        if(velocitymotor>350){
          velocitymotor = 350;
        }
        
        delay(50);
    }
    if( Ps3.event.button_up.up ){
        //Serial.println("Released the right button");
        delay(50);
    }
    // tombol bawah for speed down
    if( Ps3.event.button_down.down ){
      //Serial.println("Started pressing the right button");
      //speeddown(velocityright);
      //speeddown(velocityleft);
      velocitymotor = velocitymotor - 100;
      if(velocitymotor<80){
        velocitymotor = 80;
      }
      delay(50);
    }
    if( Ps3.event.button_up.down ){
      //Serial.println("Released the right button");
      delay(50);
    }
    
    if( Ps3.event.button_down.left ){
      //Serial.println("Started pressing the right button");
      if(toggle==0){
        toggle=1;
      }
      else if(toggle==1){
        toggle=0;
      }
      delay(50);
    }
    if( Ps3.event.button_up.left ){
      //Serial.println("Released the right button");
      delay(50);
    }
    // L1,R1,L2,R2 for move robot
    // tombol R1,R2
    // buat motor kiri
    if( Ps3.event.button_down.r1 ){  
      flagdirectleft = true;
      leftact = true;
    }
    if( Ps3.event.button_up.r1 ){
      leftact = false;
    }
    if( Ps3.event.button_down.r2 ){
      flagdirectleft = false;
      leftact=true;
    }
    if( Ps3.event.button_up.r2 ){
      leftact = false;
    }
    
    if(leftact && flagdirectleft){
      motorleft(true, leftoutput);
      //motorleft(true, 80);
    }
    if(leftact && !flagdirectleft){
      motorleft(false, leftoutput);
      //motorleft(false, 80);
    }
    if(!leftact){
      motorleft(true, 0);    
    }
    
    // tombol L1,L2
    // buat motor kanan
    if( Ps3.event.button_down.l1 ){
      flagdirectright = true;
      rightact = true;
    }
    if( Ps3.event.button_up.l1 ){
      rightact = false;
    }
    if( Ps3.event.button_down.l2 ){
      flagdirectright = false;
      rightact = true;
    }
    if( Ps3.event.button_up.l2 ){
      rightact = false;
    }

    if(rightact && flagdirectright){
      motorright(true, rightoutput);
      //motorright(true, 80);
    }
    if(rightact && !flagdirectright){
      //motorright(false, 80);
      motorright(false, rightoutput);
    }
    if(!rightact){
      motorright(true, 0);    
    }
}

void notify()
{
    //--- Digital cross/square/triangle/circle button events ---
    if( Ps3.event.button_down.cross )
        Serial.println("Started pressing the cross button");
    if( Ps3.event.button_up.cross )
        Serial.println("Released the cross button");

    if( Ps3.event.button_down.square )
        Serial.println("Started pressing the square button");
    if( Ps3.event.button_up.square )
        Serial.println("Released the square button");

    if( Ps3.event.button_down.triangle )
        Serial.println("Started pressing the triangle button");
    if( Ps3.event.button_up.triangle )
        Serial.println("Released the triangle button");

    if( Ps3.event.button_down.circle )
        Serial.println("Started pressing the circle button");
    if( Ps3.event.button_up.circle )
        Serial.println("Released the circle button");

    //--------------- Digital D-pad button events --------------
    if( Ps3.event.button_down.up )
        Serial.println("Started pressing the up button");
    if( Ps3.event.button_up.up )
        Serial.println("Released the up button");

    if( Ps3.event.button_down.right )
        Serial.println("Started pressing the right button");
    if( Ps3.event.button_up.right )
        Serial.println("Released the right button");

    if( Ps3.event.button_down.down )
        Serial.println("Started pressing the down button");
    if( Ps3.event.button_up.down )
        Serial.println("Released the down button");

    if( Ps3.event.button_down.left )
        Serial.println("Started pressing the left button");
    if( Ps3.event.button_up.left )
        Serial.println("Released the left button");

    //------------- Digital shoulder button events -------------
    /*
    if( Ps3.event.button_down.l1 )
        Serial.println("Started pressing the left shoulder button");
    if( Ps3.event.button_up.l1 )
        Serial.println("Released the left shoulder button");

    if( Ps3.event.button_down.r1 )
        Serial.println("Started pressing the right shoulder button");
    if( Ps3.event.button_up.r1 )
        Serial.println("Released the right shoulder button");
    */

    //-------------- Digital trigger button events -------------
    if( Ps3.event.button_down.l2 )
        Serial.println("Started pressing the left trigger button");
    if( Ps3.event.button_up.l2 )
        Serial.println("Released the left trigger button");

    if( Ps3.event.button_down.r2 )
        Serial.println("Started pressing the right trigger button");
    if( Ps3.event.button_up.r2 )
        Serial.println("Released the right trigger button");

    //--------------- Digital stick button events --------------
    if( Ps3.event.button_down.l3 )
        Serial.println("Started pressing the left stick button");
    if( Ps3.event.button_up.l3 )
        Serial.println("Released the left stick button");

    if( Ps3.event.button_down.r3 )
        Serial.println("Started pressing the right stick button");
    if( Ps3.event.button_up.r3 )
        Serial.println("Released the right stick button");

    //---------- Digital select/start/ps button events ---------
    if( Ps3.event.button_down.select )
        Serial.println("Started pressing the select button");
    if( Ps3.event.button_up.select )
        Serial.println("Released the select button");

    if( Ps3.event.button_down.start )
        Serial.println("Started pressing the start button");
    if( Ps3.event.button_up.start )
        Serial.println("Released the start button");

    if( Ps3.event.button_down.ps )
        Serial.println("Started pressing the Playstation button");
    if( Ps3.event.button_up.ps )
        Serial.println("Released the Playstation button");


    //---------------- Analog stick value events ---------------
   if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
       Serial.print("Moved the left stick:");
       Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
       Serial.println();
    }

   if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
       Serial.print("Moved the right stick:");
       Serial.print(" x="); Serial.print(Ps3.data.analog.stick.rx, DEC);
       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ry, DEC);
       Serial.println();
   }

   //--------------- Analog D-pad button events ----------------
   if( abs(Ps3.event.analog_changed.button.up) ){
       Serial.print("Pressing the up button: ");
       Serial.println(Ps3.data.analog.button.up, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.right) ){
       Serial.print("Pressing the right button: ");
       Serial.println(Ps3.data.analog.button.right, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.down) ){
       Serial.print("Pressing the down button: ");
       Serial.println(Ps3.data.analog.button.down, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.left) ){
       Serial.print("Pressing the left button: ");
       Serial.println(Ps3.data.analog.button.left, DEC);
   }

   //---------- Analog shoulder/trigger button events ----------
   if( abs(Ps3.event.analog_changed.button.l1)){
       Serial.print("Pressing the left shoulder button: ");
       Serial.println(Ps3.data.analog.button.l1, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.r1) ){
       Serial.print("Pressing the right shoulder button: ");
       Serial.println(Ps3.data.analog.button.r1, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.l2) ){
       Serial.print("Pressing the left trigger button: ");
       Serial.println(Ps3.data.analog.button.l2, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.r2) ){
       Serial.print("Pressing the right trigger button: ");
       Serial.println(Ps3.data.analog.button.r2, DEC);
   }

   //---- Analog cross/square/triangle/circle button events ----
   if( abs(Ps3.event.analog_changed.button.triangle)){
       Serial.print("Pressing the triangle button: ");
       Serial.println(Ps3.data.analog.button.triangle, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.circle) ){
       Serial.print("Pressing the circle button: ");
       Serial.println(Ps3.data.analog.button.circle, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.cross) ){
       Serial.print("Pressing the cross button: ");
       Serial.println(Ps3.data.analog.button.cross, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.square) ){
       Serial.print("Pressing the square button: ");
       Serial.println(Ps3.data.analog.button.square, DEC);
   }

   //---------------------- Battery events ---------------------
    if( battery != Ps3.data.status.battery ){
        battery = Ps3.data.status.battery;
        Serial.print("The controller battery is ");
        if( battery == ps3_status_battery_charging )      Serial.println("charging");
        else if( battery == ps3_status_battery_full )     Serial.println("FULL");
        else if( battery == ps3_status_battery_high )     Serial.println("HIGH");
        else if( battery == ps3_status_battery_low)       Serial.println("LOW");
        else if( battery == ps3_status_battery_dying )    Serial.println("DYING");
        else if( battery == ps3_status_battery_shutdown ) Serial.println("SHUTDOWN");
        else Serial.println("UNDEFINED");
    }

}

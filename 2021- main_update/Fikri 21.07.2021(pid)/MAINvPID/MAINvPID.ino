#include <Ps3Controller.h>
#include <ESP32Servo.h>
#include <PID_v1.h>


Servo myservo1;
Servo myservo2;
Servo myservo3;
int player = 0;
int battery = 0;

/*berikut adalah panduan penggunaan pin yang benar dari kedua board (Ardan & Rizal)
  Board Ardan:
    //pin encoder
    leftencoderA = 4
    leftencoderB = 16
    rightencoderA = 2
    rightencoderB = 15
    //pin motor
    MR_A = 25
    MR_B = 27
    ML_A = 33
    ML_B = 32
    //pin servo
    servoPin1 = 14
    servoPin2 = 12
    servoPin3 = 13
  Board Rizal:
    leftencoderA = 17
    leftencoderB = 16
    rightencoderA = 22
    rightencoderB = 23
    //pin motor
    MR_A = 25
    MR_B = 26
    ML_A = 33
    ML_B = 32
    //pin servo
    servoPin1 = 27
    servoPin2 = 14
    servoPin3 = 12
*/
const byte leftencoderA = 4;
const byte leftencoderB = 16;
const byte rightencoderA = 2;
const byte rightencoderB = 15;

const byte servoencoderA = 23;
const byte servoencoderB = 22;

const byte ML_A = 33;
const byte ML_B = 32;
const byte MR_A = 25;
const byte MR_B = 27;


const byte servoPin1 = 14;
const byte servoPin2 = 12;
const byte servoPin3 = 13;

static int flagxservo;
static int flagxservo90;

static int velocitymotor; 

byte encAlastleft;
bool dirleft;
int counterleft;
byte encAlastright;
bool dirright;
int counterright;
byte encAlastservo;
bool dirservo;
int counterservo;

// variables for controlled motor
bool flagdirectright;
bool flagdirectleft;
bool rightact;
bool leftact;
int servoact;
bool servomode;
// left motor PID variables

double leftsetpoint, leftinput, leftoutput;
double leftKp= 0.075188;
double leftKi= 6.015;
double leftKd= 0;

// right motor PID variables
double rightsetpoint, rightinput, rightoutput;
double rightKp = 0.35042;
double rightKi = 6.0395;
double rightKd = 0;

PID MyPIDleft(&leftinput, &leftoutput, &leftsetpoint, leftKp, leftKi, leftKd, DIRECT);
PID MyPIDright(&rightinput, &rightoutput, &rightsetpoint, rightKp, rightKi, rightKd, DIRECT);

unsigned long past;

bool flagspeed;
bool toggle;
//bool flagtoggle;

int first_stateA, current_stateA;
int first_stateB, current_stateB;
int stateA, stateB;

void onConnect(){
    Serial.println("Connected.");
}

void setup()
{
    Serial.begin(115200);
    initctrlmotorright();
    initctrlmotorleft();
    //initmotorleft();
    dirleft = true;
    dirright = true;
    //initmotor();
    initPS3Controller();
    initservo();
    rightinitRPM();
    leftinitRPM();
    //servoinitRPM();
    servoinitRPM2();
    rightact = false;
    leftact = false;
    velocitymotor = 100;
    toggle = false;
    //flagtoggle=0;
    counterservo = 15;
    servoact = 4;
    servomode = true;
}

void loop()
{
    if(!Ps3.isConnected())
        return;
    eventPS3Controller();
    rightinput = rightRPM();
    leftinput = leftRPM();
    ctrl_motorright(velocitymotor);
    ctrl_motorleft(velocitymotor);
    //speedMode(toggle, 100, 300);
    Speedhaha(toggle, 100, 300);
    servowheelPulse2();
    /*
    if(millis()-past>=10){
      
      Serial.print("servoact: ");
      Serial.print(servoact);
      Serial.print(" servomode: ");
      Serial.print(servomode);
      Serial.print(" poosition: ");
      Serial.println(counterservo);
      past=millis();
    }
    */
}

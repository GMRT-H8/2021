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
const byte leftencoderA = 17;
const byte leftencoderB = 16;
const byte rightencoderA = 22;
const byte rightencoderB = 23;

const byte ML_A = 33;
const byte ML_B = 32;
const byte MR_A = 25;
const byte MR_B = 26;


const byte servoPin1 = 27;
const byte servoPin2 = 14;
const byte servoPin3 = 12;

static int flagxservo;
static int flagxservo90;

static int velocitymotor; 

byte encAlastleft;
bool dirleft;
// variables for RPM
//static unsigned long now, lastTime, lastTime2;
int counterleft;
//int currentPos, lastPos;
//long RPM;

byte encAlastright;
bool dirright;
// variables for RPM
//static unsigned long now, lastTime, lastTime2;
int counterright;
//int currentPos, lastPos;
//long RPM;

// variables for controlled motor
bool flagdirectright;
bool flagdirectleft;
bool rightact;
bool leftact;
// left motor PID variables

double leftsetpoint, leftinput, leftoutput;
double leftKp= 0.020473;//0.075188;
double leftKi= 1.6379;//6.015;
double leftKd= 0;

// right motor PID variables
double rightsetpoint, rightinput, rightoutput;
double rightKp = 0.025508;//0.35042;
double rightKi = 2.0406;//6.0395;
double rightKd = 0;

PID MyPIDleft(&leftinput, &leftoutput, &leftsetpoint, leftKp, leftKi, leftKd, DIRECT);
PID MyPIDright(&rightinput, &rightoutput, &rightsetpoint, rightKp, rightKi, rightKd, DIRECT);

unsigned long past;

bool flagspeed;
bool toggle;
//bool flagtoggle;

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
    rightact = false;
    leftact = false;
    velocitymotor = 100;
    toggle = false;
    //flagtoggle=0;
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
    
    if(millis()-past>=1000){
      Serial.print("speed: ");
      Serial.println(velocitymotor);
      //Serial.print("left: ");
      //Serial.println(leftinput);
      past=millis();
    }
}

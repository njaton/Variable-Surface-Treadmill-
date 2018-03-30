//This program is used to control various motors using the TB6612 motor driver and a atmega 2560. 
//Written by: Nick Jaton
//NASA Nebraska Space Grant
// Property of : University of Nebraska's Biomechanics Research Building

#include <SparkFun_TB6612.h>

//State what pins are used for the TB6612
int MyAIN1[] = {32,40};
int MyAIN2[] = {34,42};
int MyBIN1[] = {30,38};
int MyBIN2[] = {28,36};

int PWMA = 13;
int PWMB = 12;
int PWMC = 11;
int STBY = 10;

const int offsetA = 1;
const int offsetB = -1;
const int offsetC = 1;

int AIN1 = MyAIN1[0];
int AIN2 = MyAIN2[0];

int BIN1 = MyBIN1[0];
int BIN2 = MyBIN2[0];

int AIN3 = MyAIN1[1];
int AIN4 = MyAIN2[1];


// Motor set up 
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
Motor motor3 = Motor(AIN3, AIN4, PWMC, offsetC, STBY);

// Button 1 is used for the random digit generator. 
// Button 2 is used to have the motors move upwards. 
// Button 3 is used to have the motors move back to the home position.
 
const int Button1 = 4;
const int Button2 = 5;
const int Button3 = 7; 

int Button1State = 0;
int Button2State = 0;
int Button3State = 0;

// The different variables that will be used for each motor 
int Rand1 = 0;
int Rand2 = 0;
int Rand3 = 0;


void setup() 
{
  // indicate the Buad number for displaying information
  Serial.begin(9600);

  //Set each button as an input 
   pinMode(Button1,INPUT);
   pinMode(Button2,INPUT);
   pinMode(Button3,INPUT); 

}

void loop() 
{  
    // read the information on the buttons 
    Button1State = digitalRead(Button1);
    Button2State = digitalRead(Button2);
    Button3State = digitalRead(Button3);

      // Random number generator
      if (Button1State == HIGH) 
      {
        RandomNumbers();
        Button1State = LOW;
        delay(500);
      }
     
            // Move the cell top "upwards"
            if (Button2State == HIGH) 
            {
              MoveUp();
              Button2State = LOW;
              delay(500);
            }
     
                   // resets the cell top to the starting position
                   if (Button3State == HIGH) 
                   {
                       MoveDown();
                       Button3State = LOW;
                       delay(500);
                   }
      
}

//Random Number Generator Function
//This will determine the distance for each independent motor.  
void RandomNumbers()
{ 
  Serial.println("Current time values"); //Title

        //Motor 1
        Rand1 = random(10000, 20000); 
        Serial.println(Rand1); 

        //Motor 2
        Rand2 = random(10000, 20000); 
        Serial.println(Rand2);   

        //Motor 3
        Rand3 = random(10000, 20000); 
        Serial.println(Rand3); 

        Serial.println("ready for next command");

        delay(400);
}

//Upwards Movement Function
//This function will tell the motors to move upwards based on the predetermined value. 
void MoveUp()
{
             delay(100);

             //Motor 1
             motor1.drive(255,Rand1); 
             motor1.brake();
             delay(200);
             Serial.print("Motor one moved upwards ");
             Serial.println(Rand1);

             //Motor 2
             motor2.drive(255,Rand2); 
             motor2.brake();
             delay(200);
             Serial.print("Motor two moved upwards ");
             Serial.println(Rand2);

             //Motor 3
             motor3.drive(255,Rand3); 
             motor3.brake();
             delay(400);
             Serial.print("Motor three moved upwards ");
             Serial.println(Rand3);
}

//Reset Function
//This function works by telling the motors to reverse the same amount that it moved upwards. 
void MoveDown()
{
             delay(100);

             //Motor 1
             motor1.drive(-255,Rand1); 
             motor1.brake();
             delay(200);
             Serial.print("Motor one moved downwards ");
             Serial.println(Rand1);
       
             //Motor 2
             motor2.drive(-255,Rand2); 
             motor2.brake();
             delay(200);
             Serial.print("Motor twop moved downwards ");
             Serial.println(Rand2);

             //Motor 3
             motor3.drive(-255,Rand3); 
             motor3.brake();
             delay(200);
             Serial.print("Motor three moved downwards ");
             Serial.println(Rand3);
}


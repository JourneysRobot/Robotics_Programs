#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     shoulderJoint, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     rightFrontPair, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     leftFrontPair, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     rightRear,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     leftRear,      tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    handJoint,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    ramp,                 tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

///////////////////////////////////////////////////////////////////////////////////////
//                                                                                   //
//                                  Teleop                                           //
//                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "..\includes\AvoidWierd.h"

//***********************************************************//
//                       Variables                           //
//***********************************************************//

int maxHandValue = 250;
int minHandValue = 20;

//***********************************************************//
//                         Methods                           //
//***********************************************************//

void drive(int ycord,int xcord)
{
  int maxVal = 40;
  int turningVal = returnValueMotor(xcord, maxVal);
  int motorVal = returnValueMotor(ycord, maxVal);

  motor[leftRear] = motorVal - (2*turningVal);
	motor[leftFrontPair] = motorVal - (2*turningVal);

  motor[rightRear] = motorVal + (2*turningVal);
  motor[rightFrontPair] = motorVal + (2*turningVal);
}

void shoulderMovement(int ycord)
{
  if (ycord > 0)
  {
    int maxVal = 40;
    motor[shoulderJoint] = returnValueMotor(ycord, maxVal);
    return;
  }

  else
  {
    int maxVal = 40;
    motor[shoulderJoint] = returnValueMotor(ycord, maxVal);
    return;
  }
}

void handMovement(int dPad)
{
	int currentPosition = ServoValue[handJoint];
	int newPosition = currentPosition;

	if (dPad == 0)
	{
		if ((currentPosition + 1) < maxHandValue)
		{
			newPosition = currentPosition + 1;
		}
	}
	else if (dPad == 4)
	{
		if ((currentPosition - 1) > minHandValue)
		{
			newPosition = currentPosition - 1;
		}
	}
	servo[handJoint] = newPosition;
}

//***********************************************************//
//                      User Control                         //
//***********************************************************//

task main()
{
  waitForStart();

  while (true)
  {
    getJoystickSettings(joystick);

    int cont1_left_yval = avoidWeird(joystick.joy1_y1, 20); //y coordinate for the left joystick on controller 1
    int cont1_left_xval = avoidWeird(joystick.joy1_x1, 75); //x coordinate for the left joystick on controller 1
    int cont2_right_yval = avoidWeird(joystick.joy1_y2, 20);
    int cont2_dPad = joystick.joy1_TopHat; //Value of the dPad for controller 2

    drive(cont1_left_yval, cont1_left_xval);
    shoulderMovement(cont2_right_yval);
    handMovement(cont2_dPad);

    if (joy1Btn(4) == 1)
    {
    	servoChangeRate[handJoint] = 10;
    	if ((ServoValue[handJoint] + 5) < maxHandValue)
    	{
    		servo[handJoint] = ServoValue[handJoint] + 5;
    	}
    }
    if (joy1Btn(2) == 1)
    {
    	servoChangeRate[handJoint] = 10;
    	if ((ServoValue[handJoint] - 5) > minHandValue)
    	{
    		servo[handJoint] = ServoValue[handJoint] - 5;
    	}
  	}
  	if (joy2Btn(1) == 1)
  	{
  		servo[ramp] = 0;
  	}
  	if (joy2Btn(3) == 1)
  	{
  		servo[ramp] = 255;
  	}
  	if (joy2Btn(1) != 1 && joy2Btn(3) != 1)
  	{
  		servo[ramp] = 128;
  	}
  }
}

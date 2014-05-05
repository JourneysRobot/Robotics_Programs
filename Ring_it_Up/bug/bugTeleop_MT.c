#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     shoulderJoint, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     rightFrontPair, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     leftFrontPair, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     rightRear,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     leftRear,      tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    handJoint,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    ramp,                 tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
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

void all_stop()
{
	motor[leftFrontPair] = 0;
	motor[leftRear] = 0;
	motor[rightFrontPair] = 0;
	motor[rightRear] = 0;
	motor[shoulderJoint] = 0;
	servo[ramp] = 128;
}

void drive(int ycord,int xcord, int maxVal)
{
	int turningVal = returnValueMotor(xcord, maxVal);
	int motorVal = returnValueMotor(ycord, maxVal);

	motor[leftRear] = motorVal + (2*turningVal);
	motor[leftFrontPair] = motorVal + (2*turningVal);

	motor[rightRear] = motorVal - (2*turningVal);
	motor[rightFrontPair] = motorVal - (2*turningVal);
}

void shoulderMovement(int ycord)
{
	int maxVal = 40;
	motor[shoulderJoint] = returnValueMotor(ycord, maxVal);
	return;
}

void handMovement(int dPad)
{
	int currentPosition = ServoValue[handJoint];
	int newPosition = currentPosition;

	if (dPad == 0)
	{
		if ((currentPosition + 5) < maxHandValue)
		{
			newPosition = currentPosition + 5;
		}
	}
	else if (dPad == 4)
	{
		if ((currentPosition - 5) > minHandValue)
		{
			newPosition = currentPosition - 5;
		}
	}
	servo[handJoint] = newPosition;
}

void fold_arm(bool isDown)
{
	all_stop();
	if (isDown)
	{
		motor[shoulderJoint] = 40;
		wait1Msec(1300);
		servo[handJoint] = 60;
		wait1Msec(350);
		return;
	}
	else
	{
		motor[shoulderJoint] = -40;
		wait1Msec(700);
		servo[handJoint] = 160;
		motor[shoulderJoint] = -40;
		wait1Msec(900);
		return;
	}
}

//***********************************************************//
//                      User Control                         //
//***********************************************************//

task main()
{
	waitForStart();
	servoChangeRate[handJoint] = 10;
	int maxVal = 40;

	while (true)
	{
		getJoystickSettings(joystick);

		int cont1_left_yval = avoidWeird(joystick.joy1_y1, 20); //y coordinate for the left joystick on controller 1
		int cont1_left_xval = avoidWeird(joystick.joy1_x1, 75); //x coordinate for the left joystick on controller 1
		int cont1_right_yval = avoidWeird(joystick.joy1_y2, 20);
		int cont1_dPad = joystick.joy1_TopHat; //Value of the dPad for controller 2

		if (joy1Btn(4) == 1)
		{
			if ((ServoValue[handJoint] + 5) < maxHandValue)
			{
				servo[handJoint] = ServoValue[handJoint] + 5;
			}
		}
		if (joy1Btn(2) == 1)
		{
			if ((ServoValue[handJoint] - 5) > minHandValue)
			{
				servo[handJoint] = ServoValue[handJoint] - 5;
			}
		}
		if (joy1Btn(6) == 1)
		{
			fold_arm(false);
		}
		if (joy1Btn(5) == 1)
		{
			fold_arm(true);
		}

		if (joy1Btn(1) == 1)
		{
			maxVal = 100;
		}

		if (joy1Btn(1) != 1)
		{
			maxVal = 40;
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

		drive(cont1_left_yval, cont1_left_xval, maxVal);
		shoulderMovement(cont1_right_yval);
		handMovement(cont1_dPad);
	}
}

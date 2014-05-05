///////////////////////////////////////////////////////////////////
//
// 						 Autonomous Movement Functions
//							Specifically for Ring it Up
//
///////////////////////////////////////////////////////////////////

void allStop(){
  motor[rightRear] = 0;
  motor[rightFrontPair] = 0;
  motor[leftRear] = 0;
  motor[leftFrontPair] = 0;
  motor[shoulderJoint] = 0;
}

void moveStraight(int power, int duration){
  motor[rightRear] = power;
  motor[rightFrontPair] = power;
  motor[leftRear] = power;
  motor[leftFrontPair] = power;
  wait1Msec(duration);
  motor[rightRear] = 0;
  motor[rightFrontPair] = 0;
  motor[leftRear] = 0;
  motor[leftFrontPair] = 0;
}

void move(int powerRight, int powerLeft, int duration){
  motor[rightRear] = powerRight;
  motor[rightFrontPair] = powerRight;
  motor[leftRear] = powerLeft;
  motor[leftFrontPair] = powerLeft;
  wait1Msec(duration);
  motor[rightRear] = 0;
  motor[rightFrontPair] = 0;
  motor[leftRear] = 0;
  motor[leftFrontPair] = 0;
}

void setAllMotorVals (int power){
	motor[rightFrontPair] = power;
	motor[rightRear] = power;
	motor[leftFrontPair] = power;
	motor[leftRear] = power;
}

void setDriveMotorVals (int powerRight, int powerLeft){
	motor[rightRear] = powerRight;
  motor[rightFrontPair] = powerRight;
  motor[leftRear] = powerLeft;
  motor[leftFrontPair] = powerLeft;
}

void movearm (int power, int duration){
	motor[shoulderJoint] = power;
	wait1Msec(duration);
	motor[shoulderJoint] = 0;
}

void movehand(int position){
	servo[handJoint] = position;
}

void fold_arm(bool isFold){
	// if isFold is true, the arm will return to folded position
	// otherwise it will deploy to scoring position

	int scoringHand = 100;
	int packedHand = 205;

	allStop();
	if (isFold){
		servo[handJoint] = packedHand;
		while (nMotorEncoder[shoulderJoint] < -800){
			motor[shoulderJoint] = 30;
		}
		writeDebugStreamLine("arm is folded at: %d", nMotorEncoder[shoulderJoint]);
		//motor[shoulderJoint] = 40;
		//wait1Msec(1300);
		//servo[handJoint] = 80;
		//wait1Msec(350);
		return;
	}
	else{
		while (nMotorEncoder[shoulderJoint] > -2300){
			motor[shoulderJoint] = -30;
		}
		motor[shoulderJoint] = 0;
		writeDebugStreamLine("arm is halfway at: %d", nMotorEncoder[shoulderJoint]);
		servo[handJoint] = scoringHand;

		//motor[shoulderJoint] = -40;
		//wait1Msec(700);
		//writeDebugStreamLine("encoder is at 1: %d", nMotorEncoder[shoulderJoint]);
		//servo[handJoint] = 180;

		while (nMotorEncoder[shoulderJoint] > -4900){
			motor[shoulderJoint] = -30;
		}
		motor[shoulderJoint] = 0;
		writeDebugStreamLine("arm is extended at: %d", nMotorEncoder[shoulderJoint]);


		//motor[shoulderJoint] = -40;
		//wait1Msec(900);
		//writeDebugStreamLine("encoder is at 2: %d", nMotorEncoder[shoulderJoint]);
		//return;
	}
}

void deploySpear(bool isDeploy){
	//if isDeploy is true, the spear extends
	//otherwise, it retracts

	allStop();

	if (isDeploy){
		motor[spear] = 20;
		wait1Msec(4500);
		motor[spear] = 0;
		return;
	}

	else{
		motor[spear] = -20;
		wait1Msec(4000);
		motor[spear] = 0;
		return;
	}
}

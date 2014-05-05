///////////////////////////////////////////////////////////////
//                                                           //
//                      Basic Functions                      //
//                        for Movement                       //
//                                                           //
///////////////////////////////////////////////////////////////

void allStop()
{
  motor[rightRear] = 0;
  motor[rightFrontPair] = 0;
  motor[leftRear] = 0;
  motor[leftFrontPair] = 0;
  motor[shoulderJoint] = 0;
}

void moveStraight(int power, int duration)
{
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

void move(int powerRight, int powerLeft, int duration)
{
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

void moveArm (int power, int duration)
{
	motor[shoulderJoint] = power;
	wait1Msec(duration);
	motor[shoulderJoint] = 0;
}

void moveHand(int position)
{
	servo[handJoint] = position;
}

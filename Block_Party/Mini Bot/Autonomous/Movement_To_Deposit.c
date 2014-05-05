///////////////////////////////////////////////////////////////
//                                                           //
//                      Basic Functions                      //
//                        for Movement                       //
//                                                           //
///////////////////////////////////////////////////////////////

//side selection true/false
bool red_inner = false;
bool red_outer = false;
bool blue_inner = false;
bool blue_outer = false;
int multi = -1;




void moveStraight(int power, int duration)
{
  motor[rightSide] = power;
  motor[leftSide] = power;
  wait1Msec(duration);
  motor[rightSide] = 0;
  motor[leftSide] = 0;
}

void move(int powerRight, int powerLeft, int duration)
{
  motor[rightSide] = powerRight;
  motor[leftSide] = powerLeft;
  wait1Msec(duration);
  motor[rightSide] = 0;
  motor[leftSide] = 0;
}

void allStop()
{
  motor[rightSide] = 0;
  motor[leftSide] = 0;
  motor[shoulderJoint] = 0;
  motor[elbowJoint] = 0;
  motor[ballHopper] = 0;
}

void deployHopper(bool isUp, int power, int duration)
{
  if (isUp)
  {
    motor[ballHopper] = power;
    wait1Msec(duration);
  }
  if (isUp == false)
  {
    motor[ballHopper] = -1*power;
    wait1Msec(duration);
  }
  motor[ballHopper] = 0;
}

void deployArm()
{
  deployHopper(false,10,500);
  motor[elbowJoint] = 20;
  wait1Msec(500);
  motor[elbowJoint] = 0;
  deployHopper(false,20,500);
  motor[ballHopper] = 0;
  motor[shoulderJoint] = -20;
  wait1Msec(400);
  motor[shoulderJoint] = 0;
}

///////////////////////////////////////////////////////////////
//                                                           //
//                   Autonomous Functions                    //
//                                                           //
//                                                           //
///////////////////////////////////////////////////////////////
void chooser(){
  if(blue_outer){
    wait10Msec(200);
    moveStraight(20,3000);
    deployHopper(false,30,800);         //Lower the ball hopper
    wait10Msec(75);
    //moveStraight(20,500);
    move((50*multi),(-50*multi), 1000); //Turn left/right depending on multi and isBlue
    deployHopper(true,30,250);
    moveStraight(20,500);               //If isBlue, turn right - the point is to hit the crates on the way to
    move((-50*multi),(50*multi), 500); //the parking lot and get 10 extra points
    deployHopper(true,30,550);
    wait10Msec(75);
    moveStraight(50,4000);              //Park in the parking lot
    }if(blue_inner){
    moveStraight(20,2900);
    move((50*multi),(-50*multi),900);
    moveStraight(50,4900);
    }if(red_outer){
    wait10Msec(200);
    moveStraight(20,3000);
    deployHopper(false,30,800);         //Lower the ball hopper
    wait10Msec(75);
    //moveStraight(20,500);
    move((-50*multi),(50*multi), 1000); //Turn left/right depending on multi and isBlue
    deployHopper(true,30,250);
    moveStraight(20,500);               //If isBlue, turn right - the point is to hit the crates on the way to
    move((50*multi),(-50*multi), 500); //the parking lot and get 10 extra points
    deployHopper(true,30,550);
    wait10Msec(75);
    moveStraight(50,4000);              //Park in the parking lot
    } if(red_inner){
    moveStraight(20,3300);
    move((-50*multi),(50*multi),1100);
    moveStraight(75,5000);
  }
}

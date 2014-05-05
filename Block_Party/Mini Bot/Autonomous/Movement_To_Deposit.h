
void moveStraight(int power, int duration)
{
	motor[Right] = power;
	motor[Left] = power;
	wait1Msec(duration);
	motor[Right] = 0;
	motor[Left] = 0;
}

void move(int powerRight, int powerLeft, int duration)
{
	motor[Right] = powerRight;
	motor[Left] = powerLeft;
	wait1Msec(duration);
	motor[Right] = 0;
	motor[Left] = 0;
}
void hand (int position)
{
	servo[Auto_Hand] = position;
}

void allStop()
{
	motor[Right] = 0;
	motor[Left] = 0;
}




int find_ir(int i, int r){
	bool stops = false;
	while (!stops)
	{
		if(SensorValue[IRSeeker]==5 )
		{
			if(i<23)
			{
				moveStraight (r*50,50);
				hand(60);
				moveStraight (r*50,100);
				wait10Msec(40);
				hand(180);
				stops = true;
			}
			else
			{
				hand (60);
				moveStraight (r*50,100);
				wait10Msec(40);
				hand(180);
				stops = true;
			}
		}
		else
			moveStraight (r*30,100);
		i= i+1;
	}

	return i;
	return r;
}
void move_past_buckets(int i, int r, int z){
	//	string temp = i;
	//eraseDisplay();
	//nxtDisplayCenteredBigTextLine( 4,temp);
	//wait10Msec(10000);
	string print;
	print = i;
	nxtDisplayCenteredTextLine(0,print);
	wait10Msec(400);

	int n=0;
	while(26-i > n)
	{
		moveStraight (r*30,100);
		n= n+1;
	}
	{
		moveStraight (r*50,350);
		move (z*50,r*50,600);
		moveStraight (r*50,1100);
		move (z*50,r*50,1000);
		moveStraight (r*50,1900);
	}
}

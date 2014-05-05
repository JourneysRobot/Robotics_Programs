
int time(){
	int d = 1;
	int wait_time = 0;
	nxtDisplayTextLine(1, "L_ARROW = +time");
	nxtDisplayTextLine(2, "R_ARROW = Determine Position");
	nxtDisplayTextLine(5, "Delay Time?");
	bool select = false;
	while(!select){
		nxtDisplayCenteredTextLine(3, "%d", d);
		if(nNxtButtonPressed == 2){         //Left arrow is button 2
			wait10Msec(50);
			wait_time = 100*d;
			d++;
			select = false;
			}else if(nNxtButtonPressed == 1){    // Right arow is button 1
			wait10Msec(50);
			select = true;
		}
	}
	return wait_time;
}


int position(int r){
	nxtDisplayTextLine(1, "L_ARROW = FLAG FRIST");
	nxtDisplayTextLine(2, "R_ARROW = ARM FIRST");
	nxtDisplayTextLine(5, "WHICH COLOR?");
	bool select = false;
	while(!select){
		if(nNxtButtonPressed == 2){         //Left orange is button 2
			wait10Msec(50);
			r = +1;
			select = true;
			}else if(nNxtButtonPressed == 1){    // Right orange is button 1
			wait10Msec(50);
			r = -1;
			select = true;
		}
	}
	wait10Msec(100);
	eraseDisplay();
	nxtDisplayCenteredBigTextLine(4, "READY!");
	return r;
}

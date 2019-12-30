#include <stdlib.h>
#include <time.h>
#include "snake.h"
unsigned char map[16][16]={
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,},
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,}, 
	{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,}, 
};

unsigned char player[2]={4,15};
int car[6][2];
unsigned char error=0;

void printError(){
	int i,j=0;
    //*endSnake=0;
	for(j=0;j<16;++j){
		for(i=0;i<16;++i){
			if(i==j||i==15-j)
				map[j][i]=1;
			else
				map[j][i]=0;
		}
	}
}


void updateCar(){
	int i,j;
	for(j=0;j<6;++j){
		int num=(j%2==0)?1:-1;
		car[j][0]+=num;
		car[j][1]+=num;
		if(j%2==0){
			if(car[j][1]>15){
				car[j][0]=0;
				car[j][1]=-2;
			}
		}
		else{
			if(car[j][1]<0){
				car[j][0]=15;
				car[j][1]=17;
			}
		}
	}
}

void updateMap(){
	int i,j;
    if(error!=1)
        updateCar();
	if(error==1){
		printError();
		return;
	}
	for(j=0;j<16;++j){
		for(i=0;i<16;++i){
			map[j][i]=0;
		}
	}
	for(j=0;j<6;++j){
		for(i=0;i<3;++i){
			if(j%2==0){
				if(car[j][0]-i<=15){
					map[2+2*j][car[j][0]-i]=1;
					if(player[1]==2+2*j && player[0]==car[j][0]-i)
						error=1;
				}
			}
			else{
				if(car[j][0]+i>=0){
					map[2+2*j][car[j][0]+i]=1;
					if(player[1]==2+2*j && player[0]==car[j][0]+i)
						error=1;
				}
			}
		}
			
	}
	map[player[1]][player[0]]=1;
}

void updatePlayer(){
    map[player[1]][player[0]]=1;
}

void initMap(){
	int i,j;
    error=0;
    player[1]=15;
    player[0]=4;
	srand(time(NULL));
    for(j=0;j<16;++j)
        for(i=0;i<16;++i)
            map[j][i]=0;
	map[player[1]][player[0]]=1;
	for(j=0;j<6;++j){
		int num=(j%2==0)?1:-1;
		car[j][0]=rand()%12+2;
		car[j][1]=car[j][0]+num*2;
		for(i=0;i<3;++i){
			map[2+j*2][car[j][0]+num*i]=1;
			
		}
	}
}

void move(int direct){
    map[player[1]][player[0]]=0;
	switch(direct){
		case 0:
			player[1]-=1;
			break;
		case 1:
			player[1]+=1;
			break;
		case 2:
			player[0]-=1;
			break;
		default:
			player[0]+=1;
			break;
	}
    map[player[1]][player[0]]=1;
    int i,j;
    for(j=0;j<6;++j){
        for(i=0;i<3;++i){
            if(j%2==0){
				if(car[j][0]-i<=15){
					map[2+2*j][car[j][0]-i]=1;
					if(player[1]==2+2*j && player[0]==car[j][0]-i)
						error=1;
				}
			}
			else{
				if(car[j][0]+i>=0){
					map[2+2*j][car[j][0]+i]=1;
					if(player[1]==2+2*j && player[0]==car[j][0]+i)
						error=1;
				}
			}
        }
    }

}
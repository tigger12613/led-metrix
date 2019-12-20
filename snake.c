#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct body{
	int x;
	int y;
	struct body *next;
	struct body *before;
}body;

typedef struct snake{
	int length;
	struct body *head;
	struct body *end;
}snake;

snake player;
int way=1;
int point[2];
int status=1;

void delay(unsigned int secs) 
{
 unsigned int retTime = time(0) + secs;   
 while (time(0) < retTime);               
}

int map[8][8]={
	{1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1},
};

void resetMap(){
	int i,j;
	int tmp_map[8][8]={
		{1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1},
	};
	for (i=0;i<8;++i)
		for(j=0;j<8;++j)
			map[i][j]=tmp_map[i][j];
}

void printMap(){
	int i,j;
	map[point[1]][point[0]]=3;
	for (i=0;i<8;++i){
		for(j=0;j<8;++j){
			printf("%d",map[i][j]);
		}
		printf("\n");
	}
}

void printError(){
	system("cls");
	int tmp_map[8][8]={
		{1,0,0,0,0,0,0,1},
		{0,1,0,0,0,0,1,0},
		{0,0,1,0,0,1,0,0},
		{0,0,0,1,1,0,0,0},
		{0,0,0,1,1,0,0,0},
		{0,0,1,0,0,1,0,0},
		{0,1,0,0,0,0,1,0},
		{1,0,0,0,0,0,0,1},
	};
	int i,j;
	for (i=0;i<8;++i){
		for(j=0;j<8;++j){
			printf("%d",tmp_map[i][j]);
		}
		printf("\n");
	}
}

body* createBody(int x,int y,struct body* before){
    body *tmp=(body*)malloc(sizeof(body));
	tmp->x=x;
	tmp->y=y;
	tmp->next=NULL;
	tmp->before=before;
	return tmp;
}

int checkSnake(int x, int y){
	int i;
	body *tmp=player.head;
	printf("check %d %d",x,y);
	for(i=0;i<player.length;++i){
		if(x==tmp->x && y==tmp->y)
			return 0;
		else{
			tmp=tmp->next;
		}
	}
	return 1;
}



void setPoint(){
	point[0]=(rand()%6)+1;
	point[1]=(rand()%6)+1;
}

void initSnake(int x, int y){
	player.length=2;
	body *tmp1=createBody(3,3,NULL);
	player.head=tmp1;
	body *tmp2=createBody(3,2,tmp1);
	tmp1->next=tmp2;
	player.end=tmp2;
}

void updateSnake(){
	int i;
	body *tmp=player.head;
	for(i=0;i<player.length;++i){
		if(point[0]==tmp->x && tmp->y==point[1]){
			setPoint();
			tmp=player.head;
			i=0;
		}
		else{
			map[tmp->y][tmp->x]=2;
			tmp=tmp->next;
		}

	}
}




int checkStatus(int x, int y){
	printf("Let's check %d,%d with %d %d\n",x,y,point[1],point[0]);
	if(y==point[1]&&x==point[0]){
		setPoint();
		return 2;
	}
	else if(map[y][x]==1||checkSnake(x,y)==0){
		return 0;
	}	
	else
		return 1; 
}

void move(int direct,body *target){ //0 up, 1 down, 2 left, 3 right
	int i;
	body *tmp=target->next;
	if(tmp!=NULL){
		if(target->x==(tmp->x)&&target->y==(tmp->y-1)){
			move(0,target->next);
		}
		else if(target->x==tmp->x&&target->y==tmp->y+1){
			move(1,target->next);
		}
		else if(target->x==tmp->x-1&&target->y==tmp->y){
			move(2,target->next);
		}
		else if(target->x==tmp->x+1&&target->y==tmp->y){
			move(3,target->next);
		}
	}
	else{
		int x_tmp=0,y_tmp=0;
		switch (way){
			case 0:
				y_tmp=-1;
				break;
			case 1:
				y_tmp=1;
				break;
			case 2:
				x_tmp=-1;
				break;
			case 3:
				x_tmp=1;
				break;
		}
		int check=checkStatus(player.head->x+x_tmp,player.head->y+y_tmp);
		printf("ccheck is %d\n",check); 
		if(check==2){
			body *next=createBody(target->x,target->y,NULL);
			player.length++;
			target->next=next;
			player.end=next;
		}
		else if(check==0){
			printError();
			status=0;
		}		
	}
	switch (direct){
		case 0:
			target->y=target->y-1;
			break;
		case 1:
			target->y=target->y+1;
			break;
		case 2:
			target->x-=1;
			break;
		case 3:
			target->x=target->x+1;
			break;
	}
	return;
}

int main(){
	srand(time(NULL));
	initSnake(0,0);
	setPoint();
	while(status){
		system("cls");
		updateSnake();
		printMap();
		resetMap();
		printf("輸入下個指令 WASD \n");
		char input;
		scanf("%c",&input);
		switch(input){
			case 'W':
				if(way!=1){
					way=0;
					move(0,player.head);
					
				}
				else
					move(way,player.head);
				break;
			case 'A':
				if(way!=3){
					way=2;
					move(2,player.head);
					
				}
				else
					move(way,player.head);
				break;
			case 'S':
				if(way!=0){
					way=1;
					move(1,player.head);
					
				}
				else
					move(way,player.head);
				break;
			case 'D':
				if(way!=2){
					way=3;
					move(3,player.head);
				}
				else
					move(way,player.head);
				break;	
		}
	}
	//delay(5);
	
	
	//printf("55555 \n");
	return 0;
} 

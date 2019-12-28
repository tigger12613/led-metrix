/* 
 * File:   ball.h
 * Author: MSI
 *
 * Created on 2019年12月28日, 下午 2:35
 */

#ifndef BALL_H
#define	BALL_H
#include<stdlib.h>
#include<time.h>
#include<xc.h>
unsigned char LED[16][16] = {0};
int left_board[16] = {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0};
int right_board[16] = {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0};
int ball_x=4;
int ball_y=6;
int ball_last_x=3;
int ball_last_y=5;

void initial(void);
void board(unsigned char left_up,unsigned char left_down,unsigned char right_up,unsigned char right_down);
void ball(void);
void move_ball(void);
void Delay(unsigned int secs);

#endif	/* BALL_H */
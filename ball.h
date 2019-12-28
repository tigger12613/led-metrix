/* 
 * File:   ball.h
 * Author: MSI
 *
 * Created on 2019年12月28日, 下午 2:35
 */

#ifndef BALL_H
#define	BALL_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<xc.h>
unsigned char LED[16][16] = {0};
int left_board[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int right_board[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int ball_x=4;
int ball_y=6;
int ball_last_x=3;
int ball_last_y=5;

void initial(void);
void board(void);
void ball(void);
void move_ball(void);
void Delay(unsigned int secs);

#endif	/* BALL_H */
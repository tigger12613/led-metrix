/* 
 * File:   snake.h
 * Author: Jia An
 *
 * Created on 2019?12?28?, ?? 2:35
 */

#ifndef SNAKE_H
#define	SNAKE_H

#ifdef	__cplusplus
extern "C" {
#endif

unsigned char map[16][16];
void printError();
void updateCar();
void updateMap();
void initMap();
void move(int direct);
void updatePlayer();
unsigned char *endSnake;
unsigned char error;

#ifdef	__cplusplus
}
#endif

#endif	/* SNAKE_H */


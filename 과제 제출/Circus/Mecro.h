#pragma once
#include<Windows.h>
#include<stdio.h>
#include<string>
#include<conio.h>
#include <math.h>
#include <time.h>
using namespace std;
#define NOT 20 //Çã°ø°ª?

enum State
{
	NOTHING,
	MENU,
	PLAYING,
	ENG,
	WIN,
};

enum player
{
	STOP,
	MOVE,
	JUMP,
	FINSH,
	DEATH,
	PLAYEREND,
};



enum Obstacle
{
	RING,
	FRONT,
	END,
	MONEY,
};
#pragma once
#include<Windows.h>
#include<stdio.h>
#include<string>
#include<conio.h>
#include<math.h>
#include<time.h>
#include<vector>
//#include "resource.h"
using namespace std;
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPACE,
	NON,
};
enum explosion
{
	BLOCK,
	TANK,
	MISSILE,
};
enum tank
{
	ENERY,
	PLAYER,
};
enum enery
{
	NOMAL,
	BOSS,
};
enum MapState
{
	NOT,
	ICE,
};
enum GameState
{
	MENU,
	STAGE,
	PLAYGAME,
	END,
	DEFEAT,
};
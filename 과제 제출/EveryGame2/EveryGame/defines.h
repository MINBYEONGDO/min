
#pragma once



enum SCENE_INDEX
{
	SCENE_INDEX_TITLE,
	SCENE_INDEX_GAME,
	SCENE_INDEX_FLIGHTGAME,
	SCENE_INDEX_PAPERGAME
};

enum MoveDirection
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	DONMOVE,
};
enum FeverTime
{
	NON,
	NOMAL,
	SUPER,
	ULTRA,//?
};
enum GameState
{
	PLAY,
	STOP,
	TIMEOUT,
};

enum GameType
{
	FLIGHTGAME,
	PAPERGAME,
};
//enum Color
//{
// GREEN,
// BLUE,
// RED,
// YELLOW,
//};

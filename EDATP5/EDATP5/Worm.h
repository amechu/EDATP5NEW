#pragma once
#include "Userdata.h"
#include <string>
#include <array>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "EventHandling.h"	//clase event

enum class WormState
{
	Iddle, Walking, Jumping
};

enum class WormDirection {
	Left, Right
};

typedef struct
{
	double X;
	double Y;
}Point;

class Worm
{
public:
	Worm(const Userdata& Userdata, unsigned int keySet);
	~Worm();
	void moveLeft(bool startorstop);
	void moveRight(bool startorstop);
	void Jump(const Userdata& Userdata);
	void Draw(const Userdata& Userdata);
	void Refresh(const Userdata& Userdata);
	void clearTickCount();
	void setState(WormState state);
	void setDirection(WormDirection direction);
	void setPosition(int x, int y);
private:
	Point Position;
	WormState State = WormState::Iddle;
	WormDirection Direction = WormDirection::Left;
	unsigned int tickCount;
	unsigned int jumpKey;
	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	double velocity_x;
	double velocity_y;
	const double Velocity = 4.5;
	const double Gravity = 0.24;
	unsigned int timerTick;
	unsigned int nro_foto_move;
	Event lastEvent;
};




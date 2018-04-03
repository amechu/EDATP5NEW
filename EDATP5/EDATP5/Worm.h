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
	Iddle, Walking, Jumping, WaitingToWalk, ReconfirmWalk
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
	void moveLeft(bool startorstop, const Userdata& Userdata);
	void moveRight(bool startorstop, const Userdata& Userdata);
	void Jump(const Userdata& Userdata);
	void Draw(const Userdata& Userdata);
	void Refresh(const Userdata& Userdata);
	void clearTickCount();
	void setState(WormState state);
	void setDirection(WormDirection direction);
	void setPosition(int x, int y);
	void setKeyPressed(WormDirection dir, bool booli);
private:
	Point Position;
	WormState State = WormState::Iddle;
	WormDirection Direction = WormDirection::Left;
	bool keyPressedLeft;
	bool keyPressedRight;
	unsigned int ReconfirmCounter;
	unsigned int tickCount;
	unsigned int jumpKey;
	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	const double Velocity = 4.5;
	const double Gravity = 0.24;
	Event lastEvent;
};




#pragma once
#include "Userdata.h"
#include <string>
#include <array>
#include <stdlib.h>
#include <math.h>
#include "EventHandling.h"	//clase event

#define SIZEPXLS_WORM 27
#define FPS_W 50.0

#define G 0.24
#define G_PER_TICK (G/FPS_W)
#define VEL_JUMP 4.5
#define M_PI 3.14159265359


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
	void Jump();
	void Draw(const Userdata& Userdata);
	void Refresh(const Userdata& Userdata);
	void increase_timerTick();
	void clear_timerTick();
	Event get_last_event();
	void set_last_event(Event evento);
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
	double velocity_y;
	double velocity_x;
	unsigned int timerTick;
	unsigned int nro_foto_move;
	Event lastEvent;
};




#pragma once

#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"

#include "Userdata.h"

class Allegro
{
public:
	Allegro();
	~Allegro();
	bool Init(Userdata&);
	void SetBackground();

	ALLEGRO_TIMER* Timer;
	ALLEGRO_EVENT_QUEUE* Queue;
	ALLEGRO_BITMAP *Background;
	ALLEGRO_DISPLAY* Display;

	const float FPS = 50.0;
	const float SCREEN_W = 1920;
	const float SCREEN_H = 696;
};


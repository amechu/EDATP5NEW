#pragma once

#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Userdata.h"

#define BACKGROUND_MUSIC "Super Mario Bros Soundtrack.wav"
#define JUMP_MUSIC "Super Mario Bros - Jump Sound Effect.wav"

class Allegro
{
public:
	Allegro();
	~Allegro();
	bool Init(Userdata&);

	ALLEGRO_TIMER* Timer;
	ALLEGRO_EVENT_QUEUE* Queue;
	ALLEGRO_DISPLAY* Display;
	ALLEGRO_SAMPLE * music;

	const float FPS = 50.0;
	const float SCREEN_W = 1920;
	const float SCREEN_H = 696;

	void loadPlayMusic();
	void stopMusic();

};


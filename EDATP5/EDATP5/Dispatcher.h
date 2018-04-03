#pragma once

#include "EventHandling.h" //Event type
#include "Userdata.h" //Data usage
#include "Scene.h"

class Dispatcher
{
public:
	Dispatcher();
	~Dispatcher();
	void Dispatch(Event Event, Scene& Scene, Userdata& Userdata);
	bool key_left2_held;
	bool key_left1_held;
	bool key_right1_held;
	bool key_right2_held;
private:
	//bool key_left2_held;
};


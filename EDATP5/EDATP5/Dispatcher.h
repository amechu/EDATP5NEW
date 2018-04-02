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
};


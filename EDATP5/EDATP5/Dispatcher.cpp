#include "Dispatcher.h"

Dispatcher::Dispatcher()
{
}


Dispatcher::~Dispatcher()
{
}

void Dispatcher::Dispatch(Event Event, Scene& Scene, Userdata& Userdata) {
	switch (Event) {
		case Event::Jump1: {
			(Scene.Worm1)->Jump();
			break;
		}
		case Event::moveLeft1: {
			Scene.Worm1->moveLeft();
			break;
		}
		case Event::moveRight1: {
			Scene.Worm1->moveRight();
			break;
		}
		case Event::Jump2: {
			Scene.Worm2->Jump();
			break;
		}
		case Event::moveLeft2: {
			Scene.Worm2->moveLeft();
			break;
		}
		case Event::moveRight2: {
			Scene.Worm2->moveRight();
			break;
		}
		case Event::Refresh: {
			Scene.Refresh();
			break;
		}
	}
}

#include "Dispatcher.h"

Dispatcher::Dispatcher()
{
}


Dispatcher::~Dispatcher()
{
}

void Dispatcher::Dispatch(Event Event, Scene& Scene, Userdata& Userdata, Allegro& Allegro) {
	switch (Event) {
		case Event::Jump1: {
			(Scene.Worm1)->Jump();
			break;
		}
		case Event::moveLeft1: {
			Scene.Worm1->moveLeft(true);
			break;
		}
		case Event::moveLeft1Stop: {
			Scene.Worm1->moveLeft(false);
			break;
		}
		case Event::moveRight1: {
			Scene.Worm1->moveRight(true);
			break;
		}
		case Event::moveRight1Stop: {
			Scene.Worm1->moveRight(false);
			break;
		}
		case Event::Jump2: {
			Scene.Worm2->Jump();
			break;
		}
		case Event::moveLeft2: {
			Scene.Worm2->moveLeft(true);
			break;
		}
		case Event::moveLeft2Stop: {
			Scene.Worm2->moveLeft(false);
			break;
		}
		case Event::moveRight2: {
			Scene.Worm2->moveRight(true);
			break;
		}
		case Event::moveRight2Stop: {
			Scene.Worm2->moveRight(false);
			break;
		}
		case Event::Refresh: {
			Scene.Refresh(Userdata);
			break;
		}
	}
}

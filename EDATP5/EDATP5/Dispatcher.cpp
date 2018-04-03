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
			(Scene.Worm1)->Jump(Userdata);
			break;
		}
		case Event::moveLeft1: {

			Scene.Worm1->moveLeft(true, Userdata);
			key_left1_held = true;

			break;
		}
		case Event::moveLeft1Stop: {
			Scene.Worm1->moveLeft(false, Userdata);
			key_left1_held = false;
			break;
		}
		case Event::moveRight1: {

			Scene.Worm1->moveRight(true, Userdata);
			key_right1_held = true;

			break;
		}
		case Event::moveRight1Stop: {
			Scene.Worm1->moveRight(false, Userdata);
			key_right1_held = false;
			break;
		}
		case Event::Jump2: {
			Scene.Worm2->Jump(Userdata);
			break;
		}
		case Event::moveLeft2: {

			Scene.Worm2->moveLeft(true, Userdata);
			key_left2_held = true;

			break;
		}
		case Event::moveLeft2Stop: {
			Scene.Worm2->moveLeft(false, Userdata);
			key_left2_held = false;
			break;
		}
		case Event::moveRight2: {

			Scene.Worm2->moveRight(true, Userdata);
			key_right2_held = true;

			break;
		}
		case Event::moveRight2Stop: {
			Scene.Worm2->moveRight(false, Userdata);
			key_right2_held = false;
			break;
		}
		case Event::Refresh: {
			Scene.Refresh(Userdata);
			break;
		}
	}
}

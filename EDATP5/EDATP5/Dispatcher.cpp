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

			Scene.Worm1->moveLeft(true);
			key_left1_held = true;

			break;
		}
		case Event::moveLeft1Stop: {
			Scene.Worm1->moveLeft(false);
			key_left1_held = false;
			break;
		}
		case Event::moveRight1: {

			Scene.Worm1->moveRight(true);
			key_right1_held = true;

			break;
		}
		case Event::moveRight1Stop: {
			Scene.Worm1->moveRight(false);
			key_right1_held = false;
			break;
		}
		case Event::Jump2: {
			Scene.Worm2->Jump(Userdata);
			break;
		}
		case Event::moveLeft2: {

			Scene.Worm2->moveLeft(true);
			key_left2_held = true;

			break;
		}
		case Event::moveLeft2Stop: {
			Scene.Worm2->moveLeft(false);
			key_left2_held = false;
			break;
		}
		case Event::moveRight2: {

			Scene.Worm2->moveRight(true);
			key_right2_held = true;

			break;
		}
		case Event::moveRight2Stop: {
			Scene.Worm2->moveRight(false);
			key_right2_held = false;
			break;
		}
		case Event::Refresh: {
			if (key_left2_held)
			{
				Scene.Worm2->moveLeft(true);
			}
			if (key_left1_held)
			{
				Scene.Worm1->moveLeft(true);
			}
			if (key_right2_held)
			{
				Scene.Worm2->moveRight(true);
			}
			if (key_right1_held)
			{
				Scene.Worm1->moveRight(true);
			}
			Scene.Refresh(Userdata);
			break;
		}
	}
}

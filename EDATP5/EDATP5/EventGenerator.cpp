#include "EventGenerator.h"


EventGenerator::EventGenerator()
{
}


EventGenerator::~EventGenerator()
{
}


Event EventGenerator::fetchEvent(ALLEGRO_EVENT_QUEUE* Queue, Userdata& Userdata) {
	
	ALLEGRO_EVENT allegroEvent;
	Event Event = Event::noEvent;

	if (al_get_next_event(Queue, &allegroEvent)) {

		if (allegroEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			Event = Event::Quit;

		else if (allegroEvent.type == ALLEGRO_EVENT_TIMER)
			Event = Event::Refresh;

		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (allegroEvent.keyboard.keycode == Userdata.worm1KeySet[Jump])
				Event = Event::Jump1;
			else if (allegroEvent.keyboard.keycode == Userdata.worm1KeySet[Left])
				Event = Event::moveLeft1;
			else if (allegroEvent.keyboard.keycode == Userdata.worm1KeySet[Right])
				Event = Event::moveRight1;
			else if (allegroEvent.keyboard.keycode == Userdata.worm2KeySet[Jump])
				Event = Event::Jump2;
			else if (allegroEvent.keyboard.keycode == Userdata.worm2KeySet[Left])
				Event = Event::moveLeft2;
			else if (allegroEvent.keyboard.keycode == Userdata.worm2KeySet[Right])
				Event = Event::moveRight2;
		}
		
		else if (allegroEvent.type == ALLEGRO_EVENT_KEY_UP) {
			if (allegroEvent.keyboard.keycode == Userdata.worm1KeySet[Left])
				Event = Event::moveLeft1Stop;
			else if (allegroEvent.keyboard.keycode == Userdata.worm1KeySet[Right])
				Event = Event::moveRight1Stop;
			else if (allegroEvent.keyboard.keycode == Userdata.worm2KeySet[Left])
				Event = Event::moveLeft2Stop;
			else if (allegroEvent.keyboard.keycode == Userdata.worm2KeySet[Right])
				Event = Event::moveRight2Stop;
		}
	}
	else
		Event = Event::noEvent;

	return Event;
}
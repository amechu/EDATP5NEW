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
			if (Scene.Worm1->get_last_event != Event::moveLeft1)
				Scene.Worm1->clear_timerTick();		//Si mi evento anterior nofue un move left, tendre que poner el timer en 0, ya que se trata de una nueva fase
			Scene.Worm1->moveLeft(true);
			Scene.Worm1->set_last_event(Event::moveLeft1);
			break;
		}
		case Event::moveLeft1Stop: {
			Scene.Worm1->moveLeft(false);
			break;
		}
		case Event::moveRight1: {
			if (Scene.Worm1->get_last_event != Event::moveRight1)
				Scene.Worm1->clear_timerTick();
			Scene.Worm1->moveRight(true);
			Scene.Worm1->set_last_event(Event::moveRight1);
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
			if (Scene.Worm2->get_last_event != Event::moveLeft2)
				Scene.Worm2->clear_timerTick();
			Scene.Worm2->moveLeft(true);
			Scene.Worm2->set_last_event(Event::moveLeft2);
			break;
		}
		case Event::moveLeft2Stop: {
			Scene.Worm2->moveLeft(false);
			break;
		}
		case Event::moveRight2: {
			if (Scene.Worm2->get_last_event != Event::moveRight2)
				Scene.Worm2->clear_timerTick();
			Scene.Worm2->moveRight();
			Scene.Worm2->set_last_event(Event::moveRight2);
			break;
		}
		case Event::moveRight2: {
			Scene.Worm2->moveRight(false);
			break;
		}
		case Event::Refresh: {
			Scene.Refresh();
			Scene.Worm1->increase_timerTick();	//incremento los tickers por cada refresh para poder moverme
			Scene.Worm2->increase_timerTick();
			break;
		}
	}
}

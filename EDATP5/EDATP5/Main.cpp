#include "EventGenerator.h"
#include "EventHandling.h"
#include "Allegroclass.h"
#include "Dispatcher.h"
#include "Userdata.h"
#include "Scene.h"

#include <iostream>

void GameInit(Userdata&, Scene&);

int main(void) {

	EventGenerator EventGenerator;
	Event Event = Event::noEvent;
	Dispatcher Dispatcher;
	Dispatcher.key_left2_held = false;
	Dispatcher.key_left1_held = false;
	Dispatcher.key_right2_held = false;
	Dispatcher.key_right1_held = false;
	Userdata Userdata;
	Allegro Allegro;
	Scene Scene;

	if (Allegro.Init(Userdata)) {

		GameInit(Userdata, Scene);

		while (Event != Event::Quit) {

			Event = EventGenerator.fetchEvent(Allegro.Queue, Userdata); //C++ reference

			if (Event != Event::noEvent) {

				Dispatcher.Dispatch(Event, Scene, Userdata); //C++ reference
			}
		}
	}
	else
		std::cout << "Resources not loaded properly." << std::endl;

	return EXIT_SUCCESS;
}

void GameInit(Userdata& Userdata, Scene& Scene) {
	Userdata.LoadWormImages();
	Scene.LoadWorm1(Userdata, 1); //Worm inicializado con keyset 1
	Scene.LoadWorm2(Userdata, 2); //Worm inicializado con keyset 2
	Scene.Worm1->setState(WormState::Iddle);
	Scene.Worm2->setState(WormState::Iddle);
	Scene.Worm1->setDirection(WormDirection::Right);
	Scene.Worm2->setDirection(WormDirection::Left);
	Scene.Worm1->setPosition(Userdata.LeftWall, Userdata.GroundLevel);
	Scene.Worm2->setPosition(Userdata.RightWall, Userdata.GroundLevel);
	Scene.Worm1->clearTickCount();
	Scene.Worm2->clearTickCount();
}
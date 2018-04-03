#include "EventGenerator.h"
#include "EventHandling.h"
#include "Allegroclass.h"
#include "Dispatcher.h"
#include "Userdata.h"
#include "Scene.h"

#include <iostream>

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

		//ESTO SE PODRIA CONDENSAR EN UNA FUNCION DEFINIDA EN MAIN QUE SE LLAME GAMEINIT//
		Userdata.LoadWormImages();
		Scene.LoadWorm1(Userdata, 1); //Worm inicializado con keyset 1
		Scene.LoadWorm2(Userdata, 2); //Worm inicializado con keyset 2
		Scene.Worm1->clear_timerTick();
		Scene.Worm2->clear_timerTick();
		Scene.Worm1->setState(WormState::Iddle);
		Scene.Worm2->setState(WormState::Iddle);
		Scene.Worm1->setDirection(WormDirection::Right);
		Scene.Worm2->setDirection(WormDirection::Left);
		Scene.Worm1->setPosition(Userdata.LeftWall + 200 , Userdata.GroundLevel);
		Scene.Worm2->setPosition(Userdata.RightWall , Userdata.GroundLevel);
		
		//////////////////////////////////////////////////////////////////////////////////

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
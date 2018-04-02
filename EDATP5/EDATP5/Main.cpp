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
	Userdata Userdata;
	Allegro Allegro;
	Scene Scene;

	if (Allegro.Init(Userdata)) {

		Userdata.LoadWormImages();
		Scene.LoadWorm1(Userdata, 1); //Worm inicializado con keyset 1
		Scene.LoadWorm2(Userdata, 2); //Worm inicializado con keyset 2
		
		Scene.Worm1->Draw(Userdata); //DEBUG

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
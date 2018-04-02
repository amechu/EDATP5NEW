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

				Dispatcher.Dispatch(Event, Scene, Userdata, Allegro); //C++ reference
			}
		}
	}
	else
		std::cout << "Resources not loaded properly." << std::endl;

	return EXIT_SUCCESS;
}














/*int main(void)
{
	startTimer();

	while (!quit)
	{
		if (timer)
		{
			worm1.move();
			worm2.move();
		}

		getTeclas();
		getNetwork();
	}
}

algo no es bloqueante si lo que tarda en realizarse es menor que diez veces lo que tarda en llegar el evento
mas lento.

int main(void)
{
	initialize();

	while (evento != quit)
	{
		evento = getEvent(&userData); //esto puede devolver eventos complejos que pueden ser combinacion de eventos
		if (evento != NO_EVENT)		//de perifericos, o el mismo evento para move del teclado que de network.
		{
			dispatch(evento, &userData); //dispatch va a tener informacion del escenario y cuando entre a dibujar
		}//por tick entonces entra en un for que refreshea(); a cada worm.
	}
}




eventos example
{
	tick
	move
	jump
}

por cada tick que llegue se mueve un tok la lombriz y tiene un contador de ticks y se muebe hasta cieto tick.


x(i) = x(i-1) + vel
y(i) = yo + vel.sen(60).i-1/2g.i^2

y max en vel.sen(60)/g.

class Worm //podria el constructor recibir que teclas hace que, y que con cada tecla que le llegue haga lo que tenga
{	//que hacer. Con esto podemos hacer muchos worms.
private:
	position pos;
	WORM_STATE state; //idle (refresh no da bola), waiting_to_walk(cuando hay keydown pre 100ms), walking(con keydown), end_walking(cuando hay keyup)
	ALLEGRO_BITMAP** walkImgs; //aca usariamos listas si supieramos.
	ALLEGRO_BITMAP** jumpImgs;
	uint tickCount;

public:
	void refresh(void *userData); //conte 5 ticks entonces paso del estado checking_if_walk al estado warm_up_walk y asi.
	void startWalking();
	void stopWalking();

};


***DIVISION***
clase escenario //el dispatcher habla con el escenario y no con los worms. le dice al escenario que actualice todo que dibuja el background y los worms. escenario contiene a los worms y a la informacion del background.
clase worm
main con dispatcher/gen de eventos*/
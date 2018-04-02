#include "Worm.h"
using namespace std;

Worm::Worm(const Userdata& Userdata, unsigned int keySet)
{
	switch (keySet) {
		case 1: {
			this->jumpKey = Userdata.worm1KeySet[0];
			this->moveLeftKey = Userdata.worm1KeySet[1];
			this->moveRightKey = Userdata.worm1KeySet[2];
		}
		case 2: {
			this->jumpKey = Userdata.worm2KeySet[0];
			this->moveLeftKey = Userdata.worm2KeySet[1];
			this->moveRightKey = Userdata.worm2KeySet[2];
		}
	}
}


Worm::~Worm()
{
}


void Worm::moveLeft(bool StartOrStop) {

	if (timerTick < 5)			//Si tan solo tickeo 5 veces, es inferior a 100 ms entonces solo cambia de direccion
	{
		this->Direction = WormDirection::Left;
		nro_foto_move = 1;
	}
	//POr los 3 primeros ticks muestra las primeras fotos, entonces esta todo bien
	else              //Si el ticker es mayor a 5 entonces debe moverse, se mueve lo que se tiene que mover en un segundo dividio los FPS
	{
		if (nro_foto_move > 13)	//Nro foto cambia cuando imprimo un worm
		{
			nro_foto_move = 4; //Indice para imprimir foto
		}
		if (nro_foto_move == 4)	//Solo cambio la posicion cuando se hayan mostrado las trece fotos
		{
			if ((Position.X > 701) && (Position.X < 1212))	//Si esta dentro de los parametros se mueve, sino no hace nada
			{
				this->State = WormState::Walking;
				Position.X -= 9;

			}
		}
	}
}


void Worm::moveRight(bool StartOrStop) {
	
	if (timerTick < 5)			//Si tan solo tickeo 5 veces, es inferior a 100 ms entonces solo cambia de direccion
	{
		this->Direction = WormDirection::Left;
		nro_foto_move = 0;
	}
	else if (timerTick == 7)
	{
		nro_foto_move = 5;
	}
	//POr los 3 primeros ticks muestra las primeras fotos, entonces esta todo bien
	else              //Si el ticker es mayor a 5 entonces debe moverse, se mueve lo que se tiene que mover en un segundo dividio los FPS
	{
		if (nro_foto_move > 13)	//Nro foto cambia cuando imprimo un worm
		{
			nro_foto_move = 4; //Indice para imprimir foto
		}
		if (nro_foto_move == 4)	//Solo cambio la posicion cuando se hayan mostrado las trece fotos
		{
			if ((Position.X > 701) && (Position.X < 1212))	//Si esta dentro de los parametros se mueve, sino no hace nada
			{
				this->State = WormState::Walking;
				Position.X += 9;

			}
		}
	}
}


void Worm::Jump() {
	if (timerTick = 0)
	{
		velocity_y = (VEL_JUMP * sin((60.0 / 180.0)*M_PI)) / FPS_W;	//En el primer instante cambio la velocidad
		velocity_x = (VEL_JUMP * cos((60.0 / 180.0)*M_PI)) / FPS_W;	//Divido por FPS_W asio me queda la velocidad por frame
		this->State = WormState::Jumping;
	}
	else
	{
		if (velocity_y = -(VEL_JUMP * sin((60.0 / 180.0)*M_PI)))	//cuando la velocidad y es igual a -velocidad_y inicial, termino el salto
		{
			velocity_y = 0;
			velocity_x = 0;
			this->State = WormState::Iddle;
			//Terminar salto
		}
		else
		{
			switch (this->Direction)	//el cambio de la posicion x dependera de la direccion del worm
			{
			case (WormDirection::Left):
			{
				Position.X -= velocity_x;
				Position.Y += velocity_y;
				break;
			}
			case(WormDirection::Right):
			{
				Position.X += velocity_x;
				Position.Y += velocity_y;
				break;
			}
			}
			velocity_y -= G_PER_TICK;	//cambio al velocidad cada tick
		}
	}

}


void Worm::Draw(Userdata& Userdata) {

	switch (this->Direction) {
		case WormDirection::Left: {
			switch (this->State) {
				case WormState::Iddle: {
					al_draw_bitmap(Userdata.WormWalk[0], Position.X, Position.Y, NULL); al_flip_display(); break;
				}
				case WormState::Walking: {
					al_draw_bitmap(Userdata.WormWalk[nro_foto_move++], Position.X, Position.Y, NULL); al_flip_display(); break;
				}
				case WormState::Jumping: {

				}
			}
		}
		case WormDirection::Right: {
			switch (this->State) {
				case WormState::Iddle: {
					al_draw_bitmap(Userdata.WormWalk[0], 701, 616, ALLEGRO_FLIP_HORIZONTAL); break;
				}
				case WormState::Walking: {
					al_draw_bitmap(Userdata.WormWalk[nro_foto_move++], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL); break;
				}
				case WormState::Jumping: {

				}
			}
		}
	}
}

void Worm::Refresh() {

}


void Worm::increase_timerTick()
{
	timerTick++;
}

void Worm::clear_timerTick()
{
	timerTick = 0;
}

Event Worm::get_last_event()
{
	return lastEvent;
}

void Worm::set_last_event(Event evento)
{
	lastEvent = evento;
}
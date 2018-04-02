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
	if ((this->State == WormState::Iddle) || ((this->State == WormState::Walking) && (this->Direction == WormDirection::Left)))	//Solamente se entra si el worm estaba quieto o si ya se estaba moviendo para la izquierda
	{
		if (!StartOrStop)
		{
			if ((tickCount < 5)&&(this->State == WormState::Iddle))	//Si levanto y el ticker es menor a 5 entonces solo le cambio la direccion y lo dejo en idle
			{
				
				this->Direction = WormDirection::Left;
				this->State = WormState::Iddle;
			}
			else if (((tickCount <5) || (tickCount > 45))&&(this->State == WormState::Walking))	//Si me levantan la tecla entre los 900ms y los 1100ms entonces hago un ciclo e walking
			{
				this->State = WormState::Walking;
				tickCount = 8; //Si tengo que seguir caminando me salteo el tiempo de warmup
			}
			else if((tickCount>5)&&(tickCount<50)) //Si tick count es mayor a 5 cuando se suelta la tecla camino
			{
				this->State = WormState::Walking;
			}
			else
			{
				this->State == WormState::Iddle;
			}
		}
		if ((tickCount>5)&&(tickCount<50))
		{
			this->State == WormState::Walking;
		}
		
		if ((tickCount < 5) && (this->State == WormState::Iddle))			//Si tan solo tickeo 5 veces, es inferior a 100 ms entonces solo cambia de direccion
		{
			this->Direction = WormDirection::Left;	//SI esta idle entonces es la primera vez que empiezo a moverme, espero hasta que pasen los primeros ticks y despues sigo
			
			
		}
		if (this->State == WormState::Walking)
		{
			if (tickCount < 50 /*|| ((tickCount == 8) && (this->State == WormState::Walking))*/)	//Si es el primer ciclo, o si termino el primer ciclo, pero sigo levantando
			{
				if (((timerTick - 8) % 14) == 0)	//Cambio la posicion cuando el timer tick sea multiplo de 14

				{
					if ((Position.X > 701) && (Position.X < 1212))	//Si esta dentro de los parametros se mueve, sino no hace nada
					{
						
						Position.X -= 9;

					}
				}
			}
			else
			{
				tickCount = 0;

			}
		}
		tickCount++;

	}
}


void Worm::moveRight(bool StartOrStop) {
	if ((this->State == WormState::Iddle) || ((this->State == WormState::Walking) && (this->Direction == WormDirection::Right)))
	{
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
}


void Worm::Jump() {
	if ((this->State == WormState::Iddle) || (this->State == WormState::Jumping))
	{
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

}


void Worm::Draw(const Userdata& Userdata) {

	switch (this->Direction) {
		case WormDirection::Left: {
			switch (this->State) {
				case WormState::Iddle: {
					al_draw_bitmap(Userdata.WormWalk[0], Position.X, Position.Y, NULL); break;
				}
				case WormState::Walking: {
					if (this->tickCount <= 5)
						al_draw_bitmap(Userdata.WormWalk[0], Position.X, Position.Y, NULL);
					else if (this->tickCount <= 8)
						al_draw_bitmap(Userdata.WormWalk[tickCount-6], Position.X, Position.Y, NULL);
					else if (this->tickCount <= 50) {
						if(this->tickCount <= 16)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 6], Position.X, Position.Y, NULL);
						else if(this->tickCount <= 21)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 7], Position.X, Position.Y, NULL);
						else if (this->tickCount == 22)
							al_draw_bitmap(Userdata.WormWalk[3], Position.X, Position.Y, NULL);
						else if(this->tickCount <=30)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 20], Position.X, Position.Y, NULL);
						else if(this->tickCount <=35)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 21], Position.X, Position.Y, NULL);
						else if (this->tickCount == 36)
							al_draw_bitmap(Userdata.WormWalk[3], Position.X, Position.Y, NULL);
						else if(this->tickCount <= 44)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 34], Position.X, Position.Y, NULL);
						else if(this->tickCount <= 49)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 35], Position.X, Position.Y, NULL);
						else if (this->tickCount == 50)
							al_draw_bitmap(Userdata.WormWalk[3], Position.X, Position.Y, NULL);
					}
					break;
				}
				case WormState::Jumping: {
					if (tickCount <= 2)
						al_draw_bitmap(Userdata.WormJump[tickCount], Position.X, Position.Y, NULL);
					else if (tickCount <= 26)
						al_draw_bitmap(Userdata.WormJump[3], Position.X, Position.Y, NULL);
					else if (tickCount <= 33)
						al_draw_bitmap(Userdata.WormJump[tickCount - 22], Position.X, Position.Y, NULL);
					break;
				}
			}
			break;
		}
		case WormDirection::Right: {
			switch (this->State) {
				case WormState::Iddle: {
					al_draw_bitmap(Userdata.WormWalk[0], 701, 616, ALLEGRO_FLIP_HORIZONTAL); break;
				}
				case WormState::Walking: {
					if (this->tickCount <= 5) {
						al_draw_bitmap(Userdata.WormWalk[0], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						al_flip_display();
					}
					else if (this->tickCount <= 8) {
						al_draw_bitmap(Userdata.WormWalk[tickCount - 6], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						al_flip_display();
					}
					else if (this->tickCount <= 50) {
						if (this->tickCount <= 16)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 5], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount <= 21)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 6], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount == 22)
							al_draw_bitmap(Userdata.WormWalk[3], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount <= 30)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 19], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount <= 35)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 20], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount == 36)
							al_draw_bitmap(Userdata.WormWalk[3], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount <= 44)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 33], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount <= 49)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 34], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount == 50)
							al_draw_bitmap(Userdata.WormWalk[3], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
					}
					break;
				}
				case WormState::Jumping: {
					if (tickCount <= 2)
						al_draw_bitmap(Userdata.WormJump[tickCount], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
					else if (tickCount <= 26)
						al_draw_bitmap(Userdata.WormJump[3], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
					else if (tickCount <= 33)
						al_draw_bitmap(Userdata.WormJump[tickCount - 22], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
					break;
				}
			}
		}
	}
}

void Worm::Refresh(const Userdata& Userdata) {
	switch (this->State)
	{
		case (WormState::Iddle):
		{
			this->Draw(Userdata);
			break;
		}
		case (WormState::Walking):
		{
			if (this->Direction == WormDirection::Left)
			{
				moveLeft(true);
			}
			else {
				moveRight(true);
			}
			break;
		}
		case (WormState::Jumping):
		{
			Jump();
			break;
		}


	}
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
void Worm::setState(WormState state) {
	this->State = state;
}
void Worm::setDirection(WormDirection direction) {
	this->Direction = direction;
}
void Worm::setPosition(int x, int y) {
	this->Position.X = x;
	this->Position.Y = y;
}
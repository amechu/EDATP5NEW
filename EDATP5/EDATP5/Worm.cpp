#include "Worm.h"
using namespace std;

//test

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
	if (tickCount < 5 && (this->State == WormState::Walking))	//En caso de que se mantenga la tecla, me salteo el warmup
	{
	tickCount = 8;
	}
	if (this->State == WormState::Walking)
	{
	if (tickCount < 50 && tickCount>7 /*|| ((tickCount == 8) && (this->State == WormState::Walking))*/)	//Si es el primer ciclo, o si termino el primer ciclo, pero sigo levantando
	{
	if ((tickCount - 8 != 0) && (((tickCount - 8) % 14) == 0))	//Cambio la posicion cuando el timer tick sea multiplo de 14 me salteo el caso que tickcount igual a 0

	{
	if ((Position.X > 701) && (Position.X < 1212))	//Si esta dentro de los parametros se mueve, sino no hace nada
	{

	Position.X -= 9;

	}
	}
	}
	else if (tickCount<50)
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
		if (!StartOrStop)
		{
			if ((tickCount < 5) && (this->State == WormState::Iddle))	//Si levanto y el ticker es menor a 5 entonces solo le cambio la direccion y lo dejo en idle
			{

				this->Direction = WormDirection::Left;
				this->State = WormState::Iddle;
			}
			else if (((tickCount <5) || (tickCount > 45)) && (this->State == WormState::Walking))	//Si me levantan la tecla entre los 900ms y los 1100ms entonces hago un ciclo e walking
			{
				this->State = WormState::Walking;
				tickCount = 8; //Si tengo que seguir caminando me salteo el tiempo de warmup
			}
			else if ((tickCount>5) && (tickCount<50)) //Si tick count es mayor a 5 cuando se suelta la tecla camino
			{
				this->State = WormState::Walking;
			}
			else
			{
				this->State = WormState::Iddle;
			}
		}
		if ((tickCount>5) && (tickCount<50))
		{
			this->State = WormState::Walking;
		}

		if ((tickCount < 5) && (this->State == WormState::Iddle))			//Si tan solo tickeo 5 veces, es inferior a 100 ms entonces solo cambia de direccion
		{
			this->Direction = WormDirection::Left;	//SI esta idle entonces es la primera vez que empiezo a moverme, espero hasta que pasen los primeros ticks y despues sigo


		}
		if (tickCount < 5 && (this->State == WormState::Walking))	//En caso de que se mantenga la tecla, me salteo el warmup
		{
			tickCount = 8;
		}
		if (this->State == WormState::Walking)
		{
			if (tickCount < 50 && tickCount>7 /*|| ((tickCount == 8) && (this->State == WormState::Walking))*/)	//Si es el primer ciclo, o si termino el primer ciclo, pero sigo levantando
			{
				if ((tickCount - 8 != 0) && (((tickCount - 8) % 14) == 0))	//Cambio la posicion cuando el timer tick sea multiplo de 14 me salteo el caso que tickcount igual a 0

				{
					if ((Position.X > 701) && (Position.X < 1212))	//Si esta dentro de los parametros se mueve, sino no hace nada
					{

						Position.X += 9;

					}
				}
			}
			else if (tickCount<50)
			{
				tickCount = 0;

			}
		}
		tickCount++;

	}
}

void Worm::Jump(const Userdata& Userdata) {
	
	double Linear;
	double Cuadratic;

	if (this->State == WormState::Iddle || this->State == WormState::Jumping) {

		if (this->State == WormState::Iddle)
			this->State = WormState::Jumping;

		this->tickCount++;
		if (this->Direction == WormDirection::Left) {

			if (this->tickCount <= 32) {
				if (Position.X > Userdata.LeftWall + (this->Velocity * cos(M_PI / 3))) {
					this->Position.X -= (this->Velocity * cos(M_PI / 3));
				}
				Linear = this->Velocity * sin(M_PI / 3) * tickCount;
				Cuadratic = (((this->Gravity) / 2) * tickCount * tickCount);
				this->Position.Y = Userdata.GroundLevel - Linear + Cuadratic;
			}
			else {
				this->tickCount = 0;
				this->State = WormState::Iddle;
			}
		}
		else if (this->Direction == WormDirection::Right) {

			if (this->tickCount <= 32) {
				if (Position.X < Userdata.RightWall - (this->Velocity * cos(M_PI / 3))) {
					this->Position.X += (this->Velocity * cos(M_PI / 3));
				}
				Linear = this->Velocity * sin(M_PI / 3) * tickCount;
				Cuadratic = (((this->Gravity) / 2) * tickCount * tickCount);
				this->Position.Y = Userdata.GroundLevel - Linear + Cuadratic;
			}
			else {
				this->tickCount = 0;
				this->State = WormState::Iddle;
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
					else if (tickCount <= 32)
						al_draw_bitmap(Userdata.WormJump[tickCount - 23], Position.X, Position.Y, NULL);
					break;
				}
			}
			break;
		}
		case WormDirection::Right: {
			switch (this->State) {
				case WormState::Iddle: {
					al_draw_bitmap(Userdata.WormWalk[0], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL); break;
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
						al_draw_bitmap(Userdata.WormJump[tickCount-1], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
					else if (tickCount <= 25)
						al_draw_bitmap(Userdata.WormJump[2], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
					else if (tickCount <= 32)
						al_draw_bitmap(Userdata.WormJump[tickCount - 23], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
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
			switch (this->Direction) {
				case WormDirection::Left: {
					moveLeft(true);
					break;
				}
				case WormDirection::Right: {
					moveRight(true);
					break;
				}
			}
			break;
		}
		case (WormState::Jumping):
		{
			Jump(Userdata);
			break;
		}


	}
}

void Worm::clearTickCount()
{
	this->tickCount = 0;
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

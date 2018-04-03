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
	tickCount = 0;
}


Worm::~Worm()
{
}


void Worm::moveLeft(bool StartOrStop, const Userdata& Userdata) {

	this->tickCount++; //Cada vez que entro, aumento tick counter.

	switch (this->State) //Maquina de estados
	{
		case WormState::Iddle: //Si estoy parado:
		{
			switch (StartOrStop) //Dependiendo de si me piden comenzar a mover o parar de mover.
			{
				case true: //Comienzo fase de confirmacion
					this->State = WormState::WaitingToWalk;
					this->Direction = WormDirection::Left; //Cambio de direccion
					break;
				case false://Vuelvo a iddle y reseteo counter/
					this->State = WormState::Iddle;
					this->Direction = WormDirection::Left; //Cambio de direccion
					this->tickCount = 0;
					break;
			}
			break;
		}
		case WormState::WaitingToWalk: //Si estoy en la fase de confirmacion:
		{
			if (this->tickCount <= 5) //Si aun no termino:
			{
				switch (StartOrStop)
				{
					case true:
					{
						break; //Si no tengo que parar, espero
					}
					case false:
					{
						this->State = WormState::Iddle; //Si tengo que parar, vuelvo a estar parado.
						this->tickCount = 0;
						break;
					}
				}
			}
			else if (this->tickCount > 5) //Si ya termino la fase de confirmacion:
			{
				switch (StartOrStop)
				{
					case true:
					{
						this->State = WormState::Walking; //Paso a caminar
						break;
					}
					case false:
					{
						this->State = WormState::Walking; //Paso a caminar
						break;
					}
				}
			}
			break;
		}
		case WormState::Walking: //Si estoy caminando:
		{
			if (this->tickCount <= 43) //Y aun no llegue a la fase de reconfirmacion
			{
				switch (StartOrStop)
				{
					case true:
					{
						if (this->tickCount == 22 || this->tickCount == 36) //Me fijo si tengo que aumentar posicion
							if (this->Position.X >= Userdata.LeftWall + 9)
								this->Position.X -= 9;
						break;
					}
					case false:
					{
						if (this->tickCount == 22 || this->tickCount == 36) //Me fijo si tengo que aumentar posicion
							if (this->Position.X >= Userdata.LeftWall + 9)
								this->Position.X -= 9;
						break;
					}
				}
			}
			else if (this->tickCount > 43) //Si ya paso a la fase de reconfirmacion
			{
				switch (StartOrStop)
				{
					case true:
					{
						this->State = WormState::ReconfirmWalk; //Paso
						break;
					}
					case false:
					{
						this->State = WormState::ReconfirmWalk; //Paso
						break;
					}
				}
			}
			break;
		}
		case WormState::ReconfirmWalk: //Si estoy en la fase de reconfirmacion:
		{
			if (this->tickCount == 45) { //Por las dudas reseteo counter en el primer tick
				this->ReconfirmCounter = 0;
			}

			if (this->keyPressedLeft) { //Si la tecla esta presionada por cada tick, aumento contador.
				this->ReconfirmCounter++;
			}

			if (this->tickCount < 50) { //Si no termine la fase de reconfirmacion, sigo caminando.
				switch (StartOrStop)
				{
					case true:
					{
						break;
					}
					case false:
					{
						break;
					}
				}
			}

			else if (this->tickCount == 50) {		//Si ya termino la fase de confirmacion:
				if (this->ReconfirmCounter == 6) {	//Si tuve la fase de confirmacion entera con la tecla presionada:
					this->State = WormState::Walking;
					this->tickCount = 9;
					this->ReconfirmCounter = 0;	//Paso a la fase de walking pero saltando confirmacion y warmup
					if(this->Position.X >= Userdata.LeftWall + 9) //Y reseteo todo
						this->Position.X -= 9;
				}
				else if (this->ReconfirmCounter < 6) { //Si en algun momento de la reconfirmacion, no estuvo la tecla
					this->State = WormState::Iddle; //presionada, entonces se pedira la fase de confirmacion
					this->tickCount = 0;		//y la fase de warm up de nuevo.
					this->ReconfirmCounter = 0;
					if (this->Position.X >= Userdata.LeftWall + 9)
						this->Position.X -= 9; //Se resetean las cosas.
				}
			}
		}
		break;
	}
}


void Worm::moveRight(bool StartOrStop, const Userdata& Userdata) {
	this->tickCount++; //Cada vez que entro, aumento tick counter.

	switch (this->State) //Maquina de estados
	{
	case WormState::Iddle: //Si estoy parado:
	{
		switch (StartOrStop) //Dependiendo de si me piden comenzar a mover o parar de mover.
		{
		case true: //Comienzo fase de confirmacion
			this->State = WormState::WaitingToWalk;
			this->Direction = WormDirection::Right; //Cambio de direccion
			break;
		case false://Vuelvo a iddle y reseteo counter/
			this->State = WormState::Iddle;
			this->Direction = WormDirection::Right; //Cambio de direccion
			this->tickCount = 0;
			break;
		}
		break;
	}
	case WormState::WaitingToWalk: //Si estoy en la fase de confirmacion:
	{
		if (this->tickCount <= 5) //Si aun no termino:
		{
			switch (StartOrStop)
			{
			case true:
			{
				break; //Si no tengo que parar, espero
			}
			case false:
			{
				this->State = WormState::Iddle; //Si tengo que parar, vuelvo a estar parado.
				this->tickCount = 0;
				break;
			}
			}
		}
		else if (this->tickCount > 5) //Si ya termino la fase de confirmacion:
		{
			switch (StartOrStop)
			{
			case true:
			{
				this->State = WormState::Walking; //Paso a caminar
				break;
			}
			case false:
			{
				this->State = WormState::Walking; //Paso a caminar
				break;
			}
			}
		}
		break;
	}
	case WormState::Walking: //Si estoy caminando:
	{
		if (this->tickCount <= 43) //Y aun no llegue a la fase de reconfirmacion
		{
			switch (StartOrStop)
			{
			case true:
			{
				if (this->tickCount == 22 || this->tickCount == 36) //Me fijo si tengo que aumentar posicion
					if (this->Position.X <= Userdata.RightWall - 9)
						this->Position.X += 9;
				break;
			}
			case false:
			{
				if (this->tickCount == 22 || this->tickCount == 36) //Me fijo si tengo que aumentar posicion
					if (this->Position.X <= Userdata.RightWall - 9)
						this->Position.X += 9;
				break;
			}
			}
		}
		else if (this->tickCount > 43) //Si ya paso a la fase de reconfirmacion
		{
			switch (StartOrStop)
			{
			case true:
			{
				this->State = WormState::ReconfirmWalk; //Paso
				break;
			}
			case false:
			{
				this->State = WormState::ReconfirmWalk; //Paso
				break;
			}
			}
		}
		break;
	}
	case WormState::ReconfirmWalk: //Si estoy en la fase de reconfirmacion:
	{
		if (this->tickCount == 45) { //Por las dudas reseteo counter en el primer tick
			this->ReconfirmCounter = 0;
		}

		if (this->keyPressedRight) { //Si la tecla esta presionada por cada tick, aumento contador.
			this->ReconfirmCounter++;
		}

		if (this->tickCount < 50) { //Si no termine la fase de reconfirmacion, sigo caminando.
			switch (StartOrStop)
			{
			case true:
			{
				break;
			}
			case false:
			{
				break;
			}
			}
		}

		else if (this->tickCount == 50) {		//Si ya termino la fase de confirmacion:
			if (this->ReconfirmCounter == 6) {	//Si tuve la fase de confirmacion entera con la tecla presionada:
				this->State = WormState::Walking;
				this->tickCount = 9;
				this->ReconfirmCounter = 0;	//Paso a la fase de walking pero saltando confirmacion y warmup
				if (this->Position.X <= Userdata.RightWall - 9) //Y reseteo todo
					this->Position.X += 9;
			}
			else if (this->ReconfirmCounter < 6) { //Si en algun momento de la reconfirmacion, no estuvo la tecla
				this->State = WormState::Iddle; //presionada, entonces se pedira la fase de confirmacion
				this->tickCount = 0;		//y la fase de warm up de nuevo.
				this->ReconfirmCounter = 0;
				if (this->Position.X <= Userdata.RightWall - 9)
					this->Position.X += 9; //Se resetean las cosas.
			}
		}
	}
	break;
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
				case WormState::WaitingToWalk: {
					al_draw_bitmap(Userdata.WormWalk[0], Position.X, Position.Y, NULL); break;
				}
				case WormState::ReconfirmWalk: {
					if (this->tickCount <= 49)
						al_draw_bitmap(Userdata.WormWalk[tickCount - 35], Position.X, Position.Y, NULL);
					else if (this->tickCount == 50)
						al_draw_bitmap(Userdata.WormWalk[3], Position.X, Position.Y, NULL);
					break;
				}
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
					case WormState::WaitingToWalk: {
						al_draw_bitmap(Userdata.WormWalk[0], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL); break;
					}
					case WormState::ReconfirmWalk: {
					if (this->tickCount <= 49)
						al_draw_bitmap(Userdata.WormWalk[tickCount - 35], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
					else if (this->tickCount == 50)
						al_draw_bitmap(Userdata.WormWalk[3], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						break;
					}
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
							al_draw_bitmap(Userdata.WormWalk[tickCount - 6], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount <= 21)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 7], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount == 22)
							al_draw_bitmap(Userdata.WormWalk[3], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount <= 30)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 20], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount <= 35)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 21], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount == 36)
							al_draw_bitmap(Userdata.WormWalk[3], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount <= 44)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 34], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
						else if (this->tickCount <= 49)
							al_draw_bitmap(Userdata.WormWalk[tickCount - 35], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
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
			break;
		}
		case (WormState::WaitingToWalk):
		{
			switch (this->Direction) {
				case WormDirection::Left: {
					moveLeft(true, Userdata);
					break;
				}
				case WormDirection::Right: {
					moveRight(true, Userdata);
					break;
				}
			}
			break;
		}
		case (WormState::ReconfirmWalk):
		{
			switch (this->Direction) {
				case WormDirection::Left: {
					moveLeft(true, Userdata);
					break;
				}
				case WormDirection::Right: {
					moveRight(true, Userdata);
					break;
				}
			}
			break;
		}
		case (WormState::Walking):
		{
			switch (this->Direction) {
				case WormDirection::Left: {
					moveLeft(true, Userdata);
					break;
				}
				case WormDirection::Right: {
					moveRight(true, Userdata);
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

void Worm::clearTickCount(){
	this->tickCount = 0;
	this->ReconfirmCounter = 0;
}
void Worm::setState(WormState state) {
	this->State = state;
}
void Worm::setDirection(WormDirection direction) {
	this->Direction = direction;
}
void Worm::setKeyPressed(WormDirection dir, bool booli) {
	if (dir == WormDirection::Left)
		this->keyPressedLeft = booli;
	else
		this->keyPressedRight = booli;
}
void Worm::setPosition(int x, int y) {
	this->Position.X = x;
	this->Position.Y = y;
}
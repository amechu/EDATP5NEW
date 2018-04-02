#include "Userdata.h"

using namespace std;

Userdata::Userdata()
{
}



Userdata::~Userdata()
{
	for (int i = 0; i < 15; i++) {
		al_destroy_bitmap(this->WormWalk[i]);
	}

	for (int i = 0; i < 10; i++) {
		al_destroy_bitmap(this->WormJump[i]);
	}
}

void Userdata::LoadWormImages() {
	string string;

	for (int i = 1; i < 16; i++) {
		string = str + to_string(i) + ng;    //Se inicializan los bitmaps de los worms
		this->WormWalk[i - 1] = al_load_bitmap(string.c_str());
	}

	for (int i = 1; i < 11; i++) {
		string = STR + to_string(i) + NG;
		this->WormJump[i - 1] = al_load_bitmap(string.c_str());
	}
}

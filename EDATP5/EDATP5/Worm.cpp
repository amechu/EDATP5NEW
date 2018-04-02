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


void Worm::moveLeft() {

}


void Worm::moveRight() {

}


void Worm::Jump() {

}


void Worm::Draw(Userdata& Userdata) {

	switch (this->Direction) {
		case WormDirection::Left: {
			switch (this->State) {
				case WormState::Iddle: {
					al_draw_bitmap(Userdata.WormWalk[0], 701, 616, NULL); al_flip_display(); break;
				}
				case WormState::Walking: {

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

				}
				case WormState::Jumping: {

				}
			}
		}
	}
}

void Worm::Refresh() {

}
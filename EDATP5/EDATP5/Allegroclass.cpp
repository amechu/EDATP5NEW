#include "Allegroclass.h"

Allegro::Allegro()
{
	this->Timer = NULL;
	this->Background = NULL;
	this->Queue = NULL;
	this->Display = NULL;
}


Allegro::~Allegro()
{
	al_uninstall_keyboard();
	al_destroy_bitmap(this->Background);
	al_destroy_display(this->Display);
	al_destroy_timer(this->Timer);
	al_destroy_event_queue(this->Queue);
}


bool Allegro::Init(Userdata& Userdata) {

	bool ret = false;

	if (al_init()) {
		if (al_init_image_addon()) {
			if (al_install_keyboard()) {
				if (this->Display = al_create_display(this->SCREEN_W, this->SCREEN_H)) {
					if (this->Timer = al_create_timer(1 / this->FPS)) {
						if (this->Background = al_create_bitmap(this->SCREEN_W, this->SCREEN_H)) {
							if (this->Queue = al_create_event_queue()) {
								if (Background = al_load_bitmap("Scenario.png")) {
									ret = true;
									SetBackground();
								}
								else {
									ret = false;
									al_destroy_display(this->Display);
									al_destroy_timer(this->Timer);
									al_destroy_bitmap(this->Background);
									al_destroy_event_queue(this->Queue);
								}
							}
							else {
								al_destroy_display(this->Display);
								al_destroy_timer(this->Timer);
								al_destroy_bitmap(this->Background);
							}
						}
						else {
							ret = false;
							al_destroy_display(this->Display);
							al_destroy_timer(this->Timer);
						}
					}
					else {
						ret = false;
						al_destroy_display(this->Display);
					}
				}
				else
					ret = false;
			}
			else
				ret = false;
		}
		else
			ret = false;
	}

	for (int i = 0; i < 15; i++) {
		if (Userdata.WormWalk[i] = al_create_bitmap(60, 60)) {}
		else ret = false;
	}

	for (int i = 0; i < 10; i++) {
		if (Userdata.WormJump[i] = al_create_bitmap(60, 60)) {}
		else ret = false;
	}

	if (ret) {
		al_register_event_source(this->Queue, al_get_display_event_source(this->Display));
		al_register_event_source(this->Queue, al_get_timer_event_source(this->Timer));
		al_register_event_source(this->Queue, al_get_keyboard_event_source());
	}
	else {
		for (int i = 0; i < 15; i++) {
			al_destroy_bitmap(Userdata.WormWalk[i]);
		}
		for (int i = 0; i < 10; i++) {
			al_destroy_bitmap(Userdata.WormJump[i]);
		}
	}

	return ret;
}

void Allegro::SetBackground() {

	al_clear_to_color(al_map_rgb(50, 50, 50));
	al_draw_bitmap(this->Background, 0, 0, NULL);
	al_flip_display();
}
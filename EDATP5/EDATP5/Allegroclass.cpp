#include "Allegroclass.h"

Allegro::Allegro()
{
	this->Timer = NULL;
	this->Queue = NULL;
	this->Display = NULL;
	this->music = NULL;

}


Allegro::~Allegro()
{
	al_uninstall_keyboard();
	al_destroy_display(this->Display);
	al_destroy_timer(this->Timer);
	al_destroy_event_queue(this->Queue);
	stopMusic();
	al_uninstall_audio();
}


bool Allegro::Init(Userdata& Userdata) {

	bool ret = false;

	if (al_init()) {
		if (al_init_image_addon()) {
			if (al_install_keyboard()) {
				if (this->Display = al_create_display(this->SCREEN_W, this->SCREEN_H)) {
					if (this->Timer = al_create_timer(1 / this->FPS)) {
						if ((Userdata.Background = al_create_bitmap(this->SCREEN_W, this->SCREEN_H))&&(Userdata.WindowsBackground = al_create_bitmap(this->SCREEN_W, this->SCREEN_H))) {
							if (this->Queue = al_create_event_queue()) {
								if ((Userdata.Background = al_load_bitmap("Scenario.png"))&&(Userdata.WindowsBackground = al_load_bitmap("stars.png"))) {
									ret = true;
									al_draw_bitmap(Userdata.Background, 0, 0, NULL);
									al_draw_bitmap(Userdata.WindowsBackground, 0, 0, NULL);
								}

								else {
									ret = false;
									al_destroy_display(this->Display);
									al_destroy_timer(this->Timer);
									al_destroy_bitmap(Userdata.Background);
									al_destroy_event_queue(this->Queue);
								}
							}
							else {
								al_destroy_display(this->Display);
								al_destroy_timer(this->Timer);
								al_destroy_bitmap(Userdata.Background);
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

	if (al_install_audio()) //Inicializo los addons de audio
	{
		if (al_init_acodec_addon()) {
			al_reserve_samples(1);
		}
		else
			ret = false;
	}
	else
		ret = false;
		
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

		al_start_timer(this->Timer);
	}
	else {
		for (int i = 0; i < 15; i++) {
			al_destroy_bitmap(Userdata.WormWalk[i]);
		}
		for (int i = 0; i < 10; i++) {
			al_destroy_bitmap(Userdata.WormJump[i]);
		}
	}
	loadPlayMusic();

	return ret;
}

void Allegro::loadPlayMusic(void)
{
	this->music = al_load_sample(BACKGROUND_MUSIC);
	if (this->music)
		al_play_sample(this->music, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	else
		fprintf(stderr, "Unable to load background music\n");

}



void Allegro :: stopMusic(void)
{
	al_stop_samples();
	al_destroy_sample(music);
}
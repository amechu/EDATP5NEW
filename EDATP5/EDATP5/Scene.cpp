#include "Scene.h"

Scene::Scene()
{
}


Scene::~Scene()
{
	delete Worm1;
	delete Worm2;
}


void Scene::Draw(const Userdata& Userdata) {
	al_draw_bitmap(Userdata.Background, 0, 0, NULL);
}


void Scene::Refresh(const Userdata& Userdata) {
	
	al_clear_to_color(al_map_rgb(0, 0, 0));
	this->Draw(Userdata);
	this->Worm1->Draw(Userdata);
	this->Worm2->Draw(Userdata);
	this->Worm1->Refresh(Userdata);
	this->Worm2->Refresh(Userdata);
	al_flip_display();
}


void Scene::LoadWorm1(const Userdata& Userdata, unsigned int keySet) {
	this->Worm1 = new Worm(Userdata, keySet);
}


void Scene::LoadWorm2(const Userdata& Userdata, unsigned int keySet) {
	this->Worm2 = new Worm(Userdata, keySet);
}

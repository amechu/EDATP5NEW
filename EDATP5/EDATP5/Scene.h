#pragma once
#include "Userdata.h"
#include "Worm.h"

class Scene
{
public:
	Scene();
	~Scene();
	void Draw(const Userdata&); //No necesita cambiar nada para dibujar
	void Refresh();
	void LoadWorm1(const Userdata&, unsigned int);
	void LoadWorm2(const Userdata&, unsigned int);
	Worm* Worm1;
	Worm* Worm2;
};


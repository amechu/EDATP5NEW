#pragma once
#include "Userdata.h"
#include "Allegroclass.h"
#include "Worm.h"

class Scene
{
public:
	Scene();
	~Scene();
	void Draw(const Userdata&); //No necesita cambiar nada para dibujar
	void Refresh(const Userdata&);
	void LoadWorm1(const Userdata&, unsigned int);
	void LoadWorm2(const Userdata&, unsigned int);
	Worm* Worm1;
	Worm* Worm2;
};


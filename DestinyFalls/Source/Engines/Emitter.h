#pragma once
#include <map>
#include <iostream>
#include <vector>
#include "Particle.h"

class Particle;
struct ParticleFlyweight;

class Emitter
{
private:
	ParticleFlyweight* FlyWeight;

	float Spread = 0;
	int EmitterShape = 0;
	int width = 0;
	int height = 0;
	float PositionY = 0;
	float PositionX = 0;
	int MaxParticles = 1000;
	float SpawnRate = 1;
	std::vector<Particle*> Livelist;
	std::vector<Particle*> DeadList;

public:
	Emitter();
	~Emitter();
	void Update(float elapsedTime);
	void Render();

};

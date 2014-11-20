#pragma once
#include "../Engines/Emitter.h"
#include "../Game Objects/Object.h"

class Emitter;

class ParticleManager
{
private:

	std::vector<Particle> particlevector;
	int numParticles;
	Emitter size;
	std::string managerFilepath;

public:

	ParticleManager() ;
	~ParticleManager();

	void ReadXML(const char* filepath);
	void Render(Object * rhs = nullptr);
	void Update();


};


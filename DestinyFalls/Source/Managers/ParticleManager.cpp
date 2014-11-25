#include "stdafx.h"
#include "ParticleManager.h"
#include "../TinyXML/tinyxml.h"
#include "../TinyXML/tinystr.h"
#include <string>
#include <iostream>
#include "../Game States/GameplayState.h"
#include "../Engines/Particle.h"

ParticleManager::ParticleManager()
{

}

ParticleManager::~ParticleManager()
{
	
}

void ParticleManager::Exit()
{
	SGD::GraphicsManager *gm = SGD::GraphicsManager::GetInstance();
	gm->UnloadTexture(pImage);
}

void ParticleManager::ReadXML(const char* filepath)
{
	SGD::GraphicsManager* gm = SGD::GraphicsManager::GetInstance();

	TiXmlDocument doc;
	if (doc.LoadFile(filepath) == false)
		return;

	TiXmlElement * RootElement = doc.RootElement();

	RootElement->Attribute("ParticleAmount", &numParticles);
	managerFilepath = "resource/graphics/";
	managerFilepath += RootElement->Attribute("Texture");
	pImage = gm->LoadTexture(managerFilepath.c_str(), SGD::Color(0, 0, 0));

	int particleCircle;
	int particleSquare;
	int particleLine;
	for (unsigned int i = 0; i < numParticles; i++)
	{
		Particle ptemp;

		RootElement->Attribute("ParticleLifeTime", &ptemp.particleLifeTime);
		RootElement->Attribute("Scale", &ptemp.scale);
		RootElement->Attribute("Rotation", &ptemp.rotation);
		RootElement->Attribute("VelocityX", &ptemp.velocityX);
		RootElement->Attribute("VelocityY", &ptemp.velocityY);
		RootElement->Attribute("Circle", &particleCircle);
		RootElement->Attribute("Square", &particleSquare);
		RootElement->Attribute("Line", &particleLine);
		RootElement->Attribute("EmitterPositionX", &ptemp.emitPosX);
		RootElement->Attribute("EmitterPositionY", &ptemp.emitPosY);
		RootElement->Attribute("EmitterHeight", &ptemp.emitHeight);
		RootElement->Attribute("EmitterWidth", &ptemp.emitWidth);
		RootElement->Attribute("DestinationEmitterX", &ptemp.destinationEmitX);
		RootElement->Attribute("DestinationEmitterY", &ptemp.destinationEmitY);
		RootElement->Attribute("StartColorA", &ptemp.startColorA);
		RootElement->Attribute("StartColorR", &ptemp.startColorR);
		RootElement->Attribute("StartColorG", &ptemp.startColorG);
		RootElement->Attribute("StartColorB", &ptemp.startColorB);
		RootElement->Attribute("EndColorA", &ptemp.endColorA);
		RootElement->Attribute("EndColorR", &ptemp.endColorR);
		RootElement->Attribute("EndColorG", &ptemp.endColorG);
		RootElement->Attribute("EndColorB", &ptemp.endColorB);

		ptemp.circle = (bool)particleCircle;
		ptemp.square = (bool)particleSquare;
		ptemp.line = (bool)particleLine;

		particlevector.push_back(ptemp);
	}
}

void ParticleManager::Render(Object * rhs)
{
	SGD::GraphicsManager * gm = SGD::GraphicsManager::GetInstance();
	

	for (unsigned int i = 0; i < particlevector.size(); i++)
	{


		if (rhs != nullptr)
		{
			int x = rhs->GetPosition().x;		// min values
			int y = rhs->GetPosition().y;		// min values
			int width = particlevector[i].emitWidth;	// max values
			int height = particlevector[i].emitHeight;	// max values

			particlevector[i].position.x = (x + rand() % (width - x) + x);
			particlevector[i].position.y = (y + rand() % (height - y) + y);

			gm->DrawTexture(pImage,
				SGD::Point(particlevector[i].position.x,
				particlevector[i].position.y));
		}
		else
		{
			gm->DrawTexture(pImage,
				SGD::Point(rand() % 100,
				rand() % 100));
		}

	}


}
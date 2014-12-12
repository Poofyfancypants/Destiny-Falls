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
	SGD::GraphicsManager *pGraphics = SGD::GraphicsManager::GetInstance();
	pGraphics->UnloadTexture(pImage);
}

void ParticleManager::ReadXML(const char* filepath)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	TiXmlDocument doc;
	if (doc.LoadFile(filepath) == false)
		return;

	TiXmlElement * RootElement = doc.RootElement();

	RootElement->Attribute("ParticleAmount", &numParticles);
	managerFilepath = "resource/graphics/";
	managerFilepath += RootElement->Attribute("Texture");
	pImage = pGraphics->LoadTexture(managerFilepath.c_str(), SGD::Color(0, 0, 0));

	int particleCircle;
	int particleSquare;
	int particleLine;

	for (signed int i = 0; i < numParticles; i++)
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


		particlevector.push_back(ptemp);
	}
}

void ParticleManager::Render(Object * rhs)// add a point and a size, to place it anywhere when calling render
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();

	for (unsigned int i = 0; i < particlevector.size(); i++)
	{
		if (rhs != nullptr)
		{
			float x = (float)(rhs->GetPosition().x);		// min values
			float y = ((float)(rhs->GetPosition().y));		// min values
			int width =  particlevector[i].emitWidth;	// max values
			int height = particlevector[i].emitHeight;	// max values

			particlevector[i].position.x = (x + rand() % (width - (int)x) + (int)x);
			particlevector[i].position.y = (y + rand() % (height - (int)y) + (int)y);

			pGraphics->DrawTexture(pImage, SGD::Point(x, y));
		}
		else
		{
			int RandomA = rand() % 256;
			int RandomR = rand() % 256;
			int RandomG = rand() % 256;
			int RandomB = rand() % 256;

			pGraphics->DrawTexture(pImage, SGD::Point((float)(rand() % 100), (float)(rand() % 100)), {}, {}, SGD::Color(particlevector[i].startColorA, (particlevector[i].startColorR + RandomR), (particlevector[i].startColorG + RandomG), (particlevector[i].startColorB) + RandomB));
		}
	}
}


void ParticleManager::RenderPoint(SGD::Point pt)// add a point and a size, to place it anywhere when calling render
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();

	for (unsigned int i = 0; i < particlevector.size(); i++)
	{
		if (pt.x > 0 && pt.y > 0)
		{
			float x =(float)pt.x;		// min values
			float y =(float)pt.y;		// min values
			int width = particlevector[i].emitWidth;	// max values
			int height = particlevector[i].emitHeight;	// max values

			/*x = (pt.x + i);
			y = (pt.y + i);*/
			
			pGraphics->DrawTexture(pImage, SGD::Point(x, y), (float)particlevector[i].rotation, {}, SGD::Color(particlevector[i].startColorA, particlevector[i].startColorR, particlevector[i].startColorG, particlevector[i].startColorB));
		}
		else
		{

			pGraphics->DrawTexture(pImage, SGD::Point((float)(rand() % 100), (float)(rand() % 100)), {}, {}, SGD::Color(particlevector[i].startColorA, particlevector[i].startColorR, particlevector[i].startColorG, particlevector[i].startColorB));
		}
	}
}
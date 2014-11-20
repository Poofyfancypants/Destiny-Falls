#pragma once

#include "../../SGD Wrappers/SGD_GraphicsManager.h"

class Particle
{

public:
	SGD::Point position;
	int particleAmount = 0;
	int particleLifeTime = 0;
	int scale = 0;
	int rotation = 0;
	int velocityX = 0;
	int velocityY = 0;
	bool circle = false;
	bool square = false;
	bool line = false;
	int emitPosX = 0;
	int emitPosY = 0;
	int emitHeight = 0;
	int emitWidth = 0;
	int destinationEmitX = 0;
	int destinationEmitY = 0;
	int startColorA = 0;
	int startColorR = 0;
	int startColorG = 0;
	int startColorB = 0;
	int endColorA = 0;
	int endColorR = 0;
	int endColorG = 0;
	int endColorB = 0;

	SGD::HTexture pImage = SGD::INVALID_HANDLE;

	Particle();
	~Particle();
};


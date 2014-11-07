#pragma once
#include "AnimatedObject.h"
#include "MovingObject.h"
class Companion :
	public AnimatedObject,
		public MovingObject
{
public:
	Companion();
	~Companion();
};


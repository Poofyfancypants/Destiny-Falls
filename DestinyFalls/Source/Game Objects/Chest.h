#pragma once
#include "StaticObject.h"
#include "AnimatedObject.h"

class Chest :
	public StaticObject, 
		public AnimatedObject
{
public:
	Chest();
	~Chest();
};


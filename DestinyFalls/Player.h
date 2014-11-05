#pragma once
#include "AnimatedObject.h"
#include "MovingObject.h"
class Player :
	public AnimatedObject, 
		public MovingObject
{
public:
	Player();
	~Player();
};


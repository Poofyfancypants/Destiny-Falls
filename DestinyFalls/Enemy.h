#pragma once
#include "AnimatedObject.h"
#include "MovingObject.h"
class Enemy :
	public AnimatedObject,
		public MovingObject
{
public:
	Enemy();
	~Enemy();
};


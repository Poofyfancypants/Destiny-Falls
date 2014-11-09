#pragma once
#include "AnimatedObject.h"
#include "MovingObject.h"

#include "../../SGD Wrappers/SGD_Listener.h"

class Player :
	public AnimatedObject, 
		public MovingObject,
			public SGD::Listener
{
public:
	Player();
	~Player();

	//*******************************************************************
	// Listener Interface:
	virtual void	HandleEvent(const SGD::Event* pEvent) override;
};


#pragma once
#include "Enemy.h"
#include "Minion.h"

class LevelBoss :
	public Minion
{
public:
	LevelBoss();
	~LevelBoss();

	int GetAIType(void) const { return Level_Boss; }
	virtual bool TakeTurn();
	virtual void Update( float elapsedTime );
	virtual void Render( int _posIndex );
	void SetMinionAnimation( int region );
};


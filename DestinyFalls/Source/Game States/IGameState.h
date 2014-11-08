#pragma once

class IGameState
{
protected:
	IGameState() = default;
	virtual ~IGameState() = default;

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual bool Input() = 0;
	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;
};


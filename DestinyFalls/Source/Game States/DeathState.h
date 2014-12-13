#pragma once
#include <map>
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
class DeathState : public IGameState
{
public:

	enum PauseSelections{ resume, save, options, exit };

	static DeathState* GetInstance(void);

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

	bool GetDeathState() const {return m_bdeathState;}
	void SetDeathState(bool _state) {m_bdeathState = _state;}
private:

	DeathState() = default;
	virtual ~DeathState() = default;

	DeathState(const DeathState&) = delete;
	DeathState& operator=(const DeathState&) = delete;

	int m_nCursor = 0;
	bool m_bdeathState = false;
	std::map<std::string, SGD::Rectangle> m_mMouseoverRects;

	SGD::HTexture m_hBackground = SGD::INVALID_HANDLE;
	SGD::HTexture m_hButton = SGD::INVALID_HANDLE;
	SGD::HTexture m_hSelected = SGD::INVALID_HANDLE;
	
};

#pragma once

#include "IGameState.h"
#include <map>
class PauseMenuState : public IGameState
{
public:

	enum PauseSelections{resume, save, options, exit};
	static PauseMenuState* GetInstance(void);

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

	void SetPauseState(bool _state) { m_pauseStage = _state;}
	bool GetPauseState() const {return m_pauseStage;}
private:
	PauseMenuState() = default;
	virtual ~PauseMenuState() = default;

	PauseMenuState(const PauseMenuState&) = delete;
	PauseMenuState& operator=(const PauseMenuState&) = delete;

	int m_nCursor = 0;
	bool m_pauseStage = false;

	SGD::HTexture m_hBackground = SGD::INVALID_HANDLE;
	SGD::HTexture m_hButton = SGD::INVALID_HANDLE;
	SGD::HTexture m_hSelected = SGD::INVALID_HANDLE;

	std::map<std::string, SGD::Rectangle> m_mMenuOptions;

};


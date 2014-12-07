#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_Handle.h"		
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

#include "../Runes/Runes.h"
#include <vector>

class ForgeState : public IGameState
{
public:

	static ForgeState* GetInstance(void);

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

private:
	ForgeState() = default;
	virtual ~ForgeState() = default;

	ForgeState(const ForgeState&) = delete;
	ForgeState& operator=(const ForgeState&) = delete;

	bool m_bForge = false;
	bool m_bFail = false;

	Runes m_ptSelectedRune;

	Runes m_rSlot1;
	Runes m_rSlot2;
	Runes m_rSlot3;

	//full inventory rectangle
	SGD::Rectangle Fullrect = { 50, 50, 500, 400 };

	//Rune Rect Sized images for sword
	SGD::Rectangle Equip1 = {  60, 110, 115, 200 };
	SGD::Rectangle Equip2 = { 130, 110, 185, 200 };
	SGD::Rectangle Equip3 = { 295, 75, 415, 175 };

	// left side of inventory displaying images
	SGD::Rectangle ImageRect = { 50, 250, 200, 400 };
	SGD::Rectangle ForgeButton = { 50, 50, 200, 100};
	SGD::Rectangle ResultBox = {200, 50, 500, 200};

	SGD::Rectangle rect1 = { 50, 50, 200, 200 };
	SGD::Rectangle rect2 = { 50, 100, 200, 300 };

	//Rune Images
	//t1
	SGD::Rectangle IventoryRect1 =  { 250, 240, 280, 280 };
	SGD::Rectangle IventoryRect4 =  { 300, 240, 330, 280 };
	SGD::Rectangle IventoryRect7 =  { 250, 320, 280, 360 };
	SGD::Rectangle IventoryRect10 = { 300, 320, 330, 360 };
	//t2
	SGD::Rectangle IventoryRect2 =  { 370, 240, 400, 280 };
	SGD::Rectangle IventoryRect5 =  { 420, 240, 450, 280 };
	SGD::Rectangle IventoryRect8 =  { 370, 320, 400, 360 };
	SGD::Rectangle IventoryRect11 = { 420, 320, 450, 360 };




protected:

	SGD::HTexture m_hForge = SGD::INVALID_HANDLE;
	SGD::HTexture m_hDust = SGD::INVALID_HANDLE;

	SGD::HTexture m_hFiret1 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hFiret2 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hFiret3 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hWatert1 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hWatert2 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hWatert3 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hEartht1 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hEartht2 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hEartht3 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hAirt1 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hAirt2 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hAirt3 = SGD::INVALID_HANDLE;
};


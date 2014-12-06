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

	Runes m_ptSelectedRune;
	//full inventory rectangle
	SGD::Rectangle Fullrect = { 50, 50, 500, 400 };

	// left side of inventory displaying images
	SGD::Rectangle ImageRect = { 50, 50, 200, 400 };
	SGD::Rectangle ForgeButton = { 50, 50, 200, 200};
	SGD::Rectangle ResultBox = {200, 50, 500, 200};

	//line dividers in inventory
	SGD::Rectangle RuneSet1 = { 200, 170, 300, 200 };
	SGD::Rectangle RuneSet2 = { 300, 170, 400, 200 };
	SGD::Rectangle RuneSet3 = { 400, 170, 500, 200 };
	//rune equip slots
	SGD::Rectangle rect1 = { 200, 50, 300, 170 };
	SGD::Rectangle rect2 = { 300, 50, 400, 170 };
	SGD::Rectangle rect3 = { 400, 50, 500, 170 };

	SGD::Rectangle rect4 = { 200, 200, 300, 400 };
	SGD::Rectangle rect5 = { 300, 200, 400, 400 };
	SGD::Rectangle rect6 = { 400, 200, 500, 400 };

	//Rune Images
	//t1
	SGD::Rectangle IventoryRect1 =  { 210, 240, 240, 280 };
	SGD::Rectangle IventoryRect4 =  { 260, 240, 290, 280 };
	SGD::Rectangle IventoryRect7 =  { 210, 320, 240, 360 };
	SGD::Rectangle IventoryRect10 = { 260, 320, 290, 360 };
	//t2
	SGD::Rectangle IventoryRect2 =  { 310, 240, 340, 280 };
	SGD::Rectangle IventoryRect5 =  { 360, 240, 390, 280 };
	SGD::Rectangle IventoryRect8 =  { 310, 320, 340, 360 };
	SGD::Rectangle IventoryRect11 = { 360, 320, 390, 360 };


	//Rune Rect Sized images for sword
	SGD::Rectangle Equip1 = { 220, 70, 280, 150 };
	SGD::Rectangle Equip2 = { 420, 70, 480, 150 };

protected:

	SGD::HTexture m_hForge = SGD::INVALID_HANDLE;

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


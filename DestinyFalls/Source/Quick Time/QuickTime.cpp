#include "stdafx.h"
#include "QuickTime.h"

#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../Bitmap Font/BitmapFont.h"
#include "../Game Core/Game.h"


QuickTime::QuickTime()
{
	m_vKeys.push_back(SGD::Key::Q);
	m_vKeys.push_back(SGD::Key::W);
	m_vKeys.push_back(SGD::Key::E);
	m_vKeys.push_back(SGD::Key::A);
	m_vKeys.push_back(SGD::Key::S);
	m_vKeys.push_back(SGD::Key::D);

	SetLength(4);

	m_bqtOver = false;
}


QuickTime::~QuickTime()
{
}

void QuickTime::Update(float elapsedTime)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	m_fSeconds += elapsedTime;

	if (m_fSeconds < 2.0f && m_uncounter < m_unlength)
	{
		if (m_vOutput[m_uncounter] == pInput->GetAnyKeyDown())
		{
			AddGuess(m_vOutput[m_uncounter]);
			m_uncounter++;
			m_fSeconds = 0.0f;
		}
		else if (m_vOutput[m_uncounter] != pInput->GetAnyKeyDown())
		{
			m_unNumCorrect = m_uncounter;
			m_bqtOver = true;
		}
	}
	else
	{
		m_unNumCorrect = m_uncounter;
		m_bqtOver = true;
	}
}

void QuickTime::Render()
{
	SGD::Rectangle rect = { 250, 300, 300, 350 };

	SGD::GraphicsManager::GetInstance()->DrawRectangle(rect, SGD::Color{ 255, 100, 100, 100 });

	const BitmapFont* pFont = Game::GetInstance()->GetFont();

	pFont->Draw(m_sOutput.c_str(), { 275, 310 }, 1, { 255, 255, 255, 255 });
	pFont->Draw(m_sInput.c_str(), { 275, 325 }, 1, { 255, 255, 255, 255 });
}

void QuickTime::SetLength(unsigned int x)
{
	m_unlength = x;
	for (unsigned int i = 0; i < m_unlength; i++)
	{
		GenerateRandomLetter();
	}
}

void QuickTime::GenerateRandomLetter()
{
	int temp = rand() % 6;

	m_vOutput.push_back(m_vKeys[temp]);

	switch (m_vOutput[m_uncounter])
	{
	case SGD::Key::Q:
	{
						m_sOutput += " Q ";
	}
		break;
	case SGD::Key::W:
	{
						m_sOutput += " W ";
	}
		break;
	case SGD::Key::E:
	{
						m_sOutput += " E ";
	}
		break;
	case SGD::Key::A:
	{
						m_sOutput += " A ";
	}
		break;
	case SGD::Key::S:
	{
						m_sOutput += " S ";
	}
		break;
	case SGD::Key::D:
	{
						m_sOutput += " D ";
	}
		break;
	default:
		break;
	}
}

void QuickTime::AddGuess(SGD::Key x)
{
	m_vInput.push_back(x);

	switch (x)
	{
	case SGD::Key::Q:
	{
						m_sInput += " Q ";
	}
		break;
	case SGD::Key::W:
	{
						m_sInput += " W ";
	}
		break;
	case SGD::Key::E:
	{
						m_sInput += " E ";
	}
		break;
	case SGD::Key::A:
	{
						m_sInput += " A ";
	}
		break;
	case SGD::Key::S:
	{
						m_sInput += " S ";
	}
		break;
	case SGD::Key::D:
	{
						m_sInput += " D ";
	}
		break;
	default:
		break;
	}
}
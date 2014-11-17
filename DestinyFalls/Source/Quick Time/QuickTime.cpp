#include "stdafx.h"
#include "QuickTime.h"

#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"


QuickTime::QuickTime()
{
	m_vKeys.push_back(SGD::Key::Q);
	m_vKeys.push_back(SGD::Key::W);
	m_vKeys.push_back(SGD::Key::E);
	m_vKeys.push_back(SGD::Key::A);
	m_vKeys.push_back(SGD::Key::S);
	m_vKeys.push_back(SGD::Key::D);
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
		else if (pInput->IsAnyKeyPressed())
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
}

void QuickTime::AddGuess(SGD::Key x)
{
	m_vInput.push_back(x);
}
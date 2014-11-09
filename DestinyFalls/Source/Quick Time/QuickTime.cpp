#include "stdafx.h"
#include "QuickTime.h"


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

}

void QuickTime::Render()
{

}

void QuickTime::SetLength(unsigned int x)
{
	m_unlength = x;
	for (int i = 0; i < m_unlength; i++)
	{
		GenerateRandomLetter();
	}
}

void QuickTime::GenerateRandomLetter()
{
	int temp = rand() % 6;

	m_vOutput.push_back(m_vKeys[temp]);
}
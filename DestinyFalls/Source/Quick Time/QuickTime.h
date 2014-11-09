#pragma once

#include <vector>

#include "../../SGD Wrappers/SGD_Key.h"

class QuickTime
{
public:
	QuickTime();
	~QuickTime();

	void Update(float elapsedTime);
	void Render();
	
	unsigned int GetLength()				{ return m_unlength; }
	void SetLength(unsigned int x);

	void GenerateRandomLetter();


private:

	std::vector<SGD::Key> m_vOutput;
	std::vector<SGD::Key> m_vInput;
	std::vector<SGD::Key> m_vKeys;

	unsigned int m_unlength;
	unsigned int m_unNumCorrect;

protected:


};


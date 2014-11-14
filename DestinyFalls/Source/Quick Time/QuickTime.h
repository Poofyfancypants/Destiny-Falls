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
	void AddGuess(SGD::Key x);


private:

	std::vector<SGD::Key> m_vOutput;
	std::vector<SGD::Key> m_vInput;
	std::vector<SGD::Key> m_vKeys;

	unsigned int m_unlength = 4;
	unsigned int m_unNumCorrect = 0;
	float m_fSeconds = 0.0f;
	int m_ncounter = 0;
	bool m_bqtOver = false;

protected:


};


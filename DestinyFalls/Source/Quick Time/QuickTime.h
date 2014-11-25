#pragma once

#include <vector>

#include "../../SGD Wrappers/SGD_Key.h"
#include <string>
using namespace std;

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

	std::vector<SGD::Key> m_vOutput;
	std::vector<SGD::Key> m_vInput;
	std::vector<SGD::Key> m_vKeys;

	string m_sInput = "";
	string m_sOutput = "";

	unsigned int m_unlength = 4;
	unsigned int m_unNumCorrect = 0;
	unsigned int m_uncounter = 0;
	float m_fSeconds = 0.0f;
	bool m_bqtOver = false;




};


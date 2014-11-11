#pragma once

enum Elements { Fire, Earth, Water, Air, None };

class Runes
{
public:
	Runes();
	~Runes();

private:

	unsigned int m_unTier;
	Elements* m_ptElement;

};


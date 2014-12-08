#pragma once

enum Elements { Earth, Water, Air, Fire, None };

class Runes
{
public:
	Runes();
	~Runes();

	unsigned int GetTier() { return m_unTier; }
	void SetTier(unsigned int x) { m_unTier = x; }

	Elements GetElement() { return m_ptElement; }
	void SetElement(Elements x) { m_ptElement = x; }

private:

	unsigned int m_unTier;
	Elements m_ptElement;

};


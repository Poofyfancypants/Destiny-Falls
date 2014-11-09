#include "stdafx.h"
#include "RuneManager.h"

// combins element + element
ComboElements RuneManager::ElementCombination(Elements x, Elements y)
{
	if (x == y)
		return NotCombo;

	if (((x == Fire) && (y == Water)) || ((x == Water) && (y == Fire)))
		return Steam;
	if (((x == Fire) && (y == Air)) || ((x == Air) && (y == Fire)))
		return Lightning;
	if (((x == Fire) && (y == Earth)) || ((x == Earth) && (y == Fire)))
		return Magma;
	if (((x == Water) && (y == Air)) || ((x == Air) && (y == Water)))
		return Ice;
	if (((x == Water) && (y == Earth)) || ((x == Earth) && (y == Water)))
		return Mud;
	if (((x == Air) && (y == Earth)) || ((x == Earth) && (y == Air)))
		return Dust;

	return NotCombo;
}

// element vs. element
float RuneManager::DamagetoBaseElement(Elements x, Elements y)
{
	return 0;
}

// combo vs. element
float RuneManager::DamageComboElement(ComboElements x, Elements y)
{
	return 0;
}

// element vs. element
float RuneManager::DamageReduction(Elements x, Elements y)
{
	return 0;
}
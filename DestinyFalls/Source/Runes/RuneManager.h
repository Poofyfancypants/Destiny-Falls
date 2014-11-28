#pragma once

#include "Runes.h"

enum ComboElements { Steam, Ice, Lightning, Magma, Dust, Mud, Inferno, Wave, Earthquake, Whirlwind, NotCombo };

class RuneManager
{
public:
	RuneManager() = default;
	~RuneManager() = default;

	// combins element + element
	ComboElements ElementCombination(Elements x, Elements y);

	// element vs. element
	float DamagetoBaseElement(Elements x, Elements y);

	// combo vs. element
	float DamageComboElement(ComboElements x, Elements y);

	// element vs. element
	float DamageReduction(Elements x, Elements y);

private:


};


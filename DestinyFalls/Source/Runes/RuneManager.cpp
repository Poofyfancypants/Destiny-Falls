#include "stdafx.h"
#include "RuneManager.h"

// combins element + element
ComboElements RuneManager::ElementCombination(Elements x, Elements y)
{
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

	if (((x == Fire) && (y == Fire)) || ((x == Fire) && (y == Fire)))
		return Inferno;
	if (((x == Water) && (y == Water)) || ((x == Water) && (y == Water)))
		return Wave;
	if (((x == Air) && (y == Air)) || ((x == Air) && (y == Air)))
		return Whirlwind;
	if (((x == Earth) && (y == Earth)) || ((x == Earth) && (y == Earth)))
		return Earthquake;

	return NotCombo;
}

// element vs. element, attacker = x, being attacked = y, order is important 
float RuneManager::DamagetoBaseElement(Elements x, Elements y)
{
	if ((x == Fire) && (y == Water))
		return 0.5;
	if ((x == Water) && (y == Fire))
		return 2;
	if ((x == Fire) && (y == Air))
		return 2;
	if ((x == Air) && (y == Fire))
		return 0.5;
	if ((x == Fire) && (y == Earth))
		return 1;
	if ((x == Earth) && (y == Fire))
		return 1;
	if ((x == Water) && (y == Air))
		return 1;
	if ((x == Air) && (y == Water))
		return 1;
	if ((x == Water) && (y == Earth))
		return 0.5f;
	if ((x == Earth) && (y == Water))
		return 2;
	if ((x == Air) && (y == Earth))
		return 2;
	if ((x == Earth) && (y == Air))
		return 0.5;

	return 1;
}

// combo vs. element, attacker = x, being attacked = y, order is important 
float RuneManager::DamageComboElement(ComboElements x, Elements y)
{
	if ((x == Dust) && (y == Fire))
		return 2;
	if ((x == Dust) && (y == Water))
		return 1;
	if ((x == Dust) && (y == Air))
		return 0.5;
	if ((x == Dust) && (y == Earth))
		return 1;

	if ((x == Ice) && (y == Fire))
		return 1;
	if ((x == Ice) && (y == Water))
		return 0.5;
	if ((x == Ice) && (y == Air))
		return 2;
	if ((x == Ice) && (y == Earth))
		return 1;

	if ((x == Lightning) && (y == Fire))
		return 0.5;
	if ((x == Lightning) && (y == Water))
		return 2;
	if ((x == Lightning) && (y == Air))
		return 1;
	if ((x == Lightning) && (y == Earth))
		return 1;

	if ((x == Magma) && (y == Fire))
		return 0.5;
	if ((x == Magma) && (y == Water))
		return 1;
	if ((x == Magma) && (y == Air))
		return 1;
	if ((x == Magma) && (y == Earth))
		return 2;

	if ((x == Mud) && (y == Fire))
		return 1;
	if ((x == Mud) && (y == Water))
		return 1;
	if ((x == Mud) && (y == Air))
		return 2;
	if ((x == Mud) && (y == Earth))
		return 0.5;

	if ((x == Steam) && (y == Fire))
		return 2;
	if ((x == Steam) && (y == Water))
		return 1;
	if ((x == Steam) && (y == Air))
		return 0.5;
	if ((x == Steam) && (y == Earth))
		return 1;

	if ((x == Inferno) && (y == Fire))
		return 0.25;
	if ((x == Inferno) && (y == Water))
		return 0.75;
	if ((x == Inferno) && (y == Air))
		return 2.5;
	if ((x == Inferno) && (y == Earth))
		return 2;

	if ((x == Wave) && (y == Fire))
		return 2.5;
	if ((x == Wave) && (y == Water))
		return 0.25;
	if ((x == Wave) && (y == Air))
		return 0.75;
	if ((x == Wave) && (y == Earth))
		return 2;

	if ((x == Earthquake) && (y == Fire))
		return 0.75;
	if ((x == Earthquake) && (y == Water))
		return 2.5;
	if ((x == Earthquake) && (y == Air))
		return 0.25;
	if ((x == Earthquake) && (y == Earth))
		return 2;

	if ((x == Whirlwind) && (y == Fire))
		return 0.75;
	if ((x == Whirlwind) && (y == Water))
		return 2;
	if ((x == Whirlwind) && (y == Air))
		return 0.25;
	if ((x == Whirlwind) && (y == Earth))
		return 2.5;

	return 1;
}

// element vs. element, being attacked = x,  attacked = y, order is important 
float RuneManager::DamageReduction(Elements x, Elements y)
{
	return 0;
}

string RuneManager::ToString(ComboElements x)
{
	string combo;
	switch (x)
	{
	case Steam:
		combo = "Steam";
		break;
	case Ice:
		combo = "Ice";
		break;
	case Lightning:
		combo = "Lightning";
		break;
	case Magma:
		combo = "Magma";
		break;
	case Dust:
		combo = "Dust";
		break;
	case Mud:
		combo = "Mud";
		break;
	case Inferno:
		combo = "Inferno";
		break;
	case Wave:
		combo = "Wave";
		break;
	case Earthquake:
		combo = "Earthquake";
		break;
	case Whirlwind:
		combo = "Whirlwind";
		break;
	case NotCombo:
		break;
	default:
		break;
	}

	return combo;
}
#pragma once
#include<string>

enum UI_CHAMPTYPE
{
	UI_CHAMPTYPE_STATIC,
	UI_CHAMPTYPE_DYNAMIC
};

enum UI_SPELLTYPE
{
	SPELLTYPE_End,
	cleanse,
	Exhaust,
	Flash,
	Ghost,
	Heal,
	Smite,
	Teleport,
	Ignite,
	Barrier
};



// >> cheon Champion Key value
extern std::string g_ChampName;
extern std::string g_Spell_1;
extern std::string g_Spell_2;
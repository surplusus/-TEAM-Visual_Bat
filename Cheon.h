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

typedef struct ST_PT_VERTEX
{
	D3DXVECTOR3 p; //position
	D3DXVECTOR2 t; //uv position
	enum {FVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_NORMAL};
};

struct ST_SELECTED_CHAMP_INFO
{
	std::string					m_ChampName;
	std::string					m_Spell_1Name;
	std::string					m_Spell_2Name;
	ST_SELECTED_CHAMP_INFO() {}

	ST_SELECTED_CHAMP_INFO(ST_SELECTED_CHAMP_INFO *SelectedInfo)
		: m_ChampName(SelectedInfo->m_ChampName), m_Spell_1Name(SelectedInfo->m_Spell_1Name), m_Spell_2Name(SelectedInfo->m_Spell_2Name) {}

	ST_SELECTED_CHAMP_INFO(std::string ChampName, std::string Spell_1, std::string Spell_2)
		: m_ChampName(ChampName), m_Spell_1Name(Spell_1), m_Spell_2Name(Spell_2) {}
};

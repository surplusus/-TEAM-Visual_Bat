#pragma once
class CImage_Loader;
class CUI;
class CSelectedSpells;
class CSelectedChampion
{
public:
	CSelectedChampion(string ChampName);
	~CSelectedChampion();

public:
	void Initialize();
	void Render();
	void Release();
private:
	CImage_Loader*				m_pLoadingBoarder_blue;
	CImage_Loader*				m_pLoadingBoarder_red;

	map<string, CUI*>			m_mapChampList;


	CUI*						m_pEnemy;

	string						m_ChampName;

	CSelectedSpells*			m_pSpell_1;
	CSelectedSpells*			m_pSpell_2;
};
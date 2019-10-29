#pragma once

class CScene;


struct ST_SELECTED_CHAMP_INFO
{
	string					m_ChampName;
	string					m_Spell_1Name;
	string					m_Spell_2Name;
	ST_SELECTED_CHAMP_INFO() {}
	
	ST_SELECTED_CHAMP_INFO(ST_SELECTED_CHAMP_INFO *SelectedInfo)
		: m_ChampName(SelectedInfo->m_ChampName), m_Spell_1Name(SelectedInfo->m_Spell_1Name), m_Spell_2Name(SelectedInfo->m_Spell_2Name) {}
	
	ST_SELECTED_CHAMP_INFO(string ChampName, string Spell_1, string Spell_2)
		: m_ChampName(ChampName), m_Spell_1Name(Spell_1), m_Spell_2Name(Spell_2) {}
};

class CSceneMediator
{
public:
	CSceneMediator();
	~CSceneMediator();
private:
	class CSelectScene*		m_pSelectScene = nullptr;
	class CLoadingScene*	m_pLoadingScene = nullptr;
	class CGameScene*		m_pGameScene = nullptr;
	
	class GuhyunScene*		m_pGuhyunScene = nullptr;

	map<string, string>		m_mapStringInfo;
	map<string, CScene*>	m_mapSceneMember;
private:

public:
	void SetSceneMember(CScene* member);
	void MediateInfo(MEDIATETYPE type, CScene* member);

	//cheon

private:

private:
	ST_SELECTED_CHAMP_INFO	m_stInFo;
public:
	void SetSelectedChampInfo(ST_SELECTED_CHAMP_INFO champinfo) { m_stInFo = champinfo; }
	string SetSelectedChampName() { return m_stInFo.m_ChampName; }
	string SetSelectedSpell_1Name() { return m_stInFo.m_Spell_1Name; }
	string SetSelectedSpell_2Name() { return m_stInFo.m_Spell_2Name; }
	ST_SELECTED_CHAMP_INFO Get_ST_ChampInfo() { return m_stInFo; }
};


#pragma once

class CScene;

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
	class CInGameScene*		m_pInGameScene = nullptr;

	map<string, void**>		m_mapVoidPointer;
	map<string, CScene*>	m_mapSceneMember;
private:

public:
	void SetSceneMember(CScene* member);
	void MediateInfo(MEDIATETYPE type, CScene* member);

	// Guhyun
private:
	void	SetVoidPointerMap(string key, IN void** pVoid);
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


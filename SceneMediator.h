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

	map<string, string>		m_mapStringInfo;
	map<string, CScene*>		m_mapSceneMember;
private:

public:
	void SetSceneMember(CScene* member);
	void MediateInfo(MEDIATETYPE type, CScene* member);

	void InsertStringInfo(string key, string info);
	void CopyStringInfo(OUT map<string, string>* info);

	//cheon

private:
	string					m_ChampName;
	string					m_Spell_1Name;
	string					m_Spell_2Name;

public:
	void SetChampName(string name) { m_ChampName = name; }

	void SetSpell_1Name(string name) { m_Spell_1Name = name; }

	void SetSpell_2Name(string name) { m_Spell_2Name = name; }
};


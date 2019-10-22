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
	void SetSelectScene(CSelectScene* scene) { m_pSelectScene = scene; }
	void SetLoadingScene(CLoadingScene* scene) { m_pLoadingScene = scene; }
	void SetGameScene(CGameScene* scene) { m_pGameScene = scene; }
	void SetGuhyunScene(GuhyunScene* scene) { m_pGuhyunScene = scene; }
	void SetSceneMember(string sceneName, CScene* member);

	void InsertStringInfo(string key, string info);
	void CopyStringInfo(OUT map<string, string>* info);

	void MediateInfo(MEDIATETYPE type, CScene* member);
};


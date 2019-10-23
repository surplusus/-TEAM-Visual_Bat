#pragma once
//class CStateObj;
class CScene;
class CSceneMediator;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)
public:
	CSceneMgr();
	~CSceneMgr();
public:
	void Initialize();
	void Progress();
	void Render();
	void Release();
	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	HRESULT SetState(CScene* pState);
	CSceneMediator* GetSceneMediator() { return m_pSceneMediator; }
private:
	CScene *		m_State;
	CSceneMediator* m_pSceneMediator;
};


#pragma once
//class CStateObj;
class CScene;
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
private:
	CScene * m_State;

	bool     m_bSignChangeScene = false;
};


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
	void Initalize();
	void Progress();
	void Render();
	void Release();
	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	//HRESULT SetState(CStateObj* pState);
	HRESULT SetState(CScene* pState);
private:
	//CStateObj * m_State;
	CScene * m_State;

};


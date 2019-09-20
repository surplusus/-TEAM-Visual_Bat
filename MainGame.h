#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	HRESULT Init();
	void Render();
	void Release();
	void Progress();
	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:

	int m_iCnt;
	DWORD m_fTime;
	TCHAR m_szFps[128];
	D3DXMATRIX matFont;
	HRESULT InitResuource();
};


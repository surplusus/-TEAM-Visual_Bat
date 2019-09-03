#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Init();
	void Render();
	void Release();
	void Progress();
	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


};


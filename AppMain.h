#pragma once
#include"include.h"
#include"MainGame.h"

static CMainGame m_MainGame;
class AppMain
{
public:
	AppMain();
	~AppMain();
private:
	HWND m_hWnd;
	WNDCLASSEX m_wc;
public:
	static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParm, LPARAM lParam);
	void WinMainInit(HINSTANCE hInst, HINSTANCE, LPSTR, INT);
	int WinMainLoop();
	void Release();
private:
	HRESULT InitResuource();
	void Render();
	void Progress();
};


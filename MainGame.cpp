#include "BaseInclude.h"
#include "MainGame.h"
#include"SceneMgr.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
}

void CMainGame::Init()
{
	GET_SINGLE(CSceneMgr)->Initalize();
}

void CMainGame::Render()
{
	GET_SINGLE(CDevice)->Render_Begin();
	GET_SINGLE(CSceneMgr)->Render();
	GET_SINGLE(CDevice)->Render_End();
}

void CMainGame::Release()
{
	GET_SINGLE(CSceneMgr)->Release();
}

void CMainGame::Progress()
{
	GET_SINGLE(CSceneMgr)->Progress();
}

void CMainGame::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GET_SINGLE(CSceneMgr)->WndProc(hwnd,message,wParam,lParam);
}

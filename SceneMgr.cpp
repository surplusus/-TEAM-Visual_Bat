#include "BaseInclude.h"
#include "SceneMgr.h"
#include"GameScene.h"

CSceneMgr::CSceneMgr()
	:m_State(NULL)
{
}


CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Initalize()
{
	m_State = new GameScene;
	if (m_State != NULL)
		m_State->Initalize();
}

void CSceneMgr::Progress()
{
	if (m_State != NULL)
		m_State->Progress();
}

void CSceneMgr::Render()
{

	if (m_State != NULL)
		m_State->Render();

}

void CSceneMgr::Release()
{

	if (m_State != NULL)
		m_State->Release();
}

void CSceneMgr::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(m_State !=NULL)
	((CScene*)m_State)->WndProc(hwnd, message, wParam, lParam);
}

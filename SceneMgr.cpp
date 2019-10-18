#include "BaseInclude.h"
#include "SceneMgr.h"
#include "GameScene.h"
#include "GuhyunScene.h"

CSceneMgr::CSceneMgr()
	:m_State(NULL)
{
}


CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Initialize()
{
	m_State = new GuhyunScene();
	if (m_State != NULL)
		m_State->Initialize();
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
	if (m_State != NULL) {
		m_State->Release();

		delete m_State;
		m_State = NULL;
	}
}

void CSceneMgr::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(m_State !=NULL)
	((CScene*)m_State)->WndProc(hwnd, message, wParam, lParam);
}

HRESULT CSceneMgr::SetState(CScene * pState)
{
	if (pState == NULL) 
		return E_FAIL;

	if (m_State)
	{
		m_State->Release();
		delete m_State;
		m_State = NULL;
	}

	m_State = pState;

	m_State->Initialize();

	return S_OK;
}

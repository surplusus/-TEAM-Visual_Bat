#include "BaseInclude.h"
#include "SceneMgr.h"
#include "SceneMediator.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "LoadingScene.h"
#include "GuhyunScene.h"
#include "HUDScene.h"
#include "InGameScene.h"
#include "TestScene.h"

CSceneMgr::CSceneMgr()
	:m_State(NULL)
{
}


CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Initialize()
{
	m_pSceneMediator = new CSceneMediator();
	//m_State = new CGameScene;
	//m_State = new GuhyunScene;
	m_State = new CTestScene;
	m_pSceneMediator->SetSceneMember(m_State);
	if (m_State != NULL)
		m_State->Initialize();
}

void CSceneMgr::Progress()
{
	if (CheckPushKeyOneTime(VK_ESCAPE)) {
		//GET_SINGLE(CSceneMgr)->SetState(new CGameScene);
		PostMessage(NULL, WM_QUIT, 0, 0);
		return;
	}
	if (m_State != NULL)
		m_State->Progress();
}

void CSceneMgr::Render()
{
	if (m_State != NULL)
		m_State->Render();
	MyDrawFPSByTimeMgr();
}

void CSceneMgr::Release()
{
	if (m_State != NULL) {
		m_State->Release();
		delete m_State;
		m_State = NULL;
	}
	if (m_pSceneMediator != NULL) {
		delete m_pSceneMediator;
		m_pSceneMediator = NULL;
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
	// mediator로 이전 Scene에서 정보 건내받기
	m_pSceneMediator->SetSceneMember(pState);
	m_pSceneMediator->MediateInfo(MEDIATETYPE::INIT, pState);

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

CSceneMediator * CSceneMgr::GetSceneMediator()
{
	return m_pSceneMediator;
}

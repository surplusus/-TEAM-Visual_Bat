#include "BaseInclude.h"
#include "LoadingScene.h"
#include "Image_Loader.h"
#include "SelectedPlayer.h"
#include "TextMgr.h"
#include "SceneMgr.h"
#include "SelectScene.h"
#include "GuhyunScene.h"
#include "ThreadPool.h"
#include "SelectedSpells.h"
#include "GameScene.h"
#include "InGameScene.h"
#include <functional>
#include "LoadingFunctor.h"
#include "MakingTowerFunctor.h"
#include "ProgressBarFunctor.h"

CLoadingScene::CLoadingScene()
	: m_pTextMgr(nullptr)
	, m_pBackGround(nullptr)
	, m_pChampSelect(nullptr)
	, m_pSpell_1(nullptr)
	, m_pSpell_2(nullptr)
	, m_pLoadingFunctor(nullptr)
	, m_pMakingTowerFunctor(nullptr)
	, m_pProgressBarFunctor(nullptr)
	, m_bLoadingComplete(false)
	, m_bOnSwitch(true)
{
}

CLoadingScene::~CLoadingScene()
{
}

HRESULT CLoadingScene::Initialize()
{
	m_pBackGround = new CImage_Loader("Resource/choen/Loading/LoadingBackGround.jpg", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_pBackGround->Initialize();

	m_pChampSelect = new CSelectedPlayer(GET_SINGLE(CSceneMgr)->GetSceneMediator()->SetSelectedChampName());
	m_pChampSelect->Initialize();
	
	m_pTextMgr = new CTextMgr();
	m_pTextMgr->Initialize();
	//GET_SINGLE(CSceneMgr)->GetSceneMediator()->MediateInfo(MEDIATETYPE::INIT, this);

	{	// SetUp Functors
		string sFilePath = "Test/test.dat";
		//string sFilePath = "MeshPathList.dat";
		m_pLoadingFunctor = new CLoadingFunctor(sFilePath);
		m_pMakingTowerFunctor = new CMakingTowerFunctor(sFilePath);
		m_pProgressBarFunctor = new CProgressBarFunctor(this);
	}

	return S_OK;
}

void CLoadingScene::Progress()
{
	if (GetAsyncKeyState(VK_LEFT))
		GET_SINGLE(CSceneMgr)->SetState(new CSelectScene);
	
	Progress_LoadingFunctors();
	
	if (m_bLoadingComplete) {
		GET_SINGLE(CSceneMgr)->SetState(new GuhyunScene);
		//GET_SINGLE(CSceneMgr)->SetState(new CInGameScene);
	}
}

void CLoadingScene::Render()
{
	if (!m_bLoadingComplete) {
		(*m_pProgressBarFunctor)();
		return;
	}
	m_pBackGround->Render();
	m_pTextMgr->LoadingNoticeRender();
	m_pChampSelect->Render();
}

void CLoadingScene::Release()
{
	delete m_pBackGround;
	m_pBackGround = NULL;

	delete m_pChampSelect;
	m_pChampSelect = NULL;
	delete m_pTextMgr;
	m_pTextMgr = NULL;

	SAFE_DELETE(m_pLoadingFunctor);
	SAFE_DELETE(m_pProgressBarFunctor);
}

bool CLoadingScene::Progress_LoadingFunctors()
{
	static float fCntOneSec = 0;
	bool bFunc1Complate, bFunc2Complate;
	//bFunc1Complate = bFunc2Complate = false;
	fCntOneSec += g_fDeltaTime;


	if (fCntOneSec >= 1.f) {
		if (m_pLoadingFunctor != nullptr)
			bFunc1Complate = !(*m_pLoadingFunctor)();
		else
			bFunc1Complate = true;
		
		if (m_pMakingTowerFunctor != nullptr) {
			if (bFunc1Complate)
				bFunc2Complate = !(*m_pMakingTowerFunctor)();
		}
		else
			bFunc2Complate = true;
		
		if (bFunc1Complate && bFunc2Complate) {
			if (fCntOneSec >= 2.f)
				m_bLoadingComplete = true;
		}
		else 
			fCntOneSec = 0.f;
	}
	return true;
}

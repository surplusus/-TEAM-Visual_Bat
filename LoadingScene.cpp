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
#include "ProgressBarFunctor.h"

CLoadingScene::CLoadingScene()
	: m_pTextMgr(nullptr)
	, m_pBackGround(nullptr)
	, m_pChampSelect(nullptr)
	, m_pSpell_1(nullptr)
	, m_pSpell_2(nullptr)
	, m_pLoadingFunctor(nullptr)
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
		m_pLoadingFunctor = new CLoadingFunctor;
		m_pProgressBarFunctor = new CProgressBarFunctor(this);
		{	// 로딩 functor에게 정보를 넣어준다.(수정요)
			string sChampName = GET_SINGLE(CSceneMgr)->GetSceneMediator()->Get_ST_ChampInfo().m_ChampName;
			if (sChampName == "")	sChampName = "Udyr";
			m_pLoadingFunctor->m_SelectedChamp = sChampName;
		}
	}

	return S_OK;
}

void CLoadingScene::Progress()
{
	if (GetAsyncKeyState(VK_LEFT))
		GET_SINGLE(CSceneMgr)->SetState(new CSelectScene);
	
	static float fFake = 0;
	fFake += g_fDeltaTime;
	if (fFake >= 1.f) {
		m_bLoadingComplete = (*m_pLoadingFunctor)();
		fFake = 0.f;
	}
	
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

bool CLoadingScene::OperateLoadingFunctorThruThread()
{
	try{
		//m_bLoadingComplete = (g_future.wait_for(chrono::milliseconds(0)) == future_status::ready);
		//g_status = g_future.wait_for(chrono::milliseconds(0));
		//if (g_status == std::future_status::deferred) {
		//	std::cout << "deferred\n";
		//}
		//else if (g_status == std::future_status::timeout) {
		//	std::cout << "timeout\n";
		//}
		//else if (g_status == std::future_status::ready) {
		//	std::cout << "ready!\n";
		//}
		//if (m_bLoadingComplete)
		//cout << " 결과는요 : " << g_future.get() << '\n';
	}
	catch (const std::exception& e)
	{
		cout << e.what() << '\n';
	}

	return m_bLoadingComplete;
}
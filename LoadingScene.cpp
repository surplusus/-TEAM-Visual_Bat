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

thread* pThread = nullptr;

bool Operate(CLoadingScene* pLoading, LPD3DXSPRITE pLoadingSprite, LPDIRECT3DTEXTURE9 pLoadingTexture, int iProgressBar)
{
	cout << "Thread  Begin\n";

	cout << "ProgressBar SetUp\n";
	do
	{
		this_thread::sleep_for(chrono::milliseconds(100));
		{
			printf("sprite delta time : %d\n", iProgressBar);
			Begin_Render();

			//pLoading->m_pBackGround->Render();
			//pLoading->m_pTextMgr->LoadingNoticeRender();
			//pLoading->m_pChampSelect->Render();

			pLoadingSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

			static int cnt = 0;
			cnt++;
			if (cnt >= 100) {
				iProgressBar++;
				cnt = 0;
			}
			iProgressBar %= 24;

			int startCoord = 128 * iProgressBar;

			RECT re = { startCoord, 0, startCoord + 128, 128 };
			D3DXVECTOR3 position(2 * WINSIZEX - 250.f, 2 * WINSIZEY - 200.f, 0.f);
			D3DXMATRIX matS;	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
			pLoadingSprite->SetTransform(&matS);
			pLoadingSprite->Draw(pLoadingTexture, &re
				, &D3DXVECTOR3(0.f, 0.f, 0.f), &position, D3DCOLOR_RGBA(255, 255, 255, 100));
			pLoadingSprite->End();

			End_Render(g_hWnd);
			printf("End Render\n");
		}

	} while (false);

	SAFE_RELEASE(pLoadingSprite);
	SAFE_RELEASE(pLoadingTexture);
	return true;
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
		(*m_pProgressBarFunctor)();
		LPD3DXSPRITE pSprite = m_pProgressBarFunctor->m_pLoadingSprite;
		LPDIRECT3DTEXTURE9 pTexture = m_pProgressBarFunctor->m_pLoadingTexture;
		int iProgressBar = m_pProgressBarFunctor->m_iProgressBar;
		m_pProgressBarFunctor->SetTextureByPara(pSprite, pTexture);
		{	// 로딩 functor에게 정보를 넣어준다.(수정요)
			string sChampName = GET_SINGLE(CSceneMgr)->GetSceneMediator()->Get_ST_ChampInfo().m_ChampName;
			if (sChampName == "")	sChampName = "Ezreal";
			m_pLoadingFunctor->m_SelectedChamp = sChampName;
		}

		pThread = new thread(ref(*m_pLoadingFunctor));

		//m_future = GET_THREADPOOL->EnqueueFunc(THREAD_LOADMAP, Operate, this,pSprite,pTexture,iProgressBar);
	}

	return S_OK;
}

void CLoadingScene::Progress()
{
	if (GetAsyncKeyState(VK_LEFT))
		GET_SINGLE(CSceneMgr)->SetState(new CSelectScene);
	if (CheckPushKeyOneTime(VK_SPACE))
		int n = 0;
	
	//m_bLoadingComplete = OperateLoadingFunctorThruThread();
	pThread->
	//m_bLoadingComplete = (g_future1.wait_for(chrono::seconds(0)) == future_status::ready);

	if (m_bLoadingComplete) {
		GET_SINGLE(CSceneMgr)->SetState(new GuhyunScene);
		//GET_SINGLE(CSceneMgr)->SetState(new CInGameScene);
	}
}

void CLoadingScene::Render()
{
	if (!m_bLoadingComplete)
		return;
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
	//static bool once = true;
	//static shared_future<bool> future;
	try
	{
		//if (once) {
		//	once = false;
		//	CLoadingFunctor functor;
		//	{	// 로딩 functor에게 정보를 넣어준다.(수정요)
		//	string sChampName = GET_SINGLE(CSceneMgr)->GetSceneMediator()->Get_ST_ChampInfo().m_ChampName;
		//	if (sChampName == "")	sChampName = "Ezreal";
		//	functor.m_SelectedChamp = sChampName;
		//	}


		//	function<bool(void)> func = [functor]() mutable {bool result = functor(); return result; };
		//	
		//	for (int i = 0; i < length; i++)
		//	{

		//	}

		//	future = GET_THREADPOOL->EnqueueFunc(THREAD_LOADMAP, func);
		//}

		static int iSkipTime = 0;
		++iSkipTime;
		if (iSkipTime > 10){
			cout << "들어왔따\n";
			//m_bLoadingComplete = (g_future.wait_for(chrono::milliseconds(0)) == future_status::ready);
			//g_status = g_future.wait_for(chrono::milliseconds(0));
			iSkipTime = 0;
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
	}
	catch (const std::exception& e)
	{
		cout << e.what() << '\n';
	}

	return m_bLoadingComplete;
}
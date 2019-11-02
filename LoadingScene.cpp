#include "BaseInclude.h"
#include "LoadingScene.h"
#include "Image_Loader.h"
#include "SelectedPlayer.h"
#include "TextMgr.h"
#include "SceneMgr.h"
#include "SelectScene.h"
#include "GuhyunScene.h"
#include "ThreadPool.h"
#include "ObjMgr.h"
#include "SummonTerrain.h"
#include "SelectedSpells.h"
#include "GameScene.h"
#include "Udyr.h"
#include "Ezreal.h"
#include "Factory.h"
#include "SummonTerrain.h"
#include "InGameScene.h"
#include "SoundMgr.h"
#include "MeshMgr.h"
#include "MeleeMinion.h"
#include <fstream>
#include <sstream>

CLoadingScene::CLoadingScene() 
	: m_pLoadingSprite(nullptr)
	, m_pLoadingTexture(nullptr)
	, m_iMeshInfoSize(0)
	, m_iProgressBar(0)
	, m_pTextMgr(nullptr)
	, m_pBackGround(nullptr)
	, m_pChampSelect(nullptr)
	, m_pSpell_1(nullptr)
	, m_pSpell_2(nullptr)
	, m_bLoadingComplete(false)
{
}

CLoadingScene::~CLoadingScene()
{
	Release();
}

HRESULT CLoadingScene::Initialize()
{
	m_pBackGround = new CImage_Loader("Resource/choen/Loading/LoadingBackGround.jpg", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_pBackGround->Initialize();


	m_pChampSelect = new CSelectedPlayer(GET_SINGLE(CSceneMgr)->GetSceneMediator()->SetSelectedChampName());
	m_pChampSelect->Initialize();
	
	m_pTextMgr = new CTextMgr();
	m_pTextMgr->Initialize();
	cout << "로딩 됨" << endl;
	//GET_SINGLE(CSceneMgr)->GetSceneMediator()->MediateInfo(MEDIATETYPE::INIT, this);

	{	// Loading Progress Bar
		SetUp_ProgressBar();
	}

	return S_OK;
}

void CLoadingScene::Progress()
{
	if (GetAsyncKeyState(VK_LEFT))
		GET_SINGLE(CSceneMgr)->SetState(new CSelectScene);
	if (CheckPushKeyOneTime(VK_SPACE))
		GET_SINGLE(CSceneMgr)->SetState(new GuhyunScene);
	
	bool ckeck = OperateLoadingFunctorThruThread();
	if (ckeck)
		GET_SINGLE(CSceneMgr)->SetState(new GuhyunScene);
		//GET_SINGLE(CSceneMgr)->SetState(new CInGameScene);
}

void CLoadingScene::Render()
{
	m_pBackGround->Render();
	m_pTextMgr->LoadingNoticeRender();
	m_pChampSelect->Render();

	// Loading Progress Bar
	Render_ProgressBar();
}

void CLoadingScene::Release()
{
	delete m_pBackGround;
	m_pBackGround = NULL;

	delete m_pChampSelect;
	m_pChampSelect = NULL;
	delete m_pTextMgr;
	m_pTextMgr = NULL;

	SAFE_RELEASE(m_pLoadingSprite);
	SAFE_RELEASE(m_pLoadingTexture);
}

void CLoadingScene::SetUp_ProgressBar()
{
	if (FAILED(D3DXCreateTextureFromFileExA(GET_DEVICE
		, "./Resource/choen/Loading/loading_circle.png"
		, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8
		, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT
		, 0, &m_ImageInfo, NULL, &m_pLoadingTexture)))
		cout << "그림을 못 불렀지용~" << endl;
	if (FAILED(D3DXCreateSprite(GET_DEVICE, &m_pLoadingSprite)))
		cout << "sprite를 못 불렀지용~" << endl;

	m_iProgressBar = 0;
}

void CLoadingScene::Render_ProgressBar()
{
	m_pLoadingSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	static int cnt = 0;
	cnt++;
	if (cnt >= 100) {
		m_iProgressBar++;
		cnt = 0;
	}
	m_iProgressBar %= 24;

	int startCoord = 128 * m_iProgressBar;

	RECT re = { startCoord, 0, startCoord+128, 128};
	D3DXVECTOR3 position(2 * WINSIZEX - 250.f,2 * WINSIZEY - 200.f, 0.f);
	D3DXMATRIX matS;	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
	m_pLoadingSprite->SetTransform(&matS);
	m_pLoadingSprite->Draw(m_pLoadingTexture, &re
		, &D3DXVECTOR3(0.f, 0.f, 0.f), &position, D3DCOLOR_RGBA(255, 255, 255, 100));
	m_pLoadingSprite->End();
}

bool CLoadingScene::OperateLoadingFunctorThruThread()
{
	static bool once = true;
	static future<bool> future;
	if (once) {
		once = false;
		CLoadingFunctor functor;
		string sChampName = GET_SINGLE(CSceneMgr)->GetSceneMediator()->Get_ST_ChampInfo().m_ChampName;
		if (sChampName == "")	sChampName = "Ezreal";
		functor.m_SelectedChamp = sChampName;
		future = GET_THREADPOOL->EnqueueFunc(THREAD_LOADMAP, functor);
	}

	//future_status result;
	bool bReady = future._Is_ready();
	//bool re = GET_THREADPOOL->PollThreadEnd(THREAD_LOADMAP);  이건 또 왜 안되냐?
	if (bReady)
	{
		GET_THREADPOOL->Thread_Stop(THREAD_LOADMAP);
		return true;
		//return future.get();     이거 왜 안되는거냐???
	}
	return false;
}
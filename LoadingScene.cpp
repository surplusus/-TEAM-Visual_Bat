#include "BaseInclude.h"
#include "LoadingScene.h"
#include "Image_Loader.h"
#include "SelectedChampion.h"
#include "Text.h"
#include "SceneMgr.h"
#include "SelectScene.h"
//#include "GuhyunScene.h"
#include "SceneMediator.h"

CLoadingScene::CLoadingScene() :m_pBackGround(NULL)
{
}


CLoadingScene::~CLoadingScene()
{
}



HRESULT CLoadingScene::Initialize()
{
	m_pBackGround = new CImage_Loader("Resource/choen/Loading/LoadingBackGround.jpg", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_pBackGround->Initialize();


	m_pChampSelect = new CSelectedChampion(D3DXVECTOR3(255, 0, 0));
	m_pChampSelect->Initialize();

	GET_SINGLE(CText)->Initialize();
	cout << "·Îµù µÊ" << endl;

	{	// mediate
		GET_SINGLE(CSceneMgr)->GetSceneMediator()->MediateInfo(MEDIATETYPE::INIT,this);
	}
	{
		D3DXVECTOR2 v;
		v = { 0.f,(float)WINSIZEY - 20.f };	m_vLinePoint.push_back(v);
		v = { 0.f,(float)WINSIZEY };		m_vLinePoint.push_back(v);
		v = { 0.f,(float)WINSIZEY};			m_vLinePoint.push_back(v);
		v = { 0.f,(float)WINSIZEY - 20.f };	m_vLinePoint.push_back(v);
	}
	return S_OK;
}

void CLoadingScene::Progress()
{
	//if (GetAsyncKeyState(VK_SPACE))
	//	GET_SINGLE(CSceneMgr)->SetState(new GuhyunScene);
}

void CLoadingScene::Render()
{
	m_pBackGround->Render();
	GET_SINGLE(CText)->LoadingNoticeRender();
	m_pChampSelect->Render();

	cout << nVertex1 << endl;
	{
		//static int n = 0;
		//n++;
		//if (n >= 200)	n = 200;
		//int per = WINSIZEX / (200 - nVertex1);
		//m_vLinePoint[2].x = per;
		//m_vLinePoint[3].x = per;
		//LPD3DXLINE line;
		//D3DXCreateLine(GET_DEVICE, &line);
		//line->SetWidth(10);
		//line->Begin();
		//line->Draw(&m_vLinePoint[0], 4, D3DCOLOR_XRGB(255, 0, 0));
		//line->End();
		//line->Release();
	}
	//Rectangle(GetDC(g_hWnd), 0, WINSIZEY - 20, x, WINSIZEY);
	//static int i = 0;
	//i++;
	//if (i <= WINSIZEX)
	//{
	//	return;
	//}
	//i = 0;
	//
	//x += (WINSIZEX / 100);
	//if (WINSIZEX < x)	x = WINSIZEX;
}

void CLoadingScene::Release()
{
	delete m_pBackGround;
	m_pBackGround = NULL;

	delete m_pChampSelect;
	m_pChampSelect = NULL;
}

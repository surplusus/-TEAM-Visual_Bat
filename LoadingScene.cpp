#include "BaseInclude.h"
#include "LoadingScene.h"
#include "Image_Loader.h"
#include "SelectedChampion.h"
#include "Text.h"
#include "SceneMgr.h"
#include "SelectScene.h"

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
	return S_OK;
}

static int x = 0;

void CLoadingScene::Progress()
{
	if (GetAsyncKeyState(VK_SPACE))
		GET_SINGLE(CSceneMgr)->SetState(new CSelectScene);
}

void CLoadingScene::Render()
{
	m_pBackGround->Render();
	GET_SINGLE(CText)->LoadingNoticeRender();
	m_pChampSelect->Render();

	Rectangle(GetDC(g_hWnd), 0, WINSIZEY - 20, x, WINSIZEY);
	static int i = 0;
	i++;
	if (i <= WINSIZEX)
	{
		return;
	}
	i = 0;

	x += (WINSIZEX / 100);
	if (WINSIZEX < x)	x = WINSIZEX;
}

void CLoadingScene::Release()
{
	delete m_pBackGround;
	m_pBackGround = NULL;

	delete m_pChampSelect;
	m_pChampSelect = NULL;
}
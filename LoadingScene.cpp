#include "BaseInclude.h"
#include "LoadingScene.h"
#include "Image_Loader.h"
#include "SelectedChampion.h"
#include "Text.h"
#include "SceneMgr.h"
#include "SelectScene.h"
#include "GuhyunScene.h"
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
	cout << "로딩 됨" << endl;

	{	// Loading Progress Bar
		if (FAILED(D3DXCreateTextureFromFileExA(GET_DEVICE
			, "./Resource/choen/Loading/loading_circle.png"
			, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2
			, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8
			, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT
			, 0, &m_ImageInfo, NULL, &m_pLoadingTexture)))
			cout << "그림을 못 불렀지용~" << endl;
		if (FAILED(D3DXCreateSprite(GET_DEVICE, &m_pLoadingSprite)))
			cout << "sprite를 못 불렀지용~" << endl;
	}
	{	// Load Resource By Thread

	}
	return S_OK;
}

void CLoadingScene::Progress()
{
	if (GetAsyncKeyState(VK_SPACE))
		GET_SINGLE(CSceneMgr)->SetState(new GuhyunScene);


}

void CLoadingScene::Render()
{
	m_pBackGround->Render();
	GET_SINGLE(CText)->LoadingNoticeRender();
	m_pChampSelect->Render();

	// Loading Progress Bar
	Render_Loading();
}

void CLoadingScene::Release()
{
	delete m_pBackGround;
	m_pBackGround = NULL;

	delete m_pChampSelect;
	m_pChampSelect = NULL;

	SAFE_RELEASE(m_pLoadingSprite);
	SAFE_RELEASE(m_pLoadingTexture);
}

void CLoadingScene::Render_Loading()
{
	m_pLoadingSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	static int n = 0;
	static int y = 0;
	static float size = 1.f;
	n++;
	if (n >= 500) {
		n = 0;
		y += 128;
		size *= 0.8f;
		if (y >= 3072) y = 0;
		printf(" %d ", y);
	}
	RECT re = { y,0,y+128, 128};
	D3DXVECTOR3 position(2 * WINSIZEX - 250.f,2 * WINSIZEY - 200.f, 0.f);
	D3DXMATRIX matS;	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
	m_pLoadingSprite->SetTransform(&matS);
	m_pLoadingSprite->Draw(m_pLoadingTexture, &re
		, &D3DXVECTOR3(0.f, 0.f, 0.f), &position, D3DCOLOR_RGBA(255, 255, 255, 100));
	m_pLoadingSprite->End();
}

#include "BaseInclude.h"
#include "ProgressBarFunctor.h"
#include "LoadingScene.h"
#include "Image_Loader.h"
#include "SelectedPlayer.h"
#include "TextMgr.h"

CProgressBarFunctor::CProgressBarFunctor(CLoadingScene*	pLoadingScene)
	: m_pLoadingScene(nullptr)
	, m_pLoadingSprite(nullptr)
	, m_pLoadingTexture(nullptr)
	, m_iProgressBar(0)
	, m_iTimeProgressed(0)
	, m_bOnSwitch(false)
{
}

CProgressBarFunctor::CProgressBarFunctor(CProgressBarFunctor && functor)
{
	m_pLoadingScene = functor.m_pLoadingScene;
	m_pLoadingSprite = functor.m_pLoadingSprite;
	m_pLoadingTexture = functor.m_pLoadingTexture;
	m_iProgressBar = functor.m_iProgressBar;
	m_iTimeProgressed = functor.m_iTimeProgressed;
	m_ImageInfo = functor.m_ImageInfo;
}

CProgressBarFunctor::CProgressBarFunctor(const CProgressBarFunctor & functor)
{
	m_pLoadingScene = functor.m_pLoadingScene;
	m_pLoadingSprite = functor.m_pLoadingSprite;
	m_pLoadingTexture = functor.m_pLoadingTexture;
	m_iProgressBar = functor.m_iProgressBar;
	m_iTimeProgressed = functor.m_iTimeProgressed;
	m_ImageInfo = functor.m_ImageInfo;
}


CProgressBarFunctor::~CProgressBarFunctor()
{
	SAFE_RELEASE(m_pLoadingSprite);
	SAFE_RELEASE(m_pLoadingTexture);
}

bool CProgressBarFunctor::operator()()
{
	if (!m_bOnSwitch)
		return true;

	//printf("sprite delta time : %d\n", m_iProgressBar);
	printf("Start\n");
	Begin_Render();
	
	m_pLoadingScene->m_pBackGround->Render();
	m_pLoadingScene->m_pTextMgr->LoadingNoticeRender();
	m_pLoadingScene->m_pChampSelect->Render();

	Render_ProgressBar();

	End_Render(g_hWnd);
	printf("End Render\n");

	return false;
}

void CProgressBarFunctor::SetTextureByPara(LPD3DXSPRITE pSprite, LPDIRECT3DTEXTURE9 pTexture)
{
	m_pLoadingSprite = pSprite;
	m_pLoadingTexture = pTexture;
}

void CProgressBarFunctor::SetUp_ProgressBar()
{
	if (FAILED(D3DXCreateTextureFromFileExA(GET_DEVICE
		, "./Resource/Sprite/loading_circle.png"
		, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8
		, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT
		, 0, &m_ImageInfo, NULL, &m_pLoadingTexture)))
		cout << "그림을 못 불렀지용~" << endl;
	if (FAILED(D3DXCreateSprite(GET_DEVICE, &m_pLoadingSprite)))
		cout << "sprite를 못 불렀지용~" << endl;
	cout << "ProgressBar SetUp\n";
}

void CProgressBarFunctor::Render_ProgressBar()
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

	RECT re = { startCoord, 0, startCoord + 128, 128 };
	D3DXVECTOR3 position(2 * WINSIZEX - 250.f, 2 * WINSIZEY - 200.f, 0.f);
	D3DXMATRIX matS;	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
	m_pLoadingSprite->SetTransform(&matS);
	m_pLoadingSprite->Draw(m_pLoadingTexture, &re
		, &D3DXVECTOR3(0.f, 0.f, 0.f), &position, D3DCOLOR_RGBA(255, 255, 255, 100));
	m_pLoadingSprite->End();
}

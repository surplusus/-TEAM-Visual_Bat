#include "BaseInclude.h"
#include "LoadingScene.h"
#include "Image_Loader.h"
#include "SelectedChampion.h"
#include "Text.h"

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

	cout << m_pBackGround->GetImageInfo().Width << " " << m_pBackGround->GetImageInfo().Height << endl;

	m_pChampSelect = new CSelectedChampion(D3DXVECTOR3(255, 0, 0));
	m_pChampSelect->Initialize();


	GET_SINGLE(CText)->Initialize();
	return E_NOTIMPL;
}

void CLoadingScene::Progress()
{
}

void CLoadingScene::Render()
{
	m_pBackGround->Render();
	GET_SINGLE(CText)->LoadingNoticeRender();

	m_pChampSelect->Render();
}

void CLoadingScene::Release()
{
	delete m_pBackGround;
	m_pBackGround = NULL;

	delete m_pChampSelect;
	m_pChampSelect = NULL;
}
#include "BaseInclude.h"
#include "LoadingScene.h"
#include "Image_Loader.h"
#include "SelectedChamp.h"
#include "Text.h"

CLoadingScene::CLoadingScene() :m_pLoader(NULL)
{
}


CLoadingScene::~CLoadingScene()
{
}



HRESULT CLoadingScene::Initialize()
{
	m_pLoader = new CImage_Loader("Resource/choen/Loading/LoadingBackGround.jpg", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_pLoader->Initialize();

	cout << m_pLoader->GetImageInfo().Width << " " << m_pLoader->GetImageInfo().Height << endl;


	GET_SINGLE(CText)->Initialize();
	return E_NOTIMPL;
}

void CLoadingScene::Progress()
{
}

void CLoadingScene::Render()
{
	m_pLoader->Render();
	GET_SINGLE(CText)->LoadingNoticeRender();
}

void CLoadingScene::Release()
{
	delete m_pLoader;
	m_pLoader = NULL;
}

#include "BaseInclude.h"
#include "SelectedChampion.h"
#include "Image_Loader.h"


CSelectedChampion::CSelectedChampion()
{
}


CSelectedChampion::~CSelectedChampion()
{
}

CSelectedChampion::CSelectedChampion(D3DXVECTOR3 color)
	: m_vColor(color), m_pLoadingBoarder_blue(NULL), m_pLoadingBoarder_red(NULL)
{
}

void CSelectedChampion::Initialize()
{
	m_pLoadingBoarder_blue = new CImage_Loader("Resource/choen/Loading/ChallengerBoarder.png", D3DXVECTOR3(400, 0, 0),	 D3DXVECTOR3(0.7f, 0.7f, 0));
	m_pLoadingBoarder_red  = new CImage_Loader("Resource/choen/Loading/ChallengerBoarder.png", D3DXVECTOR3(400, 410, 0), D3DXVECTOR3(0.7f, 0.7f, 0));
	m_pLoadingBoarder_blue->Initialize();
	m_pLoadingBoarder_red->Initialize();
}

int CSelectedChampion::Progress()
{
	return 0;
}

void CSelectedChampion::Render()
{
	m_pLoadingBoarder_blue->Render();
	m_pLoadingBoarder_red->Render();
}

void CSelectedChampion::Release()
{
	m_pLoadingBoarder_blue->Release();
	m_pLoadingBoarder_red ->Release();
}

void CSelectedChampion::Render(D3DXVECTOR3 pos)
{
}
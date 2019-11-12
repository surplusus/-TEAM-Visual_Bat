#include "BaseInclude.h"
#include "CameraMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "SummonTerrain.h"

#include"HeightMap.h"

#include "HUDScene.h"
#include "GameHUD.h"

cHUDScene::cHUDScene()
{
	m_pObjMgr = (GET_SINGLE(CObjMgr));
	m_pHeightMap = NULL;
}


cHUDScene::~cHUDScene()
{
}

HRESULT cHUDScene::Initialize()
{
	if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(0.f, 10.f, -10.f)
		, D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))
		return E_FAIL;

	if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
		return E_FAIL;

	/*if (FAILED(AddMesh(GetDevice(), L"./Resource/Test/", L"TestFloor.x", L"Map", MESHTYPE_STATIC)))
		{
			ERR_MSG(g_hWnd, L"Summon Map Load Failed");		return E_FAIL;
		}*/

	if (FAILED(AddMesh(GetDevice(), L"./Resource/Map/HowlingAbyss/", L"howling_Map.x", L"Map", MESHTYPE_STATIC)))
	{
		ERR_MSG(g_hWnd, L"Champion Load Failed");		return E_FAIL;
	}

	if (FAILED(m_pObjMgr->AddObject(L"Map", CFactory<CObj, CSummonTerrain >::CreateObject())))
		return E_FAIL;

	LetObjectKnowHeightMap();

	GET_SINGLE(cGameHUD)->Initialize();
	return S_OK;
}

void cHUDScene::Progress()
{
	GET_SINGLE(CCameraMgr)->Progress();

	m_pObjMgr->Progress();

	GET_SINGLE(cGameHUD)->Progress();
}

void cHUDScene::Render()
{
	m_pObjMgr->Render();
	GET_SINGLE(cGameHUD)->Render();
}

void cHUDScene::Release()
{
	m_pObjMgr->DestroyInstance();
	GET_SINGLE(cGameHUD)->Release();
}

void cHUDScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

HRESULT cHUDScene::Setup()
{
	SetRenderState(D3DRS_LIGHTING, false);
	return S_OK;
}

void cHUDScene::Update()
{
	m_pObjMgr->Progress();
	GET_SINGLE(CCameraMgr)->Progress();
}

void cHUDScene::LetObjectKnowHeightMap()
{
	m_pHeightMap = new CHeightMap();
	m_pHeightMap->LoadData("./Resource/Map/HowlingAbyss/howling_HeightMap.x");
	return;
}

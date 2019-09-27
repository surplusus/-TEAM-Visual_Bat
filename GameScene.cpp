#include "BaseInclude.h"
#include "GameScene.h"
#include "XFileUtil.h"
#include"ResourceFunc.h"
#include "CameraMgr.h"
#include"Factory.h"
#include"ObjMgr.h"
#include"Terrain.h"
#include"CameraMgr.h"
#include"SommonTerrain.h"
#include"Atrox.h"
GameScene::GameScene()
{
	m_pObjMgr = (GET_SINGLE(CObjMgr));
}


GameScene::~GameScene()
{
}

HRESULT GameScene::Initalize()
{
	if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_GAME, D3DXVECTOR3(0.f, 50.f, -10.f)
		, D3DXVECTOR3(0.f, 10.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))
		return E_FAIL;

	if (Setup())
		return E_FAIL;
	
	if (FAILED(AddMesh(GetDevice(), L"./Resource/Aatrox/", L"Atrax.x", L"Atrax", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"Sylva Load Failed");		return E_FAIL;
	}

	if (FAILED(AddMesh(GetDevice(), L"./Resource/MapSommon/", L"SummonMap.x", L"Map", MESHTYPE_STATIC)))
	{
		ERR_MSG(g_hWnd, L"Summon Map Load Failed");		return E_FAIL;
	}


	if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
		return E_FAIL;

	if (FAILED(m_pObjMgr->AddObject(L"Map_SommonMap", CFactory<CObj, CSommonTerrain>::CreateObject())))
	{
		return E_FAIL;
	}
	if (FAILED(m_pObjMgr->AddObject(L"Player_Atrax", CFactory<CObj, CAtrox >::CreateObject())))
	{
		return E_FAIL;
	}

}

void GameScene::Progress()
{
	GET_SINGLE(CCameraMgr)->Progress();
	m_pObjMgr->Progress();
	
}

void GameScene::Render()
{
	m_pObjMgr->Render();

}

void GameScene::Release()
{
}

HRESULT GameScene::Setup()
{
	SetRenderState(D3DRS_LIGHTING, FALSE);
	return S_OK;

}

void GameScene::Update()
{
	m_pObjMgr->Progress();
	GET_SINGLE(CCameraMgr)->Progress();
}

void GameScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}


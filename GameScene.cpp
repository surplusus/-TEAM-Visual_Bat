#include "BaseInclude.h"
#include "GameScene.h"
#include "XFileUtil.h"
#include"ResourceFunc.h"
#include "CameraMgr.h"
#include"Factory.h"
#include"ObjMgr.h"
#include "SceneMgr.h"
   
#include"Terrain.h"
#include"SummonTerrain.h"
#include"Atrox.h"
GameScene::GameScene()
{
	m_pObjMgr = (GET_SINGLE(CObjMgr));
}


GameScene::~GameScene()
{
}

HRESULT GameScene::Initialize()
{
	/*if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(0.f, 10.f, -10.f)
		, D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))
		return E_FAIL;*/
	if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(0.f, 50.f, -10.f)
		, D3DXVECTOR3(0.f, 10.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))
		return E_FAIL;

	if (Setup())		// light off
		return E_FAIL;
	

	if (FAILED(AddMesh(GetDevice(), L"./Resource/MapSummon/", L"SummonMap.x", L"Map", MESHTYPE_STATIC)))
	{
		ERR_MSG(g_hWnd, L"Summon Map Load Failed");		return E_FAIL;
	}
	/*if (FAILED(AddMesh(GetDevice(), L"./Resource/Mesh/Dynamic/Sylva", L"sylva.X", L"sylva", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"Sylva Load Failed");		return E_FAIL;
	}

	if (FAILED(AddMesh(GetDevice(), L"./Resource/Mesh/Static/TombStone", L"TombStone.X", L"TombStone", MESHTYPE_STATIC)))
	{
		ERR_MSG(g_hWnd, L"TomeStone Load Failed");		return E_FAIL;
	}*/


	//if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
	//	return E_FAIL;
	//if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_SPHERE)))
	//	return E_FAIL;


	if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
		return E_FAIL;

	if (FAILED(m_pObjMgr->AddObject(L"Map", CFactory<CObj, CSummonTerrain >::CreateObject())))
		return E_FAIL;
	//if (FAILED(m_pObjMgr->AddObject(L"Player_Atrax", CFactory<CObj, CAtrox >::CreateObject())))
	//	return E_FAIL;

	//ObjMgr정보를 등록한다.
	//const CObj*pObj = m_pObjMgr->GetObj(L"Player_Atrax");
	//((CChampion*)pObj)->RegisterObjMgr(m_pObjMgr);

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
	SetRenderState(D3DRS_LIGHTING, false);
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


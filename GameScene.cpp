#include "BaseInclude.h"
#include "GameScene.h"
#include "XFileUtil.h"
#include"ResourceFunc.h"
#include "CameraMgr.h"
#include"Factory.h"
#include"ObjMgr.h"
#include"Terrain.h"
#include"CameraMgr.h"
#include"SummonTerrain.h"
#include"Atrox.h"
#include"Amumu.h"
CGameScene::CGameScene()
{
	m_pObjMgr = (GET_SINGLE(CObjMgr));
}


CGameScene::~CGameScene()
{
}

HRESULT CGameScene::Initialize()
{
	/*if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(0.f, 10.f, -10.f)
		, D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))
		return E_FAIL;*/
	if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(0.f, 50.f, -10.f)
		, D3DXVECTOR3(0.f, 10.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))
		return E_FAIL;

	if (Setup())
		return E_FAIL;
	
	//if (FAILED(AddMesh(GetDevice(), L"./Resource/MapSummon/", L"Floor.x", L"Map", MESHTYPE_STATIC)))
	//{
	//	ERR_MSG(g_hWnd, L"Summon Map Load Failed");		return E_FAIL;
	//}
	//if (FAILED(AddMesh(GetDevice(), L"./Resource/Ez/", L"Ez.X", L"Amumu", MESHTYPE_DYNAMIC)))
	//{
	//	ERR_MSG(g_hWnd, L"Champion Load Failed");		return E_FAIL;
	//}

	//if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
	//	return E_FAIL;
	//if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_SPHERE)))
	//	return E_FAIL;
	if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
		return E_FAIL;

	//if (FAILED(m_pObjMgr->AddObject(L"Map", CFactory<CObj, CSummonTerrain >::CreateObject())))
	//	return E_FAIL;
	//if (FAILED(m_pObjMgr->AddObject(L"Amumu", CFactory<CObj, CAmumu >::CreateObject())))
	//	return E_FAIL;

	//ObjMgr정보를 등록한다.
	//const CObj*pObj = m_pObjMgr->GetObj(L"Amumu");
	//((CChampion*)pObj)->RegisterObjMgr(m_pObjMgr);

}

void CGameScene::Progress()
{
	GET_SINGLE(CCameraMgr)->Progress();
	m_pObjMgr->Progress();
	
}

void CGameScene::Render()
{
	m_pObjMgr->Render();
}

void CGameScene::Release()
{

}

HRESULT CGameScene::Setup()
{
	SetRenderState(D3DRS_LIGHTING, false);
	return S_OK;
}

void CGameScene::Update()
{
	m_pObjMgr->Progress();
	GET_SINGLE(CCameraMgr)->Progress();
}

void CGameScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}


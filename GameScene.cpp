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
#include"Ezreal.h"
#include"EzealQ_Particle.h"
#include"ParticleMgr.h"
#include"HeightMap.h"
#include"CollisionMgr.h"
#include"Cursor.h"
#include"GameHUD.h"
#include"Udyr.h"
#include"Turret.h"
#include"Nexus.h"
#include"Inhibitor.h"
CGameScene::CGameScene()
{
	m_pObjMgr = (GET_SINGLE(CObjMgr));
	m_pHeightMap = NULL;
}


CGameScene::~CGameScene()
{
}

HRESULT CGameScene::Initialize()
{
	if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(0.f, 50.f, -10.f)
		, D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))		return E_FAIL;

	if (Setup())
		return E_FAIL;
	InitAsset();
	if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE))) return E_FAIL;
	
	if (FAILED(AddMesh(GetDevice(), L"./Resource/Champion/", L"Ezreal.x", L"Ezreal", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"Champion Load Failed");		return E_FAIL;
	}
	if (FAILED(AddMesh(GetDevice(), L"./Resource/Champion/", L"Ezreal.x", L"Ezreal2", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"Champion Load Failed");		return E_FAIL;
	}
	if (FAILED(AddMesh(GetDevice(), L"./Resource/Map/HowlingAbyss/", L"howling_Map.x", L"Map", MESHTYPE_STATIC)))
	{
		ERR_MSG(g_hWnd, L"Champion Load Failed");		return E_FAIL;
	}
	if (FAILED(AddMesh(GetDevice(), L"./Resource/Champion/", L"Udyr.x", L"Udyr", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"Champion Load Failed");		return E_FAIL;
	}

#pragma region 천->포탑, 억제기, 타워(order)
	if (FAILED(AddMesh(GetDevice(), L"./Resource/choen/Tower/Blue_Turret/", L"order_Turret.x", L"Blue_Turret", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"Turret Failed"); return E_FAIL;
	}
	vector<CTurret*> vecTurret(4);
	vecTurret[0] = new CTurret(D3DXVECTOR3(23.f, 0.f, 22.5f));
	vecTurret[1] = new CTurret(D3DXVECTOR3(14.5f, 0.f, 14.3f));
	vecTurret[2] = new CTurret(D3DXVECTOR3(4.5f, 0.f, 0.9f));
	vecTurret[3] = new CTurret(D3DXVECTOR3(1.f, 0.f, 4.7f));
	for (size_t i = 0; i < vecTurret.size(); i++)
	{
		vecTurret[i]->Initialize();
		GET_SINGLE(CObjMgr)->AddObject(L"Blue_Turret", vecTurret[i]);
	}

	if (FAILED(AddMesh(GetDevice(), L"./Resource/choen/Tower/inhibitor/", L"inhibitor.x", L"Inhibitor", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"inhibitor Failed"); return E_FAIL;
	}
	CInhibitor * pinhibitor = NULL;
	pinhibitor = new CInhibitor(D3DXVECTOR3(9.5f, 0.f, 9.5f));
	pinhibitor->Initialize();
	GET_SINGLE(CObjMgr)->AddObject(L"Inhibitor", pinhibitor);

	if (FAILED(AddMesh(GetDevice(), L"./Resource/choen/Tower/Nexus/", L"Nexus.x", L"Nexus", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"Nexus Failed"); return E_FAIL;
	}
	CNexus * pNexus = NULL;
	pNexus = new CNexus(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	pNexus->Initialize();
	GET_SINGLE(CObjMgr)->AddObject(L"Nexus", pNexus);

#pragma endregion
	
	if (FAILED(m_pObjMgr->AddObject(L"Map", CFactory<CObj, CSummonTerrain >::CreateObject())))
		return E_FAIL;
	if (FAILED(m_pObjMgr->AddObject(L"Ezreal", CFactory<CObj, CEzreal >::CreateObject())))
		return E_FAIL;

	CObj* p = new CEzreal("IDLE1", false);
	p->Initialize();
	if (FAILED(m_pObjMgr->AddObject(L"Ezreal2", p)))
		return E_FAIL;

//	if (FAILED(m_pObjMgr->AddObject(L"Udyr", CFactory<CObj, CUdyr >::CreateObject())))
//		return E_FAIL;

	LetObjectKnowHeightMap();
	m_Cursor = new CCursor;
	m_Cursor->InitCursor();
	m_Cursor->SetCursor(CCursor::CURSORTYPE::CURSORTYPE_INGAME);
	GET_SINGLE(cGameHUD)->Initialize();
}

void CGameScene::Progress()
{
	GET_SINGLE(CCameraMgr)->Progress();
	m_pObjMgr->Progress();

	GET_SINGLE(CCollisionMgr)->Progress();
	GET_SINGLE(CParticleMgr)->Progress();
	GET_SINGLE(cGameHUD)->Progress();
}

void CGameScene::Render()
{
	m_pObjMgr->Render();
	GET_SINGLE(CCollisionMgr)->Render();
	GET_SINGLE(CParticleMgr)->Render();
	GET_SINGLE(cGameHUD)->Render();
}

void CGameScene::Release()
{
	m_pObjMgr->DestroyInstance();
	GET_SINGLE(CCollisionMgr)->DestroyInstance();
	GET_SINGLE(CParticleMgr)->DestroyInstance();
	GET_SINGLE(CCameraMgr)->DestroyInstance();
	GET_SINGLE(cGameHUD)->Release();
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

HRESULT CGameScene::InitAsset()
{	
	HRESULT hr;
	if (FAILED(InsertTexture(GetDevice(), TEXTYPE_NORMAL, L"./Resource/Ez/Particles/Ezreal_Base_Q_mis_trail.dds", L"Effect", L"Arrow_Q1")))
	{
		return E_FAIL;
	}
	if (FAILED(InsertTexture(GetDevice(), TEXTYPE_NORMAL, L"./Resource/Ez/Particles/Ezreal_Base_R_trail.dds", L"Effect", L"Arrow_Q2")))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CGameScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}


void CGameScene::LetObjectKnowHeightMap()
{
	m_pHeightMap = new CHeightMap();
	m_pHeightMap->LoadData("./Resource/Map/HowlingAbyss/howling_HeightMap.x");
	CObj* pObj = nullptr;
	pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Ezreal"));
	
	if (pObj != nullptr) {
		dynamic_cast<CEzreal*>(pObj)->SetHeightMap(m_pHeightMap);
	}	
	pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Ezreal2"));
	if (pObj != nullptr) {
		dynamic_cast<CEzreal*>(pObj)->SetHeightMap(m_pHeightMap);
	}

	return;
}
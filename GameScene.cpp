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
#include"ColitionMgr.h"
#include"Cursor.h"
#include"Turret.h"
#include"Inhibitor.h"
#include"Nexus.h"
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
	/*if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(0.f, 10.f, -10.f)
		, D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))
		return E_FAIL;*/
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
	if (FAILED(AddMesh(GetDevice(), L"./Resource/Map/HowlingAbyss/", L"howling_Map.x", L"Map", MESHTYPE_STATIC)))
	{
		ERR_MSG(g_hWnd, L"Champion Load Failed");		return E_FAIL;
	}

	if (FAILED(m_pObjMgr->AddObject(L"Ezreal", CFactory<CObj, CEzreal >::CreateObject())))
		return E_FAIL;
	CObj *ez = new CEzreal("IDLE1", false);
	ez->Initialize();
	if (FAILED(m_pObjMgr->AddObject(L"Ezreal2",ez)))
		return E_FAIL;

// cheon
#pragma region 블루팀 포탑
	if (SUCCEEDED(AddMesh(GetDevice(), L"./Resource/choen/Tower/Blue_Turret/"
		, L"blue_Turret.x", L"Blue_Turret", MESHTYPE_DYNAMIC)))
	{
		CTurret* pTurret = new CTurret(D3DXVECTOR3(23.f, 0.f, 22.5f));
		pTurret->Initialize();
		GET_SINGLE(CObjMgr)->AddObject(L"Blue_Turret", pTurret);
	}
	else
		ERR_MSG(g_hWnd, L"Blue_Turret Load Failed");
#pragma endregion 포탑 끝

#pragma region 블루팀 억제기
	if (SUCCEEDED(AddMesh(GetDevice(), L"./Resource/choen/Tower/inhibitor/"
		, L"inhibitor.x", L"Inhibitor", MESHTYPE_DYNAMIC)))
	{
		CInhibitor*	pInhibitor = new CInhibitor(D3DXVECTOR3(9.5f, 0.f, 9.5f));
		pInhibitor->Initialize();
		GET_SINGLE(CObjMgr)->AddObject(L"Inhibitor", pInhibitor);
	}
	else
		ERR_MSG(g_hWnd, L"inhibitor Load Failed");
#pragma endregion 억제기 끝

#pragma region 넥서스
	if (SUCCEEDED(AddMesh(GetDevice(), L"./Resource/choen/Tower/Nexus/"
		, L"Nexus.x", L"Nexus", MESHTYPE_DYNAMIC)))
		GET_SINGLE(CObjMgr)->AddObject(L"Nexus", CFactory<CObj, CNexus>::CreateObject());
	else
		ERR_MSG(g_hWnd, L"Nexus Load Failed");
#pragma endregion 넥서스 끝
// choen

	if (FAILED(m_pObjMgr->AddObject(L"Map", CFactory<CObj, CSummonTerrain >::CreateObject())))
		return E_FAIL;

	LetObjectKnowHeightMap();

	m_Cursor = new CCursor;
	m_Cursor->InitCursor();
	m_Cursor->SetCursor(CCursor::CURSORTYPE::CURSORTYPE_INGAME);
}

void CGameScene::Progress()
{
	GET_SINGLE(CCameraMgr)->Progress();
	m_pObjMgr->Progress();

	GET_SINGLE(CColitionMgr)->Progress();
	GET_SINGLE(CParticleMgr)->Progress();
}

void CGameScene::Render()
{
	m_pObjMgr->Render();

	GET_SINGLE(CColitionMgr)->Render();
	GET_SINGLE(CParticleMgr)->Render();
}

void CGameScene::Release()
{
	m_pObjMgr->DestroyInstance();
	GET_SINGLE(CColitionMgr)->DestroyInstance();
	GET_SINGLE(CParticleMgr)->DestroyInstance();
	GET_SINGLE(CCameraMgr)->DestroyInstance();
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
		return;
	}
}
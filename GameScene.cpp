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
#include"Inhibitor.h"
#include"Nexus.h"
#include"Turret.h"
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
	if (FAILED(AddMesh(GetDevice(), L"./Resource/Map/HowlingAbyss/", L"howling_Map.x", L"Map", MESHTYPE_STATIC)))
	{
		ERR_MSG(g_hWnd, L"Champion Load Failed");		return E_FAIL;
	}
	if (FAILED(AddMesh(GetDevice(), L"./Resource/choen/Tower/Blue_Turret/"
		, L"order_Turret.x", L"Blue_Turret", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"포탑로드 실패"); return E_FAIL;
	}
	if (FAILED(AddMesh(GetDevice(), L"./Resource/choen/Tower/inhibitor/"
		, L"inhibitor.x", L"Inhibitor", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"억제기 로드 실패"); return E_FAIL;
	}
	if (FAILED(AddMesh(GetDevice(), L"./Resource/choen/Tower/Nexus/"
		, L"Nexus.x", L"Nexus", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"넥서스 로드 실패"); return E_FAIL;
	}
#pragma region 객체 생성

	//>>객체 생성 
	if (FAILED(m_pObjMgr->AddObject(L"Map", CFactory<CObj, CSummonTerrain >::CreateObject())))
		return E_FAIL;
	if (FAILED(m_pObjMgr->AddObject(L"Ezreal", CFactory<CObj, CEzreal >::CreateObject())))
		return E_FAIL;	
	
	//////////////// 파랑팀 포탑

	{
		//터렛
		vector<CTurret*>	vecTurret(4);
		vecTurret[0] = (new CTurret(D3DXVECTOR3(23.f, 0.f, 22.5f))); vecTurret[0]->SetMeshName(L"Blue_Turret");
		vecTurret[1] = (new CTurret(D3DXVECTOR3(14.5f, 0.f, 14.3f)));vecTurret[1]->SetMeshName(L"Blue_Turret");
		vecTurret[2] = (new CTurret(D3DXVECTOR3(4.5f, 0.f, 0.9f)));	 vecTurret[2]->SetMeshName(L"Blue_Turret");
		vecTurret[3] = (new CTurret(D3DXVECTOR3(1.f, 0.f, 4.7f)));	 vecTurret[3]->SetMeshName(L"Blue_Turret");
		for (size_t i = 0; i < vecTurret.size(); i++)
		{
			vecTurret[i]->Initialize();
			GET_SINGLE(CObjMgr)->AddObject(L"Blue_Turret", vecTurret[i]);
		}
		//억제기
		CInhibitor*	pInhibitor = new CInhibitor(D3DXVECTOR3(9.5f, 0.f, 9.5f));
		pInhibitor->Initialize();
		GET_SINGLE(CObjMgr)->AddObject(L"Inhibitor", pInhibitor);
	
		CNexus*	pNexus = new CNexus(D3DXVECTOR3(0, 0, 0));
		pNexus->Initialize();
		GET_SINGLE(CObjMgr)->AddObject(L"Nexus", pNexus);
	}
#pragma endregion
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

	GET_SINGLE(CParticleMgr)->Progress();
	GET_SINGLE(CCollisionMgr)->Progress();
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
	//pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Ezreal2"));
	//if (pObj != nullptr) {
	//	dynamic_cast<CEzreal*>(pObj)->SetHeightMap(m_pHeightMap);
	//}

	return;
}
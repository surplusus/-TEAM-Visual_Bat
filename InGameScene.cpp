#include "BaseInclude.h"
#include "InGameScene.h"
#include "ResourceFunc.h"
#include "CameraMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "ThreadPool.h"
#include "Frustum.h"
#include "SoundMgr.h"
#include "EventMgr.h"
#include "HeightMap.h"
#include "GameHUD.h"
#include "Udyr.h"
#include "Ezreal.h"
#include "MinionMgr.h"
#include "MeleeMinion.h"
#include "Cursor.h"
#include"Factory.h"
#include"Inhibitor.h"
#include"Nexus.h"
#include"Turret.h"
#include"Cursor.h"
#include"CollisionMgr.h"
#include"ParticleMgr.h"
CInGameScene::CInGameScene()
{
	m_pObjMgr = GET_SINGLE(CObjMgr);
	m_pHeightMap = NULL;

}

CInGameScene::~CInGameScene()
{
}

HRESULT CInGameScene::Initialize()
{
	// 절두체 Setup
	GET_SINGLE(CFrustum)->InitFrustum();
	// Make Light
	//Setup_Light();
	// make Dynamic Camera
	if (FAILED(Setup_Camera()))
		return E_FAIL;
	// Make InGame UI
	GET_SINGLE(cGameHUD)->Initialize();
	{
		// 높이맵이 필요한 Object에게 eHightMap 포인터 알려주기
		LetObjectKnowHeightMap();
	}
	InitAsset();
	InitAddObject();
	return S_OK;
}

void CInGameScene::Progress()
{
	GET_SINGLE(CCameraMgr)->Progress();

	m_pObjMgr->Progress();

	GET_SINGLE(CParticleMgr)->Progress();
	GET_SINGLE(CCollisionMgr)->Progress();
	GET_SINGLE(cGameHUD)->Progress();
	SoundUpdate();
}

void CInGameScene::Render()
{
	SetRenderState(D3DRS_LIGHTING, false);
	m_pObjMgr->Render();
	GET_SINGLE(CParticleMgr)->Render();
	GET_SINGLE(CCollisionMgr)->Render();
	GET_SINGLE(cGameHUD)->Render();
}

void CInGameScene::Release()
{
	GET_SINGLE(CObjMgr)->Release();
	GET_SINGLE(CFrustum)->DestroyInstance();
	GET_SINGLE(CCameraMgr)->Release();
	GET_SINGLE(CCollisionMgr)->DestroyInstance();
	GET_SINGLE(CParticleMgr)->DestroyInstance();

	GET_SINGLE(cGameHUD)->Release();
}

HRESULT CInGameScene::Setup_Light()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.f);
	stLight.Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.f);
	stLight.Specular = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.f);
	D3DXVECTOR3 vDir(1.f, -1.f, 1.f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	GET_DEVICE->SetLight(0, &stLight);
	GET_DEVICE->LightEnable(0, true);
	GET_DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	SetRenderState(D3DRS_LIGHTING, true);
	return S_OK;
}

HRESULT CInGameScene::Setup_Camera()
{
	{	// Dynamic 카메라 
		if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(0.f, 10.f, -10.f)
			, D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
			, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))
			return E_FAIL;
	}
	return S_OK;
}

void CInGameScene::SoundUpdate()
{
	m_fSceneTime += GetTime();
	float time[3] = { 0.2f, 4.f, 5.f };
	if (GET_SINGLE(SoundMgr)->PlayOnTime(1.f, 1)) {
		GET_SINGLE(SoundMgr)->PlayAnnouncerMention(T_SOUND::ANNOUNCER_Welcome);
		cout << "소환사의 협곡에 오신것을 환영합니다." << endl;
	}
	if (GET_SINGLE(SoundMgr)->PlayOnTime(10.f, 2)) {
		GET_SINGLE(SoundMgr)->PlayAnnouncerMention(T_SOUND::ANNOUNCER_Left30sec);
		cout << "미니언 생성까지 30초 남았습니다." << endl;
	}
	GET_SINGLE(SoundMgr)->Update();
}

void CInGameScene::LetObjectKnowHeightMap()
{
	m_pHeightMap = new CHeightMap();
	m_pHeightMap->LoadData("./Resource/Map/HowlingAbyss/howling_HeightMap.x");
	CObj* pObj = nullptr;
	pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Udyr"));
	if (pObj != nullptr) {
		dynamic_cast<CUdyr*>(pObj)->SetHeightMap(m_pHeightMap);
		return;
	}
	pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Ezreal"));
	if (pObj != nullptr) {
		dynamic_cast<CEzreal*>(pObj)->SetHeightMap(m_pHeightMap);
		return;
	}
}

bool CInGameScene::InitAsset()
{
	if (FAILED(AddMesh(GetDevice(), L"./Resource/choen/Tower/Blue_Turret/"
		, L"order_Turret.x", L"Blue_Turret1", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"포탑로드 실패"); return E_FAIL;
	}
	if (FAILED(AddMesh(GetDevice(), L"./Resource/choen/Tower/Blue_Turret/"
		, L"order_Turret.x", L"Blue_Turret2", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"포탑로드 실패"); return E_FAIL;
	}
	if (FAILED(AddMesh(GetDevice(), L"./Resource/choen/Tower/Blue_Turret/"
		, L"order_Turret.x", L"Blue_Turret3", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"포탑로드 실패"); return E_FAIL;
	}
	if (FAILED(AddMesh(GetDevice(), L"./Resource/choen/Tower/Blue_Turret/"
		, L"order_Turret.x", L"Blue_Turret4", MESHTYPE_DYNAMIC)))
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
}

bool CInGameScene::InitAddObject()
{
	//터렛
	vector<CTurret*>	vecTurret(4);
	vecTurret[0] = (new CTurret(D3DXVECTOR3(23.f, 0.f, 22.5f), L"order_outer_Turret", 50.0f)); vecTurret[0]->SetMeshName(L"Blue_Turret1");
	vecTurret[1] = (new CTurret(D3DXVECTOR3(14.5f, 0.f, 14.3f), L"order_iner_Turret", 50.0f));vecTurret[1]->SetMeshName(L"Blue_Turret2");
	vecTurret[2] = (new CTurret(D3DXVECTOR3(4.5f, 0.f, 0.9f), L"order_twins_left_Turret", 50.0f));	 vecTurret[2]->SetMeshName(L"Blue_Turret3");
	vecTurret[3] = (new CTurret(D3DXVECTOR3(1.f, 0.f, 4.7f), L"order_twins_right_Turret", 50.0f));	 vecTurret[3]->SetMeshName(L"Blue_Turret4");
	for (size_t i = 0; i < vecTurret.size(); i++)
	{
		vecTurret[i]->Initialize();
	}

	GET_SINGLE(CObjMgr)->AddObject(L"order_outer_Turret", vecTurret[0]);
	GET_SINGLE(CObjMgr)->AddObject(L"order_iner_Turret", vecTurret[1]);
	GET_SINGLE(CObjMgr)->AddObject(L"order_twins_left_Turret", vecTurret[2]);
	GET_SINGLE(CObjMgr)->AddObject(L"order_twins_right_Turret", vecTurret[3]);
	//억제기
	CInhibitor*	pInhibitor = new CInhibitor(D3DXVECTOR3(9.5f, 0.f, 9.5f));
	pInhibitor->Initialize();
	GET_SINGLE(CObjMgr)->AddObject(L"Inhibitor", pInhibitor);

	CNexus*	pNexus = new CNexus(D3DXVECTOR3(0, 0, 0));
	pNexus->Initialize();
	GET_SINGLE(CObjMgr)->AddObject(L"Nexus", pNexus);

	LetObjectKnowHeightMap();
	m_pCursor = new CCursor;
	m_pCursor->InitCursor();
	m_pCursor->SetCursor(CCursor::CURSORTYPE::CURSORTYPE_INGAME);
	GET_SINGLE(cGameHUD)->Initialize();
	return true;
}


void CInGameScene::GetMinionMgr(void ** pMinionMgr)
{
	m_pMinionMgr = reinterpret_cast<CMinionMgr*>(*pMinionMgr);
}

void CInGameScene::GetCursor(void ** pCursor)
{
	m_pCursor = reinterpret_cast<CCursor*>(*pCursor);
}

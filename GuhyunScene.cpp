#include "BaseInclude.h"
#include "GuhyunScene.h"
#include "ResourceFunc.h"
#include "CameraMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "Frustum.h"
#include "EventMgr.h"
#include "HeightMap.h"
#include "GameHUD.h"
#include "CollisionMgr.h"
#include "ParticleMgr.h"
#include "Cursor.h"
#include "SoundMgr.h"
#include "Udyr.h"
#include "Ezreal.h"
#include "MinionMgr.h"
#include "Factory.h"
#include "SummonTerrain.h"

GuhyunScene::GuhyunScene()
{
	m_pObjMgr = (GET_SINGLE(CObjMgr));
}

GuhyunScene::~GuhyunScene()
{
}

HRESULT GuhyunScene::Initialize()
{
	//if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(-15.f, 30.f, -20.f)
	if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(0.f, 10.f, -10.f)
		, D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))
		return E_FAIL;

	if (Setup())		// light off
		return E_FAIL;

	LetObjectKnowHeightMap();

	m_pCursor->SetCursor(CCursor::CURSORTYPE::CURSORTYPE_INGAME);

	return S_OK;
}

void GuhyunScene::Progress()
{
	if (m_pMinionMgr)
		m_pMinionMgr->Progress();
	m_pObjMgr->Progress();

	GET_SINGLE(CCameraMgr)->Progress();
	GET_SINGLE(CFrustum)->InitFrustum();
	GET_SINGLE(CCollisionMgr)->Progress();
	GET_SINGLE(CParticleMgr)->Progress();
	SoundUpdate();
}

void GuhyunScene::Render()
{
	if (m_pMinionMgr)
		m_pMinionMgr->Render();
	m_pObjMgr->Render();
	GET_SINGLE(CCollisionMgr)->Render();
	GET_SINGLE(CParticleMgr)->Render();
	//m_pHeightMap->Render();
}

void GuhyunScene::Release()
{
	GET_SINGLE(CObjMgr)->Release();
	GET_SINGLE(CFrustum)->DestroyInstance();
	SAFE_DELETE(m_pMinionMgr);
	GET_SINGLE(CCameraMgr)->Release();
	SAFE_DELETE(m_pHeightMap);
}

HRESULT GuhyunScene::Setup()
{
	// Make Light
	SetUp_Light();
	return S_OK;
}

void GuhyunScene::SetUp_Light()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.f);
	stLight.Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.f);
	stLight.Specular = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.f);
	D3DXVECTOR3 vDir(1.f, 1.f, 1.f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	GET_DEVICE->SetLight(0, &stLight);
	GET_DEVICE->LightEnable(0, true);
	GET_DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	SetRenderState(D3DRS_LIGHTING, true);
}

void GuhyunScene::SoundUpdate()
{
	m_fSceneTime += GetTime();
	float time[3] = { 0.2f, 4.f, 5.f };
	//if (GET_SINGLE(SoundMgr)->PlayOnTime(1.f, 1)) {
	//	GET_SINGLE(SoundMgr)->PlayAnnouncerMention("welcome");
	//	cout << "소환사의 협곡에 오신것을 환영합니다." << endl;
	//}
	//if (GET_SINGLE(SoundMgr)->PlayOnTime(10.f, 2)) {
	//	GET_SINGLE(SoundMgr)->PlayAnnouncerMention("left30sec");
	//	cout << "미니언 생성까지 30초 남았습니다." << endl;
	//}
	//
	//if (GET_SINGLE(SoundMgr)->PlayOnTime(40.f, 3)) {
	//	GET_SINGLE(SoundMgr)->PlayAnnouncerMention("createminion");
	//	cout << "미니언이 생성되었습니다." << endl;
	//}
	GET_SINGLE(SoundMgr)->Update();
}

void GuhyunScene::LetObjectKnowHeightMap()
{
	m_pHeightMap = new CHeightMap();
	m_pHeightMap->LoadData("./Resource/Map/HowlingAbyss/howling_HeightMap.x");
	// for Minion
	m_pMinionMgr->SetHeightMap(&m_pHeightMap);
	// for Champion
	CObj* pObj = nullptr;
	pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Udyr"));
	if (pObj != nullptr) {
		dynamic_cast<CUdyr*>(pObj)->SetHeightMap(m_pHeightMap);
	}
	pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Ezreal"));
	if (pObj != nullptr) {
		dynamic_cast<CEzreal*>(pObj)->SetHeightMap(m_pHeightMap);
	}
}

void GuhyunScene::GetMinionMgr(void ** pMinionMgr)
{
	m_pMinionMgr = reinterpret_cast<CMinionMgr*>(*pMinionMgr);
}

void GuhyunScene::GetCursor(void ** pCursor)
{
	m_pCursor = reinterpret_cast<CCursor*>(*pCursor);
}

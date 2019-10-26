#include "BaseInclude.h"
#include "InGameScene.h"
#include "ResourceFunc.h"
#include "CameraMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "SceneMgr.h"
#include "ThreadPool.h"
#include "Frustum.h"
#include "SoundManager.h"
#include "EventMgr.h"
#include "HeightMap.h"
#include "GameHUD.h"
#include "SummonTerrain.h"
#include "Udyr.h"
#include "MinionMgr.h"
#include "MeleeMinion.h"

CInGameScene::CInGameScene()
{
	m_pObjMgr = GET_SINGLE(CObjMgr);
}

CInGameScene::~CInGameScene()
{
}

HRESULT CInGameScene::Initialize()
{
	// Set InGame Sound
	GET_SINGLE(SoundManager)->SetUp();
	// 절두체 Setup
	GET_SINGLE(CFrustum)->InitFrustum();
	// Make Light
	Setup_Light();
	// make Dynamic Camera
	if (FAILED(Setup_Camera()))
		return E_FAIL;
	// Make InGame UI
	GET_SINGLE(cGameHUD)->Initialize();

	// 높이맵이 필요한 Object에게 HeightMap 포인터 알려주기
	LetObjectKnowHeightMap();

	return S_OK;
}

void CInGameScene::Progress()
{
	GET_SINGLE(cGameHUD)->Progress();
	GET_SINGLE(CCameraMgr)->Progress();
	m_pObjMgr->Progress();

	SoundUpdate();
}

void CInGameScene::Render()
{
	GET_SINGLE(cGameHUD)->Render();
	m_pObjMgr->Render();
}

void CInGameScene::Release()
{
	GET_SINGLE(CObjMgr)->Release();
	GET_SINGLE(CFrustum)->DestroyInstance();
	GET_SINGLE(CCameraMgr)->Release();
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
	if (GET_SINGLE(SoundManager)->PlayOnTime(1.f, 1)) {
		GET_SINGLE(SoundManager)->PlayAnnouncerMention("welcome");
		cout << "소환사의 협곡에 오신것을 환영합니다." << endl;
	}
	if (GET_SINGLE(SoundManager)->PlayOnTime(10.f, 2)) {
		GET_SINGLE(SoundManager)->PlayAnnouncerMention("left30sec");
		cout << "미니언 생성까지 30초 남았습니다." << endl;
	}
	GET_SINGLE(SoundManager)->Update();
}

void CInGameScene::LetObjectKnowHeightMap()
{
	m_pHeightMap = new CHeightMap();
	m_pHeightMap->LoadData("./Resource/howling/howling_HeightMap.x");
	CObj* pObj = nullptr;
	pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Udyr"));
	if (pObj != nullptr)
		dynamic_cast<CUdyr*>(pObj)->SetHeightMap(m_pHeightMap);
	pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Zealot"));
	if (pObj != nullptr)
		dynamic_cast<CUdyr*>(pObj)->SetHeightMap(m_pHeightMap);
}

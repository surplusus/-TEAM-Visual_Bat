#include "BaseInclude.h"
#include "InGameScene.h"
#include "ResourceFunc.h"
#include "CameraMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "Frustum.h"
#include "SoundMgr.h"
#include "EventMgr.h"
#include "HeightMap.h"
#include "GameHUD.h"
#include "MinionMgr.h"
#include "Cursor.h"
#include "CollisionMgr.h"
#include "ParticleMgr.h"
#include "Champion.h"
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
	// ����ü Setup
	//GET_SINGLE(CFrustum)->InitFrustum();
	// Make Light
	//Setup_Light();
	// make Dynamic Camera
	if (FAILED(Setup_Camera()))
		return E_FAIL;
	// Make InGame UI
	GET_SINGLE(cGameHUD)->Initialize();
	// ���̸��� �ʿ��� Object���� eHightMap ������ �˷��ֱ�
	LetObjectKnowHeightMap();
	// Ŀ�� �ٽ� ����
	m_pCursor->SetCursor(CCursor::CURSORTYPE::CURSORTYPE_INGAME);
	return S_OK;
}

void CInGameScene::Progress()
{
	GET_SINGLE(CCameraMgr)->Progress();
	//GET_SINGLE(CFrustum)->InitFrustum();

	RECT r;
	//GetWindowRect(g_hWnd, &r);
	GetClientRect(g_hWnd, &r);
	ClipCursor(&r);

	m_pObjMgr->Progress();
	if (m_pMinionMgr)
		m_pMinionMgr->Progress();

	GET_SINGLE(CParticleMgr)->Progress();
	GET_SINGLE(CCollisionMgr)->Progress();
	GET_SINGLE(cGameHUD)->Progress();

	SoundUpdate();
}

void CInGameScene::Render()
{
	m_pObjMgr->Render();
	if (m_pMinionMgr)
		m_pMinionMgr->Progress();
	if (CheckPushKeyOneTime(VK_C))
	{
		GET_SINGLE(CParticleMgr)->Render();
		GET_SINGLE(CCollisionMgr)->Render();
	}
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
	SAFE_DELETE(m_pMinionMgr);
	SAFE_DELETE(m_pHeightMap);
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
	{	// Dynamic ī�޶� 
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
		cout << "��ȯ���� ��� ���Ű��� ȯ���մϴ�." << endl;
	}
	if (GET_SINGLE(SoundMgr)->PlayOnTime(10.f, 2)) {
		GET_SINGLE(SoundMgr)->PlayAnnouncerMention(T_SOUND::ANNOUNCER_Createminion);
		cout << "�̴Ͼ� �����Ǿ����ϴ�." << endl;
	}
	GET_SINGLE(SoundMgr)->Update();
}

void CInGameScene::LetObjectKnowHeightMap()
{
	m_pHeightMap = new CHeightMap();
	m_pHeightMap->LoadData("./Resource/Map/HowlingAbyss/howling_HeightMap.x");
	// for Minion
	if (m_pMinionMgr != nullptr)
		m_pMinionMgr->SetHeightMap(&m_pHeightMap);
	CObj* pObj = nullptr;
	pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Udyr"));
	if (pObj != nullptr) {
		dynamic_cast<CChampion*>(pObj)->SetHeightMap(m_pHeightMap);
		return;
	}
	pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Ezreal"));
	if (pObj != nullptr) {
		dynamic_cast<CChampion*>(pObj)->SetHeightMap(m_pHeightMap);
		return;
	}
}

void CInGameScene::GetMinionMgr(void ** pMinionMgr)
{
	m_pMinionMgr = reinterpret_cast<CMinionMgr*>(*pMinionMgr);
}

void CInGameScene::GetCursor(void ** pCursor)
{
	m_pCursor = reinterpret_cast<CCursor*>(*pCursor);
}

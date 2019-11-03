#include "BaseInclude.h"
#include "GuhyunScene.h"
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


	//=========== Subscribe Events ==========//
	//GET_SINGLE(EventMgr)->Subscribe(this, &GuhyunScene::RegisterMapLoaded);

	#pragma region ���� LoadingScene �κ����� ����
	//=========== Add Mesh(Bounding) ===========//
	//if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
	//{
	//	ERR_MSG(g_hWnd, L"BoundingBox Load Failed");		return E_FAIL;
	//}
	//=========== Add Texture ===========//

	//=========== Add Mesh(static or dynamic) ===========//

	if (SUCCEEDED(AddMesh(GetDevice(), L"./Resource/Test/", L"TestFloor.x", L"Map", MESHTYPE_STATIC))) {
		if (FAILED(GET_SINGLE(CObjMgr)->AddObject(L"Map_Floor", CFactory<CObj, CSummonTerrain >::CreateObject())))
			ERR_MSG(g_hWnd, L"Fail : Register On ObjMgr");
	}
	else
		ERR_MSG(g_hWnd, L"MapSummon Load Failed");
		
	if (SUCCEEDED(AddMesh(GetDevice(), L"./Resource/Test/", L"Udyr.x", L"Udyr", MESHTYPE_DYNAMIC))) {
		if (FAILED(GET_SINGLE(CObjMgr)->AddObject(L"Udyr", CFactory<CObj, CUdyr>::CreateObject())))
			ERR_MSG(g_hWnd, L"Fail : Register On ObjMgr");
	}
	else
		ERR_MSG(g_hWnd, L"Udyr Load Failed");

	//=========== Add Shader ===========//
	
	//=========== Add Object ===========//	

	//=========== Add Particle ===========//	
	#pragma endregion

	// ���̸��� �ʿ��� Object���� HeightMap ������ �˷��ֱ�
	LetObjectKnowHeightMap();
	m_pMinionMgr = new CMinionMgr();
	m_pMinionMgr->CreateMinions();
	//HRESULT res;
	//m_pMinion = new CMeleeMinion();
	//if (SUCCEEDED(AddMesh(GetDevice(), L"./Resource/Test/", L"Minion_Melee_Blue.x", L"Minion", MESHTYPE_DYNAMIC))) {
	//	if (FAILED(GET_SINGLE(CObjMgr)->AddObject(L"Minion", m_pMinion)))
	//		ERR_MSG(g_hWnd, L"Fail : Register On ObjMgr");
	//	m_pMinion->Initialize();
	//}
	//else
	//	ERR_MSG(g_hWnd, L"Udyr Load Failed");

	return S_OK;
}

void GuhyunScene::Progress()
{
	if (m_pMinionMgr)
		m_pMinionMgr->Progress();
	m_pObjMgr->Progress();

	GET_SINGLE(CCameraMgr)->Progress();
	GET_SINGLE(CFrustum)->InitFrustum();
	
	SoundUpdate();
}

void GuhyunScene::Render()
{
	if (m_pMinionMgr)
		m_pMinionMgr->Render();
	m_pObjMgr->Render();
	//m_pHeightMap->Render();
	//Bound_Render(BOUNDTYPE::BOUNDTYPE_SPHERE);
}

void GuhyunScene::Release()
{
	GET_SINGLE(CObjMgr)->Release();
	GET_SINGLE(CFrustum)->DestroyInstance();
	SAFE_DELETE(m_pMinionMgr);
	GET_SINGLE(CCameraMgr)->Release();
	SAFE_DELETE(m_pHeightMap);
	//GET_SINGLE(EventMgr)->Unsubscribe(this, &GuhyunScene::RegisterMapLoaded);
}

HRESULT GuhyunScene::Setup()
{
	{	// Make Light
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
	}
	return S_OK;
}

void GuhyunScene::SoundUpdate()
{
	m_fSceneTime += GetTime();
	float time[3] = { 0.2f, 4.f, 5.f };
	//if (GET_SINGLE(SoundMgr)->PlayOnTime(1.f, 1)) {
	//	GET_SINGLE(SoundMgr)->PlayAnnouncerMention("welcome");
	//	cout << "��ȯ���� ��� ���Ű��� ȯ���մϴ�." << endl;
	//}
	//if (GET_SINGLE(SoundMgr)->PlayOnTime(10.f, 2)) {
	//	GET_SINGLE(SoundMgr)->PlayAnnouncerMention("left30sec");
	//	cout << "�̴Ͼ� �������� 30�� ���ҽ��ϴ�." << endl;
	//}
	//
	//if (GET_SINGLE(SoundMgr)->PlayOnTime(40.f, 3)) {
	//	GET_SINGLE(SoundMgr)->PlayAnnouncerMention("createminion");
	//	cout << "�̴Ͼ��� �����Ǿ����ϴ�." << endl;
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
		return;
	}
	pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Ezreal"));
	if (pObj != nullptr) {
		dynamic_cast<CEzreal*>(pObj)->SetHeightMap(m_pHeightMap);
		return;
	}
	pObj = const_cast<CObj*>(m_pObjMgr->GetObj(L"Zealot"));
	if (pObj != nullptr)
		dynamic_cast<CUdyr*>(pObj)->SetHeightMap(m_pHeightMap);
}

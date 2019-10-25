#include "BaseInclude.h"
#include "GuhyunScene.h"
#include "XFileUtil.h"
#include "ResourceFunc.h"
#include "CameraMgr.h"
#include "Factory.h"
#include "ObjMgr.h"
#include "SkyBox.h"
#include "SceneMgr.h"
#include "GameScene.h"
#include "ThreadPool.h"
#include "Frustum.h"
#include <sstream>

#include "SoundManager.h"
#include "Amumu.h"
#include "Zealot.h"
#include "Udyr.h"
#include "SummonTerrain.h"
#include "EventMgr.h"
#include "MinionMgr.h"
#include "HeightMap.h"
#include "LoadingScene.h"
#include "SceneMediator.h"


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

	//=========== Add Mesh(Bounding) ===========//
	if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
	{
		ERR_MSG(g_hWnd, L"BoundingBox Load Failed");		return E_FAIL;
	}
	#pragma region 이제 스레스 부분으로 갔음
	//=========== Add Texture ===========//
	//if (FAILED(InsertTexture(GetDevice()
	//	, TEXTYPE_CUBE
	//	, L"./Resource/SkyBox/Berger%d.dds"
	//	, L"SkyBox", L"Cube", 3)))
	//{
	//	ERR_MSG(g_hWnd, L"Texture Create Failed");
	//	return E_FAIL;
	//}

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
	//m_minion = new MinionMgr();

		// 스레드 돌려서 맵 로딩
	//LoadResourceByThread();
	m_pHeightMap = new CHeightMap();
	m_pHeightMap->LoadData("./Resource/Test/MapHeight.x");
	dynamic_cast<CUdyr*>(const_cast<CObj*>(m_pObjMgr->GetObj(L"Udyr")))->SetHeightMap(m_pHeightMap);
	return S_OK;
}

void GuhyunScene::Progress()
{
	if (CheckPushKeyOneTime(VK_ESCAPE)) {
		//GET_SINGLE(CSceneMgr)->SetState(new CGameScene);
		PostMessage(NULL, WM_QUIT, 0, 0);
		return;
	}
	
	//if (CheckPushKeyOneTime(VK_0))
	//	GET_SINGLE(EventMgr)->Publish(new ANNOUNCEEVENT());
	m_pObjMgr->Progress();

	GET_SINGLE(CCameraMgr)->Progress();
	GET_SINGLE(CFrustum)->InitFrustum();
	
	SoundUpdate();
}

void GuhyunScene::Render()
{
	m_pObjMgr->Render();
	//m_pHeightMap->Render();
	//Bound_Render(BOUNDTYPE::BOUNDTYPE_SPHERE);
}

void GuhyunScene::Release()
{
	GET_SINGLE(CObjMgr)->Release();
	GET_SINGLE(CFrustum)->DestroyInstance();
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
	{	// Set InGame Sound
		GET_SINGLE(SoundManager)->SetUp();
	}

	return S_OK;
}

void GuhyunScene::SoundUpdate()
{
	m_fSceneTime += GetTime();
	float time[3] = { 0.2f, 4.f, 5.f };
	//if (GET_SINGLE(SoundManager)->PlayOnTime(1.f, 1)) {
	//	GET_SINGLE(SoundManager)->PlayAnnouncerMention("welcome");
	//	cout << "소환사의 협곡에 오신것을 환영합니다." << endl;
	//}
	//if (GET_SINGLE(SoundManager)->PlayOnTime(10.f, 2)) {
	//	GET_SINGLE(SoundManager)->PlayAnnouncerMention("left30sec");
	//	cout << "미니언 생성까지 30초 남았습니다." << endl;
	//}
	//
	//if (GET_SINGLE(SoundManager)->PlayOnTime(40.f, 3)) {
	//	GET_SINGLE(SoundManager)->PlayAnnouncerMention("createminion");
	//	cout << "미니언이 생성되었습니다." << endl;
	//}
	GET_SINGLE(SoundManager)->Update();
}
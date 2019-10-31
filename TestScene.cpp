#include "BaseInclude.h"
#include "TestScene.h"
#include "XFileUtil.h"
#include "ResourceFunc.h"
#include "CameraMgr.h"
#include "Factory.h"
#include "ObjMgr.h"
#include "SkyBox.h"
#include "SceneMgr.h"
#include "GameScene.h"
#include "ThreadPool.h"
#include <sstream>

#include "SoundMgr.h"
#include "Amumu.h"
#include "Zealot.h"
#include "SummonTerrain.h"
#include "EventMgr.h"
#include "MinionMgr.h"
#include "HeightMap.h"
#include "LoadingScene.h"
#include "SceneMediator.h"


CTestScene::CTestScene()
{
	m_pObjMgr = GET_SINGLE(CObjMgr);
}


CTestScene::~CTestScene()
{
}

HRESULT CTestScene::Initialize()
{
	if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(0.f, 10.f, -10.f)
		, D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))
		return E_FAIL;
	
	if (Setup())
		return E_FAIL;

	//========= SubScribe Events ===========//(이벤트 구독)
	//GET_SINGLE(EventMgr)->Subscribe(this, &GuhyunScene::RegisterMapLoaded);

	//========= Add Mesh(Bounding) ========//
	if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
	{
		ERR_MSG(g_hWnd, L"BoundingBox Load Failed");
		return E_FAIL;
	}
#pragma region 이제 스레스 부분으로 갔음
	// ======== Add Texture ========== //
	

	// ========= Add Mesh(static or dynamic) ============ //
	if (SUCCEEDED(AddMesh(GetDevice(), L"./Resource/Test/", L"TestFloor.x", L"Map", MESHTYPE_STATIC)))
		GET_SINGLE(CObjMgr)->AddObject(L"Map_Floor", CFactory<CObj, CSummonTerrain >::CreateObject());
	else
		ERR_MSG(g_hWnd, L"MapSummon Load Failed");


	if (SUCCEEDED(AddMesh(GetDevice(), L"./Resource/Zealot/"
		, L"zealot.x", L"Zealot", MESHTYPE_DYNAMIC)))
		GET_SINGLE(CObjMgr)->AddObject(L"Zealot", CFactory<CObj, CZealot>::CreateObject());
	else
		ERR_MSG(g_hWnd, L"Zealot Load Failed");

	return S_OK;
}

void CTestScene::Progress()
{
	GET_SINGLE(CCameraMgr)->Progress();

	m_pObjMgr->Progress();
}

void CTestScene::Render()
{
	m_pObjMgr->Render();
}

void CTestScene::Release()
{
	m_pObjMgr->Release();
}

HRESULT CTestScene::Setup()
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

void CTestScene::SoundUpdate()
{
}

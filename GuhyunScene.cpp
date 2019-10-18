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

#include "SoundManager.h"
#include "Amumu.h"
#include "Zealot.h"
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
	GET_SINGLE(SoundManager)->SetUp();


	//=========== Add Texture ===========//
	//if (FAILED(InsertTexture(GetDevice()
	//	, TEXTYPE_CUBE
	//	, L"./Resource/SkyBox/Berger%d.dds"
	//	, L"SkyBox", L"Cube", 3)))
	//{
	//	ERR_MSG(g_hWnd, L"Texture Create Failed");
	//	return E_FAIL;
	//}
	//if (FAILED(AddMesh(GetDevice(), L"./Resource/MapSummon/", L"Floor.x", L"Map", MESHTYPE_STATIC)))
	//{
	//	ERR_MSG(g_hWnd, L"Summon Map_Floor Load Failed");		return E_FAIL;
	//}
	if (FAILED(AddMesh(GetDevice(), L"./Resource/Test/", L"TestFloor.x", L"Map", MESHTYPE_STATIC)))
	{
		ERR_MSG(g_hWnd, L"Summon Map_Floor Load Failed");		return E_FAIL;
	}
	//=========== Add Mesh(static or dynamic) ===========//
	if (FAILED(AddMesh(GetDevice(), L"./Resource/Zealot/"
		, L"zealot.x", L"Zealot", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"zealot Load Failed");
	}

	//=========== Add Mesh(Bounding) ===========//
	if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
	{
		ERR_MSG(g_hWnd, L"BoundingSphere Load Failed");		return E_FAIL;
	}

	//=========== Add Shader ===========//

	//=========== Add Object ===========//	
	if (FAILED(m_pObjMgr->AddObject(L"Map_Floor", CFactory<CObj, CSummonTerrain >::CreateObject())))
		return E_FAIL;
	if (FAILED(m_pObjMgr->AddObject(L"Zealot", CFactory<CObj, CZealot>::CreateObject())))
	{
		ERR_MSG(g_hWnd, L"Zealot Load Failed");
	}


	//=========== Add Particle ===========//	


	return S_OK;
}

void GuhyunScene::Progress()
{
	if (CheckPushKeyOneTime(VK_ESCAPE)) {
		//GET_SINGLE(CSceneMgr)->SetState(new GameScene);
		PostMessage(NULL, WM_QUIT, 0, 0);
		return;
	}

	GET_SINGLE(CCameraMgr)->Progress();
	m_pObjMgr->Progress();
	//SoundUpdate();
	//cout << "Get Time : " << GetTime() << " g_fdeltaTime : " << g_fDeltaTime << endl;
}

void GuhyunScene::Render()
{
	m_pObjMgr->Render();
	//Bound_Render(BOUNDTYPE::BOUNDTYPE_SPHERE);
}

void GuhyunScene::Release()
{
	GET_SINGLE(CObjMgr)->Release();
}

HRESULT GuhyunScene::Setup()
{

	SetRenderState(D3DRS_LIGHTING, false);
	return S_OK;
}

void GuhyunScene::Update()
{
	m_pObjMgr->Progress();
	GET_SINGLE(CCameraMgr)->Progress();
}

void GuhyunScene::SoundUpdate()
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
	
	if (GET_SINGLE(SoundManager)->PlayOnTime(40.f, 3)) {
		GET_SINGLE(SoundManager)->PlayAnnouncerMention("createminion");
		cout << "미니언이 생성되었습니다." << endl;
	}
	GET_SINGLE(SoundManager)->Update();
}

void GuhyunScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

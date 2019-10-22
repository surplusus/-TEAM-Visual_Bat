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
#include <sstream>

#include "SoundManager.h"
#include "Amumu.h"
#include "Zealot.h"
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
	GET_SINGLE(EventMgr)->Subscribe(this, &GuhyunScene::RegisterMapLoaded);

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

	//if (SUCCEEDED(AddMesh(GetDevice(), L"./Resource/Test/", L"TestFloor.x", L"Map", MESHTYPE_STATIC)))
	//	GET_SINGLE(CObjMgr)->AddObject(L"Map_Floor", CFactory<CObj, CSummonTerrain >::CreateObject());
	//else
	//	ERR_MSG(g_hWnd, L"MapSummon Load Failed");
	//
	//
	//if (SUCCEEDED(AddMesh(GetDevice(), L"./Resource/Zealot/"
	//	, L"zealot.x", L"Zealot", MESHTYPE_DYNAMIC)))
	//	GET_SINGLE(CObjMgr)->AddObject(L"Zealot", CFactory<CObj, CZealot>::CreateObject());
	//else
	//	ERR_MSG(g_hWnd, L"Zealot Load Failed");

	//=========== Add Shader ===========//
	
	//=========== Add Object ===========//	
	//if (FAILED(m_pObjMgr->AddObject(L"Map_Floor", CFactory<CObj, CSummonTerrain >::CreateObject())))
	//	ERR_MSG(g_hWnd, L"Test Floor Load Failed");
	//if (FAILED(m_pObjMgr->AddObject(L"Zealot", CFactory<CObj, CZealot>::CreateObject())))
	//{
	//	ERR_MSG(g_hWnd, L"Zealot Load Failed");
	//}

	//=========== Add Particle ===========//	

	#pragma endregion
	//m_minion = new MinionMgr();

		// 스레드 돌려서 맵 로딩
	//LoadResourceByThread();
	m_pHeightMap = new CHeightMap();
	m_pHeightMap->LoadData("./Resource/Test/MapHeight.x");
	return S_OK;
}

void GuhyunScene::Progress()
{
	if (CheckPushKeyOneTime(VK_ESCAPE)) {
		//GET_SINGLE(CSceneMgr)->SetState(new CGameScene);
		PostMessage(NULL, WM_QUIT, 0, 0);
		return;
	}
	
	if (m_bLoading)
		m_pLoadingScene->Progress();

	//if (CheckPushKeyOneTime(VK_0))
	//	GET_SINGLE(EventMgr)->Publish(new ANNOUNCEEVENT());

	if (CheckPushKeyOneTime(VK_SPACE))
		m_bLoading = false;
	GET_SINGLE(CCameraMgr)->Progress();

	for (auto& it : m_vFuncRegister) {
		//ProcessRegisterMapLoaded(it);

	}
	m_vFuncRegister.clear();
	m_pObjMgr->Progress();
	
	SoundUpdate();
}

void GuhyunScene::Render()
{
	if (m_bLoading) {
		m_pLoadingScene->Render();
		return;
	}
	m_pObjMgr->Render();
	//m_pHeightMap->Render();
	//Bound_Render(BOUNDTYPE::BOUNDTYPE_SPHERE);
}

void GuhyunScene::Release()
{
	GET_SINGLE(CObjMgr)->Release();
	GET_SINGLE(EventMgr)->Unsubscribe(this, &GuhyunScene::RegisterMapLoaded);
}

HRESULT GuhyunScene::Setup()
{
	{	// Insert in SceneMediator
		GET_SINGLE(CSceneMgr)->GetSceneMediator()->SetSceneMember(typeid(this).name(),this);
	}
	{	// Immediately Render LoadingScene
		Begin_Render();
		m_pLoadingScene = new CLoadingScene();
		m_pLoadingScene->Initialize();
		m_pLoadingScene->Render();
		End_Render(g_hWnd);
	}
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

void GuhyunScene::RegisterMapLoaded(REGISTEREVENT * evt)
{
	//vector<string> sResult(*(evt->m_result));
	//size_t nSize = evt->m_result->size();
	string sResult = *evt->m_result;
	delete evt->m_result;
	delete evt;

	bool bResult = false;
	stringstream ss;
	string strResult, strName, strType, dump;
	ss << sResult;
	ss >> strName >> dump >> strResult;
	ss.str("");
	bResult = (strResult[0] == 'C') ? true : false;
	stEventInfo queMem = { bResult,strName};
	m_vFuncRegister.push_back(queMem);
		
	cout << sResult << '\n';
}

void GuhyunScene::RegisterMapLoaded(string sLoadResult)
{
	bool bResult = false;
	stringstream ss;
	string strResult, strName, strType, dump;
	ss << sLoadResult;
	ss >> strName >> dump >> strResult;
	ss.str("");
	bResult = (strResult[0] == 'C') ? true : false;
	stEventInfo queMem = { bResult,strName };
	m_vFuncRegister.push_back(queMem);

	cout << sLoadResult << '\n';
}

//void GuhyunScene::ProcessRegisterMapLoaded(stEventInfo evtInfo)
//{
//	if (!evtInfo.m_bComplate)
//		return;
//
//	basic_string<TCHAR> converted(evtInfo.m_sObjName.begin(), evtInfo.m_sObjName.end());
//	const TCHAR * szName = converted.c_str();
//
//
//	if (evtInfo.m_sObjName == "MapSummon" || evtInfo.m_sObjName == "Floor") {
//		GET_SINGLE(CObjMgr)->AddObject(szName, CFactory<CObj, CSummonTerrain >::CreateObject());
//		cout << evtInfo.m_sObjName << " Register Complited\n";
//	}
//	else if (evtInfo.m_sObjName == "Zealot" || evtInfo.m_sObjName == "Udyr") {
//		GET_SINGLE(CObjMgr)->AddObject(szName, CFactory<CObj, CZealot>::CreateObject());
//		cout << evtInfo.m_sObjName << " Register Complited\n";
//	
//		CZealot* zealot = (CZealot*)(m_pObjMgr->GetObj(L"Zealot"));
//		zealot->SetHeightMap(m_pHeightMap);
//	}
//
//}
//
//string GuhyunScene::AddStaticMeshByThread(string path, string fileName, string objName)
//{
//	basic_string<TCHAR> sTemp1(path.begin(), path.end());
//	basic_string<TCHAR> sTemp2(fileName.begin(), fileName.end());
//	basic_string<TCHAR> sTemp3(objName.begin(), objName.end());
//	string result;
//	const TCHAR* t1 = sTemp1.c_str();
//	const TCHAR* t2 = sTemp1.c_str();
//	const TCHAR* t3 = sTemp1.c_str();
//	if (SUCCEEDED(AddMesh(GetDevice(), t1, t2, t3, MESHTYPE_STATIC)))
//		result = sTemp3 + " Load Complited";
//	else
//		result = sTemp3 + " Load Failed";
//
//	return result;
//}
//
//string GuhyunScene::AddDynamicMeshByThread(string path, string fileName, string objName)
//{
//	basic_string<TCHAR> sTemp1(path.begin(), path.end());
//	basic_string<TCHAR> sTemp2(fileName.begin(), fileName.end());
//	basic_string<TCHAR> sTemp3(objName.begin(), objName.end());
//	string result;
//	const TCHAR* t1 = sTemp1.c_str();
//	const TCHAR* t2 = sTemp1.c_str();
//	const TCHAR* t3 = sTemp1.c_str();
//	//if (SUCCEEDED(AddMesh(GetDevice(), sTemp1.c_str(), sTemp2.c_str(), sTemp3.c_str(), MESHTYPE_DYNAMIC)))
//	if (SUCCEEDED(AddMesh(GetDevice(), t1, t2, t3, MESHTYPE_DYNAMIC)))
//		result = sTemp3 + " Load Complited";
//	else
//		result = sTemp3 + " Load Failed";
//
//	return result;
//}
//
//bool GuhyunScene::LoadResourceByThread()
//{
//	bool result = true;
//	string sPath, sFileName, sObjName, sResult;
//	sPath = "./Resource/Test/Map/";
//	sFileName = "MapSummon.x";
//	sObjName = "Map";
//	m_vThreadCompleted.push_back(false);
//	
//	sResult = GET_THREADPOOL->EnqueueFunc(THREAD_LOADMAP, AddStaticMeshByThread, sPath, sFileName).get();
//	g_sThreadResult.push_back();
//	if (sResult != "") {
//		GET_THREADPOOL->Thread_Stop(THREAD_LOADMAP);
//		RegisterMapLoaded(sResult);
//	}
//	
//	sPath = "./Resource/Test/";
//	sFileName = L"Udyr.x";
//	sObjName = "Zealot";
//	m_vThreadCompleted.push_back(false);
//	sResult = GET_THREADPOOL->EnqueueFunc(THREAD_LOADCHAMP, AddDynamicMeshByThread, sPath, sFileName).get();
//	if (sResult != "") {
//		GET_THREADPOOL->Thread_Stop(THREAD_LOADCHAMP);
//		RegisterMapLoaded(sResult);
//	}
//
//	for (auto& it : m_vThreadCompleted)
//		if (it == false)
//			return false;
//
//	return true;
//}
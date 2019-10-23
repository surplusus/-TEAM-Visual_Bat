#include "BaseInclude.h"
#include "LoadingScene.h"
#include "Image_Loader.h"
#include "SelectedChampion.h"
#include "TextMgr.h"
#include "SceneMgr.h"
#include "SelectScene.h"
#include "GuhyunScene.h"
#include "SceneMediator.h"
#include "ThreadPool.h"
#include "ObjMgr.h"
#include "SummonTerrain.h"
#include "Zealot.h"
#include "Factory.h"
#include <fstream>
#include <sstream>

CLoadingScene::CLoadingScene() 
	: m_pBackGround(NULL)
	, m_nStage(0)
{
}

CLoadingScene::~CLoadingScene()
{
}

HRESULT CLoadingScene::Initialize()
{
	m_pBackGround = new CImage_Loader("Resource/choen/Loading/LoadingBackGround.jpg", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_pBackGround->Initialize();


	m_pChampSelect = new CSelectedChampion(D3DXVECTOR3(255, 0, 0));
	m_pChampSelect->Initialize();

	GET_SINGLE(CTextMgr)->Initialize();
	cout << "로딩 됨" << endl;

	{	// Loading Progress Bar
		if (FAILED(D3DXCreateTextureFromFileExA(GET_DEVICE
			, "./Resource/choen/Loading/loading_circle.png"
			, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2
			, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8
			, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT
			, 0, &m_ImageInfo, NULL, &m_pLoadingTexture)))
			cout << "그림을 못 불렀지용~" << endl;
		if (FAILED(D3DXCreateSprite(GET_DEVICE, &m_pLoadingSprite)))
			cout << "sprite를 못 불렀지용~" << endl;
	}
	{	// Load Resource By Thread
		Begin_Render();
		Render();
		End_Render(g_hWnd);
		LoadResourceByThread();
	}
	SetMeshRegistryInfoThruFile();
	return S_OK;
}

void CLoadingScene::Progress()
{
	if (GetAsyncKeyState(VK_SPACE))
		GET_SINGLE(CSceneMgr)->SetState(new GuhyunScene);

#pragma region 스테이지 시작
	//// STAGE 1

	//if (!(m_nStage & (1 << BOXCOLLIDER))) {
	//	if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
	//	{
	//		ERR_MSG(g_hWnd, L"BoundingBox Load Failed");
	//	}
	//	m_nStage ^= (1 << BOXCOLLIDER);
	//	return;
	//}
	//// STAGE 2
	//if (!(m_nStage & (1 << LOADCHAMP))) {
	//	m_vpMeshInfo.emplace_back(new stMeshInfo("Zealot"
	//		, "./Resource/Test/", "Udyr.x"));
	//	if (GET_THREADPOOL->EnqueueFunc(THREAD_LOADCHAMP
	//		, LoadDynamicMeshByThread, m_vpMeshInfo[0]).get()) {
	//		GET_THREADPOOL->Thread_Stop(THREAD_LOADCHAMP);
	//		m_vpMeshInfo[0]->m_bComplete = true;
	//	}
	//	m_nStage ^= (1 << LOADCHAMP);
	//	return;
	//}
	//// STAGE 3
	//if (!(m_nStage & (1 << LOADMAP))) {
	//	// Load Map
	//	m_vpMeshInfo.emplace_back(new stMeshInfo("Map"
	//		, "./Resource/MapSummon/", "Floor.x"));
	//	//m_vpMeshInfo.emplace_back(new stMeshInfo("Map"
	//	//	, "./Resource/MapSummon/", "SummonMap.x"));
	//	if (GET_THREADPOOL->EnqueueFunc(THREAD_LOADMAP
	//		, LoadStaticMeshByThread, m_vpMeshInfo[1]).get()) {
	//		GET_THREADPOOL->Thread_Stop(THREAD_LOADMAP);
	//		m_vpMeshInfo[1]->m_bComplete = true;
	//	}
	//	m_nStage ^= (1 << LOADMAP);
	//	return;
	//}
	//// STAGE 4
	//if (!(m_nStage & (1 << INROLLCHAMP))) {
	//	RegisterOnObjMgr(m_vpMeshInfo[0]);
	//	m_nStage ^= (1 << INROLLCHAMP);
	//	return;
	//}
	//// STAGE 5
	//if (!(m_nStage & (1 << INROLLMAP))) {
	//	//RegisterOnObjMgr(m_vpMeshInfo[1]);
	//	m_nStage ^= (1 << INROLLMAP);
	//	return;
	//}
#pragma endregion

	//GET_SINGLE(CSceneMgr)->SetState(new GuhyunScene);
}

void CLoadingScene::Render()
{
	m_pBackGround->Render();
	GET_SINGLE(CTextMgr)->LoadingNoticeRender();
	m_pChampSelect->Render();

	// Loading Progress Bar
	Render_Loading();
}

void CLoadingScene::Release()
{
	delete m_pBackGround;
	m_pBackGround = NULL;

	delete m_pChampSelect;
	m_pChampSelect = NULL;

	SAFE_RELEASE(m_pLoadingSprite);
	SAFE_RELEASE(m_pLoadingTexture);

	for (auto& it : m_vpMeshInfo)
		delete it;
	m_vpMeshInfo.clear();
}

void CLoadingScene::Render_Loading()
{
	m_pLoadingSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	static int n = 0;
	static int y = 0;
	static float size = 1.f;
	n++;
	if (n >= 500) {
		n = 0;
		y += 128;
		size *= 0.8f;
		if (y >= 3072) y = 0;
		printf(" %d ", y);
	}
	RECT re = { y,0,y+128, 128};
	D3DXVECTOR3 position(2 * WINSIZEX - 250.f,2 * WINSIZEY - 200.f, 0.f);
	D3DXMATRIX matS;	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
	m_pLoadingSprite->SetTransform(&matS);
	m_pLoadingSprite->Draw(m_pLoadingTexture, &re
		, &D3DXVECTOR3(0.f, 0.f, 0.f), &position, D3DCOLOR_RGBA(255, 255, 255, 100));
	
	m_pLoadingSprite->End();
}

bool CLoadingScene::LoadResourceByThread()
{
	return true;
}

bool CLoadingScene::RegisterOnObjMgr(stMeshInfo * info)
{
	basic_string<TCHAR> sTemp(info->m_ObjName.begin(), info->m_ObjName.end());
	const TCHAR* t = sTemp.c_str();
	if (info->m_ObjName == "Map") {
		GET_SINGLE(CObjMgr)->AddObject(t, CFactory<CObj, CSummonTerrain>::CreateObject());
		cout << info->m_ConsoleText << '\n';
	}
	else if (info->m_ObjName == "Zealot") {
		GET_SINGLE(CObjMgr)->AddObject(t, CFactory<CObj, CZealot>::CreateObject());
		cout << info->m_ConsoleText << '\n';
	}
	return true;
}

bool CLoadingScene::LoadMeshByThread(stMeshInfo * info)
{
	basic_string<TCHAR> sTemp1(info->m_FolderPath.begin(), info->m_FolderPath.end());
	basic_string<TCHAR> sTemp2(info->m_FileName.begin(), info->m_FileName.end());
	basic_string<TCHAR> sTemp3(info->m_ObjName.begin(), info->m_ObjName.end());
	const TCHAR* t1 = sTemp1.c_str();
	const TCHAR* t2 = sTemp2.c_str();
	const TCHAR* t3 = sTemp3.c_str();
	
	if (SUCCEEDED(AddMesh(GetDevice(), t1, t2, t3, info->m_MeshType))) {
		info->m_ConsoleText = info->m_ObjName + " Load Complited";
		
		return true;
	}

	//CLoadingScene temp;
	//  
	//std::function<bool(stMeshInfo*)> func = [this](stMeshInfo* info) { this-> }

	info->m_ConsoleText = info->m_ObjName + " Load Failed";
	return false;
}

void CLoadingScene::SetMeshRegistryInfoThruFile()
{
	//ofstream file("./Resource/Test/test.dat",fstream::in | fstream::ate);
	ifstream file("./Resource/Test/test.dat", ifstream::in);

	if (!file.is_open()) {
		cout << "Error Opening File\n";
		return;
	}

	string name;
	while (file)
	{
		vector<string> token;
		string s, t;
		getline(file, s);
		if (s == "")	break;
		for (stringstream ss(s); (ss >> t);)
			token.push_back(t);
		if (token[0][0] == '-') {
			name = token[0].substr(1, token[0].size() - 2);
			m_mapMeshInfo[name];
		}
		else if (token[0] == "bComplete")
			m_mapMeshInfo[name].m_bComplete = (token[1][0] == 't') ? true : false;
		else if (token[0] == "ObjName")
			m_mapMeshInfo[name].m_ObjName = token[1];
		else if (token[0] == "FolderPath")
			m_mapMeshInfo[name].m_FolderPath = token[1];
		else if (token[0] == "FileName")
			m_mapMeshInfo[name].m_FileName = token[1];
		else if (token[0] == "ConsoleText")
			for (int i = 1; i < token.size(); ++i)
				m_mapMeshInfo[name].m_ConsoleText += token[i] + " ";
		else if (token[0] == "MeshType")
			m_mapMeshInfo[name].m_MeshType = static_cast<MESHTYPE>(stoi(token[1]));
		if (file.eof())	break;
	}
	int n = 0;
}

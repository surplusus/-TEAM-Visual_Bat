#include "BaseInclude.h"
#include "LoadingScene.h"
#include "Image_Loader.h"
#include "SelectedPlayer.h"
#include "TextMgr.h"
#include "SceneMgr.h"
#include "SelectScene.h"
#include "GuhyunScene.h"
#include "SceneMediator.h"
#include "ThreadPool.h"
#include "ObjMgr.h"
#include "SummonTerrain.h"
#include "SelectedSpells.h"
#include "GameScene.h"
#include "Udyr.h"
#include "Ezreal.h"
#include "Factory.h"
#include "SummonTerrain.h"
#include "InGameScene.h"
#include "SoundManager.h"
#include "MeshMgr.h"
#include "MeleeMinion.h"
#include <fstream>
#include <sstream>

CLoadingScene::CLoadingScene() 
	: m_pBackGround(NULL)
	, m_pTextMgr(NULL)
	, m_pChampSelect(NULL)
	, m_pSpell_1(NULL)
	, m_pSpell_2(NULL)
{
}

CLoadingScene::~CLoadingScene()
{
}

HRESULT CLoadingScene::Initialize()
{
	m_pBackGround = new CImage_Loader("Resource/choen/Loading/LoadingBackGround.jpg", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_pBackGround->Initialize();


	m_pChampSelect = new CSelectedPlayer(GET_SINGLE(CSceneMgr)->GetSceneMediator()->SetSelectedChampName());
	m_pChampSelect->Initialize();
	
	m_pTextMgr = new CTextMgr();
	m_pTextMgr->Initialize();
	cout << "로딩 됨" << endl;
	//GET_SINGLE(CSceneMgr)->GetSceneMediator()->MediateInfo(MEDIATETYPE::INIT, this);

	{	// Loading Progress Bar
		if (FAILED(D3DXCreateTextureFromFileExA(GET_DEVICE
			, "./Resource/choen/Loading/Loading_Green.png"
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

		SetFuncLoading(); // 쓰레드 대신 써본다(callable vector)
	}
	return S_OK;
}

void CLoadingScene::Progress()
{
	if (GetAsyncKeyState(VK_SPACE)) //GET_SINGLE(CSceneMgr)->SetState(new CGameScene);
		GET_SINGLE(CSceneMgr)->SetState(new GuhyunScene);
	if (GetAsyncKeyState(VK_LEFT))
		GET_SINGLE(CSceneMgr)->SetState(new CSelectScene);

	static int idx = 0;
	if (idx < m_vfuncLoading.size()) {
	//if (idx ) {
		FuncLoading fp = m_vfuncLoading[idx];
		fp();
		idx++;

		return;
	}

	GET_SINGLE(CSceneMgr)->SetState(new CInGameScene);
}

void CLoadingScene::Render()
{
	m_pBackGround->Render();
	m_pTextMgr->LoadingNoticeRender();
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
	delete m_pTextMgr;
	m_pTextMgr = NULL;

	SAFE_RELEASE(m_pLoadingSprite);
	SAFE_RELEASE(m_pLoadingTexture);

	m_mapMeshInfo.clear();
}

void CLoadingScene::Render_Loading()
{
	m_pLoadingSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	static int y = 0;
	static int prev = -2;
	if (prev != g_iLoadingSubSet) {
		prev = g_iLoadingSubSet;
		y += 128;
		if (y >= 3072) {
			y = 0;
			printf(" %d ", y);
		}
	}
	RECT re = { y,0,y+128, 128};
	D3DXVECTOR3 position(2 * WINSIZEX - 250.f,2 * WINSIZEY - 200.f, 0.f);
	D3DXMATRIX matS;	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
	m_pLoadingSprite->SetTransform(&matS);
	m_pLoadingSprite->Draw(m_pLoadingTexture, &re
		, &D3DXVECTOR3(0.f, 0.f, 0.f), &position, D3DCOLOR_RGBA(255, 255, 255, 100));
	m_pLoadingSprite->End();
}

void CLoadingScene::FuncDefaultMgrSetUp()
{
	// Set up Sounds
	//GET_SINGLE(SoundManager)->SetUp();
	//printf("Sound Set Up\n");
	// Make Bound
	if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
	{
		ERR_MSG(g_hWnd, L"BoundingBox Load Failed");
	}
	printf("BoundingBox On!\n");
}

void CLoadingScene::FuncLoadMap()
{
	if (!OperateFuncAddMeshByKey("Map")) {
		printf("맵 매쉬 로딩 실패\n");
		return;
	}
	OperateFuncAddObjectByKey("Map");
	printf("맵 매쉬 로딩 완료!\n");
}

void CLoadingScene::FuncLoadChamp()
{
	if (!OperateFuncAddMeshByKey("Udyr")) {
		printf("우디르 매쉬 로딩 실패\n");
		return;
	}
	OperateFuncAddObjectByKey("Udyr");
	printf("우디르 매쉬 로딩 완료!\n");
}

void CLoadingScene::FuncLoadMinion()
{
	if (!OperateFuncAddMeshByKey("Minion")) {
		printf("미니언 매쉬 로딩 실패\n");
		return;
	}
	OperateFuncAddObjectByKey("Minion");
	printf("미니언 매쉬 로딩 완료!\n");
}

void CLoadingScene::SetFuncLoading()
{
	//function<void(const CLoadingScene&)> fp = &CLoadingScene::FuncLoadBound;
	m_vfuncLoading.push_back([this]() {this->SetMeshInfoThruFile(); });
	m_vfuncLoading.push_back([this]() {this->FuncDefaultMgrSetUp(); });
	m_vfuncLoading.push_back([this]() {this->FuncLoadMap(); });
	m_vfuncLoading.push_back([this]() {this->FuncLoadChamp(); });
	m_vfuncLoading.push_back([this]() {this->FuncLoadMinion(); });
}

void CLoadingScene::SetMeshInfoThruFile()
{
	ifstream file("./Resource/MeshPathList.dat", ifstream::in);
	//ifstream file("./Resource/Test/test.dat", ifstream::in);

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

		if (token[0][0] == '#') {
			continue;
		}
		else if (token[0][0] == '-') {
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
	file.close();
}

bool CLoadingScene::OperateFuncAddMeshByKey(string key)
{
	if (m_mapMeshInfo.find(key) == m_mapMeshInfo.end())
		return false;
	auto info = m_mapMeshInfo[key];
	
	basic_string<TCHAR> sFolder(info.m_FolderPath.begin(), info.m_FolderPath.end());
	basic_string<TCHAR> sFile(info.m_FileName.begin(), info.m_FileName.end());
	const TCHAR* t1 = sFolder.c_str();
	const TCHAR* t2 = sFile.c_str();

	if (key == "Map") {
		if (SUCCEEDED(AddMesh(GetDevice(), t1, t2, L"Map", info.m_MeshType))) {
			printf("%s\n", info.m_ConsoleText.c_str());
			return true;
		}
	}
	else if (key == "Udyr"){
		if (SUCCEEDED(AddMesh(GetDevice(), t1, t2, L"Udyr", info.m_MeshType))) {
			printf("%s\n", info.m_ConsoleText.c_str());
			return true;
		}
	}
	else if (key == "Ezreal") {
		if (SUCCEEDED(AddMesh(GetDevice(), t1, t2, L"Ezreal", info.m_MeshType))) {
			printf("%s\n", info.m_ConsoleText.c_str());
			return true;
		}
	}
	else if (key == "Minion") {
		if (SUCCEEDED(AddMesh(GetDevice(), t1, t2, L"Minion", info.m_MeshType))) {
			printf("%s\n", info.m_ConsoleText.c_str());
			return true;
		}
	}
	return false;
}

void CLoadingScene::OperateFuncAddObjectByKey(string key)
{
	if (m_mapMeshInfo.find(key) == m_mapMeshInfo.end())
		return;

	auto info = m_mapMeshInfo[key];
	basic_string<TCHAR> sName(info.m_ObjName.begin(), info.m_ObjName.end()); 
	TCHAR* szName = new TCHAR[sName.length() + 1];
	ZeroMemory(szName, sizeof(TCHAR) * (sName.length() + 1));
	lstrcpy(szName, sName.c_str());
	HRESULT re;
	if (key == "Map")
		re = GET_SINGLE(CObjMgr)->AddObject(L"Map", CFactory<CObj, CSummonTerrain>::CreateObject());
	else if (key == "Udyr")
		re = GET_SINGLE(CObjMgr)->AddObject(L"Udyr", CFactory<CObj, CUdyr>::CreateObject());
	else if (key == "Minion")
		re = GET_SINGLE(CObjMgr)->AddObject(L"Minion", CFactory<CObj, CMeleeMinion>::CreateObject());
	// 추상클래스를 인스턴스화할수없습니다(?)
	//else if (key == "Ezreal")
	//	re = GET_SINGLE(CObjMgr)->AddObject(L"Ezreal", CFactory<CObj, CEzreal>::CreateObject());

	if (SUCCEEDED(re))
		printf("Succeeded in Object Registered\n");
	else
		printf("Failed to Register Object\n");
}
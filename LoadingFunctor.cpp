#include "BaseInclude.h"
#include "LoadingFunctor.h"
#include "ThreadPool.h"
#include "SoundMgr.h"
#include "Factory.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include <fstream>
#include <sstream>

#include "Udyr.h"
#include "Ezreal.h"
#include "SummonTerrain.h"
#include "MeleeMinion.h"
#include "CannonMinion.h"
#include "MinionMgr.h"
#include "Cursor.h"

CLoadingFunctor::CLoadingFunctor()
	: m_iFuncSize(0)
	, m_iFuncIdx(0)
{
	m_SelectedChamp = "";
	m_mapMeshInfo.clear();

	{
		m_queFunc.push([this]() {return this->SetMeshInfoThruFile(); });
		m_queFunc.push([this]() {return this->FuncDefaultMgrSetUp(); });
		m_queFunc.push([this]() {return this->FuncLoadMap(); });
		m_queFunc.push([this]() {return this->FuncLoadChamp(); });
		m_queFunc.push([this]() {return this->FuncLoadMinion(); });

		m_mapMeshInfo.clear();
	}
}

CLoadingFunctor::CLoadingFunctor(const CLoadingFunctor & rhv)
{
	m_SelectedChamp = rhv.m_SelectedChamp;
	m_mapMeshInfo.clear();
	m_iFuncIdx = rhv.m_iFuncIdx;
	m_iFuncSize = rhv.m_iFuncSize;
}

CLoadingFunctor::~CLoadingFunctor()
{
	m_mapMeshInfo.clear();
}

bool CLoadingFunctor::operator()()
{
	using FUNC = function<bool(void)>;
	if (m_queFunc.empty())
		return true;
	FUNC fp = m_queFunc.front();
	bool re = fp();
	++m_iFuncIdx;
	m_queFunc.pop();
	return false;
}

bool CLoadingFunctor::SetMeshInfoThruFile()
{
	//ifstream file("./Resource/MeshPathList.dat", ifstream::in);
	ifstream file("./Resource/Test/test.dat", ifstream::in);

	if (!file.is_open()) {
		cout << "Error Opening File\n";
		SendMessage(NULL, WM_QUIT, 0, 0);
		return false;
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
	cout << "파일 로딩 끝\n";
	return true;

}

bool CLoadingFunctor::FuncDefaultMgrSetUp()
{
	{	// Set up Sounds
		//GET_SINGLE(SoundMgr)->SetUp();
		//printf("sound set up\n");
	}
	
	{	// Make Bound
		if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
		{
			ERR_MSG(g_hWnd, L"BoundingBox Load Failed");
		}
		printf("BoundingBox On!\n");
	}

	{	// Make Cursor
		CCursor* pCursor = new CCursor();
		pCursor->InitCursor();
		GET_SINGLE(CSceneMgr)->GetSceneMediator()->SetVoidPointerMap("Cursor", reinterpret_cast<void**>(&pCursor));
		pCursor->SetCursor(CCursor::CURSORTYPE::CURSORTYPE_INGAME);
		printf("Make Hand Cursor\n");
	}
	return true;
}

bool CLoadingFunctor::FuncLoadMap()
{
	if (!OperateFuncAddMeshByKey("Map")) {
		printf("맵 매쉬 로딩 실패\n");
		return false;
	}
	OperateFuncAddObjectByKey("Map");
	printf("맵 매쉬 로딩 완료!\n");
	return true;
}

bool CLoadingFunctor::FuncLoadChamp()
{
	if (!OperateFuncAddMeshByKey(m_SelectedChamp)) {
		printf("챔피언 매쉬 로딩 실패\n");
		return false;
	}
	OperateFuncAddObjectByKey(m_SelectedChamp);

	{	//Ezreal dummy
		if (!OperateFuncAddMeshByKey("Ezreal")) {
			printf("챔피언 매쉬 로딩 실패\n");
			return false;
		}
		OperateFuncAddObjectByKey("Ezreal");
	}
	printf("챔피언 매쉬 로딩 완료!\n");
	return true;
}

bool CLoadingFunctor::FuncLoadMinion()
{
	if (!OperateFuncAddMeshByKey("MeleeMinion")) {
		printf("미니언 매쉬 로딩 실패\n");
		return false;
	}
	OperateFuncAddObjectByKey("MeleeMinion");
	printf("미니언 매쉬 로딩 완료!\n");
	return true;
}

bool CLoadingFunctor::OperateFuncAddMeshByKey(string key)
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
	else if (key == "Udyr") {
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
	else if (key == "MeleeMinion") {
		if (SUCCEEDED(AddMesh(GetDevice(), t1, t2, L"MeleeMinion", info.m_MeshType))) {
			printf("%s\n", info.m_ConsoleText.c_str());
			return true;
		}
	}
	else if (key == "CannonMinion") {
		if (SUCCEEDED(AddMesh(GetDevice(), t1, t2, L"CannonMinion", info.m_MeshType))) {
			printf("%s\n", info.m_ConsoleText.c_str());
			return true;
		}
	}
	return false;
}

bool CLoadingFunctor::OperateFuncAddObjectByKey(string key)
{
	if (m_mapMeshInfo.find(key) == m_mapMeshInfo.end())
		return false;

	HRESULT re = S_FALSE;
	if (key == "Map")
		re = GET_SINGLE(CObjMgr)->AddObject(L"Map", CFactory<CObj, CSummonTerrain>::CreateObject());
	else if (key == "Udyr")
		re = GET_SINGLE(CObjMgr)->AddObject(L"Udyr", CFactory<CObj, CUdyr>::CreateObject());
	else if (key == "Ezreal")
		re = GET_SINGLE(CObjMgr)->AddObject(L"Ezreal", CFactory<CObj, CEzreal>::CreateObject());
	else if (key == "MeleeMinion" || key == "CannonMinion")
	{	// 미니언 매니저 생성(&미니언 objmgr 등록)과 mediator setter
		CMinionMgr* pMinionMgr = new CMinionMgr;
		pMinionMgr->CreateMinions();
		GET_SINGLE(CSceneMgr)->GetSceneMediator()->SetVoidPointerMap("MinionMgr",
			reinterpret_cast<void**>(&pMinionMgr));
	}

	if (SUCCEEDED(re)) {
		printf("%s register 완료\n", key.c_str());
		return true;
	}

	printf("%s register 건너뜀\n", key.c_str());
	return false;
}

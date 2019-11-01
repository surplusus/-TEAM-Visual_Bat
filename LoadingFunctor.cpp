#include "BaseInclude.h"
#include "LoadingFunctor.h"
#include "ThreadPool.h"
#include "SoundMgr.h"
#include "Factory.h"
#include "ObjMgr.h"
#include <fstream>
#include <sstream>

#include "Zealot.h"
#include "Udyr.h"
#include "Ezreal.h"
#include "SummonTerrain.h"
#include "MeleeMinion.h"
#include "CannonMinion.h"

bool CLoadingFunctor::g_bComplete = false;

CLoadingFunctor::CLoadingFunctor()
	: m_iFuncIdx(0)
{
	//m_queFunc.push([this]() {return this->SetMeshInfoThruFile(); });
	//m_queFunc.push([this]() {return this->FuncDefaultMgrSetUp(); });
	//m_queFunc.push([this]() {return this->FuncLoadMap(); });
	//m_queFunc.push([this]() {return this->FuncLoadChamp(); });
	//m_queFunc.push([this]() {return this->FuncLoadMinion(); });
	//
	//m_iFuncSize = m_queFunc.size();
	//m_mapMeshInfo.clear();
}

CLoadingFunctor::~CLoadingFunctor()
{
	m_mapMeshInfo.clear();
}

bool CLoadingFunctor::operator()()
{
	{	// 생성자가 불리지 않는 관계로 여기서 초기화한다.
		m_iFuncIdx = 0;
		m_queFunc.push([this]() {return this->SetMeshInfoThruFile(); });
		m_queFunc.push([this]() {return this->FuncDefaultMgrSetUp(); });
		m_queFunc.push([this]() {return this->FuncLoadMap(); });
		m_queFunc.push([this]() {return this->FuncLoadChamp(); });
		m_queFunc.push([this]() {return this->FuncLoadMinion(); });

		m_iFuncSize = m_queFunc.size();
		m_mapMeshInfo.clear();
	}

	using FUNC = function<bool(void)>;
	int iPrevFuncIdx = m_iFuncIdx;
	
	while (m_iFuncIdx < m_iFuncSize)
	{
		FUNC fp = m_queFunc.front();
		fp();
		++m_iFuncIdx;
		m_queFunc.pop();
	}
	g_bComplete = true;
	return true;
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
	return true;

}

bool CLoadingFunctor::FuncDefaultMgrSetUp()
{
	// Set up Sounds
	GET_SINGLE(SoundMgr)->SetUp();
	printf("sound set up\n");
	// Make Bound
	if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
	{
		ERR_MSG(g_hWnd, L"BoundingBox Load Failed");
	}
	printf("BoundingBox On!\n");
	return true;
}

bool CLoadingFunctor::FuncLoadMap()
{
	if (!OperateFuncAddMeshByKey("Map")) {
		printf("맵 매쉬 로딩 실패\n");
		return true;
	}
	OperateFuncAddObjectByKey("Map");
	printf("맵 매쉬 로딩 완료!\n");
	return true;
}

bool CLoadingFunctor::FuncLoadChamp()
{
	if (!OperateFuncAddMeshByKey("Udyr")) {
		printf("우디르 매쉬 로딩 실패\n");
		return true;
	}
	OperateFuncAddObjectByKey("Udyr");
	printf("우디르 매쉬 로딩 완료!\n");
	return true;
}

bool CLoadingFunctor::FuncLoadMinion()
{
	if (!OperateFuncAddMeshByKey("MeleeMinion")) {
		printf("미니언 매쉬 로딩 실패\n");
		return true;
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
	//else if (key == "CannonMinion") {
	//	if (SUCCEEDED(AddMesh(GetDevice(), t1, t2, L"CannonMinion", info.m_MeshType))) {
	//		printf("%s\n", info.m_ConsoleText.c_str());
	//		return true;
	//	}
	//}
	return false;
}

bool CLoadingFunctor::OperateFuncAddObjectByKey(string key)
{
	if (m_mapMeshInfo.find(key) == m_mapMeshInfo.end())
		return false;

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
	else if (key == "Ezreal")
		re = GET_SINGLE(CObjMgr)->AddObject(L"Ezreal", CFactory<CObj, CEzreal>::CreateObject());
	else if (key == "MeleeMinion")
		re = GET_SINGLE(CObjMgr)->AddObject(L"MeleeMinion", CFactory<CObj, CMeleeMinion>::CreateObject());
	//else if (key == "CannonMinion")
	//	re = GET_SINGLE(CObjMgr)->AddObject(L"CannonMinion", CFactory<CObj, CCannonMinion>::CreateObject());

	if (SUCCEEDED(re))
		printf("Succeeded in Object Registered\n");
	else
		printf("Failed to Register Object\n");
}

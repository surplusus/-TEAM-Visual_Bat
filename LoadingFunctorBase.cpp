#include "BaseInclude.h"
#include "LoadingFunctorBase.h"
#include "Factory.h"
#include "ObjMgr.h"
#include <fstream>
#include <sstream>

#include "Udyr.h"
#include "Ezreal.h"
#include "SummonTerrain.h"
#include "MeleeMinion.h"
#include "CannonMinion.h"
#include "MinionMgr.h"
#include "Cursor.h"
#include "Turret.h"
#include "Inhibitor.h"
#include "Nexus.h"


bool CLoadingFunctorBase::SetMeshInfoThruFile(string sFileName)
{
	string sFilePath = "./Resource/" + sFileName;
	ifstream file(sFilePath, ifstream::in);
	//ifstream file("./Resource/Test/test.dat", ifstream::in);

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
			continue;
		}
		else if (token[0] == "ObjName") {
			name = token[1];
			m_mapMeshInfo.insert({ name, new stMeshInfo(name) });
		}
		else if (token[0] == "FolderPath")
			m_mapMeshInfo[name]->m_FolderPath = basic_string<TCHAR>(token[1].begin(), token[1].end());
		else if (token[0] == "FileName")
			m_mapMeshInfo[name]->m_FileName = basic_string<TCHAR>(token[1].begin(), token[1].end());
		else if (token[0] == "ConsoleText")
			for (int i = 1; i < token.size(); ++i)
				m_mapMeshInfo[name]->m_ConsoleText += token[i] + " ";
		else if (token[0] == "MeshType")
			m_mapMeshInfo[name]->m_MeshType = static_cast<MESHTYPE>(stoi(token[1]));
		if (file.eof())	break;
	}
	file.close();
	cout << "파일 로딩 끝\n";
	return true;
}

bool CLoadingFunctorBase::RegisterCloneObjectByKey(string key)
{
	if (key == "Udyr")
		return OperateAddObjectByKey<CUdyr>(key);
	if (key == "Ezreal")
		return OperateAddObjectByKey<CEzreal>(key);
	if (key == "Map")
		return OperateAddObjectByKey<CSummonTerrain>(key);
}

bool CLoadingFunctorBase::OperateAddMeshByKey(string key)
{
	if (m_mapMeshInfo.find(key) == m_mapMeshInfo.end())
		return false;
	auto info = m_mapMeshInfo[key];

	if (SUCCEEDED(AddMesh(GetDevice(), info->m_FolderPath.c_str(), info->m_FileName.c_str(), info->m_szObjName, info->m_MeshType))) {
		printf("%s\n", info->m_ConsoleText.c_str());
		return true;
	}
	else {
		basic_string<TCHAR> sTCHAR(info->m_szObjName);
		string name(sTCHAR.begin(), sTCHAR.end());
		cout << name << " 매쉬 로딩 실패\n";
		return false;
	}
}

template<typename ClassType>
bool CLoadingFunctorBase::OperateAddObjectByKey(string key)
{
	if (m_mapMeshInfo.find(key) == m_mapMeshInfo.end())
		return false;
	auto info = m_mapMeshInfo[key];

	HRESULT re = S_FALSE;
	re = GET_SINGLE(CObjMgr)->AddObject(info->m_szObjName, CFactory<CObj, ClassType>::CreateObject());

	if (SUCCEEDED(re)) {
		printf("%s register 완료\n", key.c_str());
		return true;
	}

	printf("%s register 건너뜀\n", key.c_str());
	return false;
}

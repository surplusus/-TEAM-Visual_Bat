#pragma once
struct stMeshInfo
{
	bool m_bComplete = false;
	string m_ObjName;
	string m_FolderPath;
	string m_FileName;
	string m_ConsoleText;
	MESHTYPE m_MeshType;
	stMeshInfo() {}
	stMeshInfo(string objName, string folderPath, string fileName, MESHTYPE type)
		: m_ObjName(objName), m_FolderPath(folderPath), m_FileName(fileName), m_MeshType(type) {}
};

class CLoadingFunctor
{
public:
	CLoadingFunctor();
	CLoadingFunctor(const CLoadingFunctor& rhv);
	~CLoadingFunctor();
	bool operator() ();
public:
	string							m_SelectedChamp;
public:
	int								m_iFuncSize;
	int								m_iFuncIdx;
	map<string, stMeshInfo>			m_mapMeshInfo;
	queue<function<bool(void)>>		m_queFunc;
	bool SetMeshInfoThruFile();
	bool FuncDefaultMgrSetUp();
	bool FuncLoadMap();
	bool FuncLoadChamp();
	bool FuncLoadMinion();
	bool OperateFuncAddMeshByKey(string key);
	bool OperateFuncAddObjectByKey(string key);
};


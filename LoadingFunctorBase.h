#pragma once

struct stMeshInfo
{
	const TCHAR*		m_szObjName;
	basic_string<TCHAR> m_FolderPath;
	basic_string<TCHAR> m_FileName;
	string				m_ConsoleText;
	MESHTYPE			m_MeshType;
	stMeshInfo(string str) {
		if (str == "Map" || str == "map")		m_szObjName = L"Map";
		if (str == "Udyr" || str == "udyr")		m_szObjName = L"Udyr";
		if (str == "Ezreal" || str == "ezreal")	m_szObjName = L"Ezreal";
		if (str == "MeleeMinion")				m_szObjName = L"MeleeMinion";
		if (str == "CannonMinion")				m_szObjName = L"CannonMinion";
		if (str == "Blue_Turret")				m_szObjName = L"Blue_Turret";
		if (str == "Inhibitor")					m_szObjName = L"Inhibitor";
		if (str == "Nexus")						m_szObjName = L"Nexus";
	}
	stMeshInfo(const stMeshInfo& rhs) : m_szObjName(rhs.m_szObjName) {}
};

class CLoadingFunctorBase
{
public:
	CLoadingFunctorBase(){ m_mapMeshInfo.clear(); }
	virtual ~CLoadingFunctorBase() {
		for (auto & it : m_mapMeshInfo)
			SAFE_DELETE(it.second);
		m_mapMeshInfo.clear();
	}
	bool SetMeshInfoThruFile();
	template<typename ClassType>
	bool OperateAddObjectByKey(string key);
	bool RegisterCloneObjectByKey(string key);
	bool OperateAddMeshByKey(string key);
protected:
	map<string, stMeshInfo*>		m_mapMeshInfo;
};

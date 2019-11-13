#include "BaseInclude.h"
#include "MakingTowerFunctor.h"
#include "ObjMgr.h"
#include "Turret.h"
#include "Inhibitor.h"
#include "Nexus.h"

CMakingTowerFunctor::CMakingTowerFunctor(string sFilePath)
	: m_sFilePath(sFilePath)
{
	m_mapMeshInfo.clear();

	{	// lampda를 queue에 넣어주기
		m_queFunc.push([this]() {return this->SetMeshInfoThruFile(m_sFilePath); });
		m_queFunc.push([this]() {return this->FuncLoadTurret(); });
		m_queFunc.push([this]() {return this->FuncLoadInhibitor(); });
		m_queFunc.push([this]() {return this->FuncLoadNexus(); });
	}

}

CMakingTowerFunctor::~CMakingTowerFunctor()
{
	for (auto & it : m_vTurret)
		SAFE_DELETE(it);
	m_vTurret.clear();
	SAFE_DELETE(m_pInhibitor);
	SAFE_DELETE(m_pNexus);
}

bool CMakingTowerFunctor::operator()()
{
	using FUNC = function<bool(void)>;
	if (m_queFunc.empty())
		return false;
	FUNC fp = m_queFunc.front();
	bool re = fp();
	++m_iFuncIdx;
	m_queFunc.pop();
	return true;
}

bool CMakingTowerFunctor::FuncLoadTurret()
{
	string key = "Blue_Turret";
	if (m_mapMeshInfo.find(key) == m_mapMeshInfo.end()){
		printf("Blue Turret 파일에 없음\n");
		return false;
	}
	auto info = m_mapMeshInfo[key];

	{
		HRESULT re = true;
		bool bSignFalse = false;
		re = AddMesh(GetDevice(), info->m_FolderPath.c_str(), info->m_FileName.c_str(), L"Blue_Turret1", info->m_MeshType);
		if (SUCCEEDED(re))
			printf("1 : %s\n", info->m_ConsoleText.c_str());
		else
			bSignFalse = true;
		if (SUCCEEDED(AddMesh(GetDevice(), info->m_FolderPath.c_str(), info->m_FileName.c_str(), L"Blue_Turret2", info->m_MeshType)))
			if (SUCCEEDED(re))
				printf("2 : %s\n", info->m_ConsoleText.c_str());
			else
				bSignFalse = true;
		if (SUCCEEDED(AddMesh(GetDevice(), info->m_FolderPath.c_str(), info->m_FileName.c_str(), L"Blue_Turret3", info->m_MeshType)))
			if (SUCCEEDED(re))
				printf("3 : %s\n", info->m_ConsoleText.c_str());
			else
				bSignFalse = true;
		if (SUCCEEDED(AddMesh(GetDevice(), info->m_FolderPath.c_str(), info->m_FileName.c_str(), L"Blue_Turret4", info->m_MeshType)))
			if (SUCCEEDED(re))
				printf("4 : %s\n", info->m_ConsoleText.c_str());
			else
				bSignFalse = true;
		if (bSignFalse) {
			basic_string<TCHAR> sTCHAR(info->m_szObjName);
			string name(sTCHAR.begin(), sTCHAR.end());
			cout << name << " 매쉬 로딩 실패\n";
			return false;
		}
	}
	{
		//터렛
		m_vTurret.emplace_back(new CTurret(D3DXVECTOR3(23.f, 0.f, 22.5f), L"order_outer_Turret", 50.0f));
		m_vTurret.emplace_back(new CTurret(D3DXVECTOR3(14.5f, 0.f, 14.3f), L"order_iner_Turret", 50.0f));
		m_vTurret.emplace_back(new CTurret(D3DXVECTOR3(4.5f, 0.f, 0.9f), L"order_twins_left_Turret", 50.0f));
		m_vTurret.emplace_back(new CTurret(D3DXVECTOR3(1.f, 0.f, 4.7f), L"order_twins_right_Turret", 50.0f));

		m_vTurret[0]->SetMeshName(L"order_outer_Turret");
		m_vTurret[1]->SetMeshName(L"order_iner_Turret");
		m_vTurret[2]->SetMeshName(L"order_twins_left_Turret");
		m_vTurret[3]->SetMeshName(L"order_twins_right_Turret");
		
		for (size_t i = 0; i < m_vTurret.size(); i++)
			m_vTurret[i]->Initialize();
		
		GET_SINGLE(CObjMgr)->AddObject(L"order_outer_Turret", m_vTurret[0]);
		GET_SINGLE(CObjMgr)->AddObject(L"order_iner_Turret", m_vTurret[1]);
		GET_SINGLE(CObjMgr)->AddObject(L"order_twins_left_Turret", m_vTurret[2]);
		GET_SINGLE(CObjMgr)->AddObject(L"order_twins_right_Turret", m_vTurret[3]);
	}
	return true;
}

bool CMakingTowerFunctor::FuncLoadInhibitor()
{
	if (!OperateAddMeshByKey("Inhibitor")) {
		//ERR_MSG(g_hWnd, L"억제기 로드 실패");
		printf("억제기 로드 실패\n");
		return false;
	}
	{
		//억제기
		CInhibitor*	pInhibitor = new CInhibitor(D3DXVECTOR3(9.5f, 0.f, 9.5f));
		pInhibitor->Initialize();
		GET_SINGLE(CObjMgr)->AddObject(L"Inhibitor", pInhibitor);
	}
	return true;
}

bool CMakingTowerFunctor::FuncLoadNexus()
{
	if (!OperateAddMeshByKey("Nexus")) {
		//ERR_MSG(g_hWnd, L"넥서스 로드 실패");
		printf("넥서스 로드 실패\n");
		return false;
	}
	{
		//넥서스
		CNexus*	pNexus = new CNexus(D3DXVECTOR3(0, 0, 0));
		pNexus->Initialize();
		GET_SINGLE(CObjMgr)->AddObject(L"Nexus", pNexus);
	}
	return true;
}




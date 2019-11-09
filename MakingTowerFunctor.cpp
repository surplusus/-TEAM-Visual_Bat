#include "BaseInclude.h"
#include "MakingTowerFunctor.h"
#include "ObjMgr.h"
#include "Turret.h"
#include "Inhibitor.h"
#include "Nexus.h"

CMakingTowerFunctor::CMakingTowerFunctor()
{
	m_mapMeshInfo.clear();

	{	// lampda를 queue에 넣어주기
		m_queFunc.push([this]() {return this->SetMeshInfoThruFile(); });
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
	if (!OperateAddMeshByKey("Blue_Turret")) {
		ERR_MSG(g_hWnd, L"포탑로드 실패");
		return false;
	}
	{
		//터렛
		m_vTurret.emplace_back(new CTurret(D3DXVECTOR3(23.f, 0.f, 22.5f)));
		m_vTurret.emplace_back(new CTurret(D3DXVECTOR3(14.5f, 0.f, 14.3f)));
		m_vTurret.emplace_back(new CTurret(D3DXVECTOR3(4.5f, 0.f, 0.9f)));
		m_vTurret.emplace_back(new CTurret(D3DXVECTOR3(1.f, 0.f, 4.7f)));
		for (size_t i = 0; i < m_vTurret.size(); i++)
		{
			m_vTurret[i]->Initialize();
			GET_SINGLE(CObjMgr)->AddObject(L"Blue_Turret", m_vTurret[i]);
		}
	}
	return true;
}

bool CMakingTowerFunctor::FuncLoadInhibitor()
{
	if (!OperateAddMeshByKey("Inhibitor")) {
		ERR_MSG(g_hWnd, L"억제기 로드 실패");
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
		ERR_MSG(g_hWnd, L"넥서스 로드 실패");
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

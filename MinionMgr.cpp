#include "BaseInclude.h"
#include "MinionMgr.h"
#include "Minion.h"
#include "SoundMgr.h"
#include "MeleeMinion.h"
#include "ObjMgr.h"
#include "HeightMap.h"

CMinionMgr::CMinionMgr()
{

}


CMinionMgr::~CMinionMgr()
{
	Release();
}

void CMinionMgr::CreateMinions()
{
	HRESULT res;
	for (size_t i = 0; i < 3; ++i)
		m_vMinion.emplace_back(new CMeleeMinion());
	m_vMinion[0]->SetMeshName(L"MeleeMinion1");
	m_vMinion[1]->SetMeshName(L"MeleeMinion2");
	m_vMinion[2]->SetMeshName(L"MeleeMinion3");

	for (size_t i = 0; i < 3; ++i) {
		m_vMinion[i]->SetMinionMgr(this);
		res = GET_SINGLE(CObjMgr)->AddObject(m_vMinion[i]->m_MeshName, m_vMinion[i]);
		
		if (FAILED(res))
			ERR_MSG(g_hWnd, L"Fail : Register On Minion1");
		//m_vMinion.push_back(new CMeleeMinion());
	}
	
	this->Initialize();
}

void CMinionMgr::SetFirstPositions(CMinion *pMinion, const D3DXVECTOR3 * pos)
{
	pMinion->SetPosition(pos);
}

void CMinionMgr::SetHeightMap(CHeightMap ** pHeightMap)
{
	for (CMinion* it : m_vMinion)
		it->SetHeightMap(pHeightMap);
}

CMinion * CMinionMgr::GetMinion(int nIndex)
{
	if (nIndex >= (int)m_vMinion.size())
		return nullptr;
	return m_vMinion[nIndex];
}

void CMinionMgr::Initialize()
{
	for (auto & it : m_vMinion)
		it->Initialize();
	//GET_SINGLE(SoundMgr)->PlayAnnouncerMention(T_SOUND::ANNOUNCER_Createminion);
}

void CMinionMgr::Progress()
{
	for (auto & it : m_vMinion)
		it->Progress();
}

void CMinionMgr::Render()
{
	for (auto & it : m_vMinion)
		it->Render();
}

void CMinionMgr::Release()
{
	m_vMinion.clear();
}

#include "BaseInclude.h"
#include "MinionMgr.h"
#include "Minion.h"
#include "SoundMgr.h"
#include "MeleeMinion.h"
#include "ObjMgr.h"
#include "HeightMap.h"
#include "MeleeMinion.h"

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
	for (size_t i = 0; i < 3; ++i) {
		m_vMinion.emplace_back(new CMeleeMinion());
		m_vMinion[i]->SetMinionMgr(this);
	}
	m_vMinion[0]->SetMeshName(L"MeleeMinion1");
	m_vMinion[1]->SetMeshName(L"MeleeMinion2");
	m_vMinion[2]->SetMeshName(L"MeleeMinion3");
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
	//for (auto & it : m_vMinion)
	//	it->Progress();
	static int cnt = 0;
	static size_t idx = 0;

	//if (cnt == 600 || cnt == 800 || cnt == 1000)
	if (cnt == 100 || cnt == 300 || cnt == 500)
	{
		HRESULT res = GET_SINGLE(CObjMgr)->AddObject(m_vMinion[idx]->m_MeshName, m_vMinion[idx]);
		if (FAILED(res))
			ERR_MSG(g_hWnd, L"Fail : Register On Minion1");
		
		m_vMinion[idx]->Initialize();
		// 초기 위치를 여기서 잡아야됨
		m_vMinion[idx]->SetPos(&D3DXVECTOR3(5.f, 0.f, 5.f));
		++idx;
	}
	if (cnt <= 1000) {
		++cnt;
		return;
	}
	
	if (m_vMinion[0]->m_bAlive == false) {
		GET_SINGLE(CObjMgr)->EraseObject(m_vMinion[0]->GetMeshName());
		m_vMinion.erase(m_vMinion.begin());
	}
	if (m_vMinion[1]->m_bAlive == false) {
		GET_SINGLE(CObjMgr)->EraseObject(m_vMinion[1]->GetMeshName());
		m_vMinion.erase(m_vMinion.begin() + 1);
	}
	if (m_vMinion[2]->m_bAlive == false) {
		GET_SINGLE(CObjMgr)->EraseObject(m_vMinion[2]->GetMeshName());
		m_vMinion.erase(m_vMinion.begin() + 2);
	}
}

void CMinionMgr::Render()
{
	//for (auto & it : m_vMinion)
	//	it->Render();
}

void CMinionMgr::Release()
{
	m_vMinion.clear();
}

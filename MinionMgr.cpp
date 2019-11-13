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
	if (cnt < 200) {
		++cnt;
		return;
	}

	if (cnt == 200)
	{
		for (auto & it : m_vMinion)
			it->Initialize();
		{	// 초기 위치를 여기서 잡아야됨
			m_vMinion[0]->SetPos(&D3DXVECTOR3(5.f, 0.f, 5.f));
			m_vMinion[1]->SetPos(&D3DXVECTOR3(-5.f, 0.f, 5.f));
			m_vMinion[2]->SetPos(&D3DXVECTOR3(5.f, 0.f, -5.f));
		}
		++cnt;
	}

	if (dynamic_cast<CMeleeMinion*>(m_vMinion[0])->m_pBehavior->m_BlackBoard->getBool("Alive") == false)
		GET_SINGLE(CObjMgr)->EraseObject(L"MeleeMinion1");
	if (dynamic_cast<CMeleeMinion*>(m_vMinion[1])->m_pBehavior->m_BlackBoard->getBool("Alive") == false)
		GET_SINGLE(CObjMgr)->EraseObject(L"MeleeMinion2");
	if (dynamic_cast<CMeleeMinion*>(m_vMinion[2])->m_pBehavior->m_BlackBoard->getBool("Alive") == false)
		GET_SINGLE(CObjMgr)->EraseObject(L"MeleeMinion3");
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

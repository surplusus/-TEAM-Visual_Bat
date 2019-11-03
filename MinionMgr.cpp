#include "BaseInclude.h"
#include "MinionMgr.h"
#include "Minion.h"
#include "SoundMgr.h"
#include "MeleeMinion.h"
#include "ObjMgr.h"

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
	{
		m_vMinion.push_back(new CMeleeMinion());
		m_vMinion[i]->SetMinionMgr(this);;
		if (FAILED(m_vMinion[i]->Initialize()))
			ERR_MSG(g_hWnd, L"Fail : Minion Initialize");
		
		{	// 미니언 처음 위치 설정 (바꾸어야 됨)
			int iPos = rand() % 10;
			SetFirstPositions(D3DXVECTOR3((float)iPos, 0, (float)iPos));
		}
	}

	res = GET_SINGLE(CObjMgr)->AddObject(L"Minion0", m_vMinion[0]);
	if (FAILED(res))
		ERR_MSG(g_hWnd, L"Fail : Register On Minion0");
	m_vMinion.push_back(new CMeleeMinion());
	res = GET_SINGLE(CObjMgr)->AddObject(L"Minion1", m_vMinion[1]);
	if (FAILED(res))
		ERR_MSG(g_hWnd, L"Fail : Register On Minion1");
	m_vMinion.push_back(new CMeleeMinion());
	res = GET_SINGLE(CObjMgr)->AddObject(L"Minion2", m_vMinion[2]);
	if (FAILED(res))
		ERR_MSG(g_hWnd, L"Fail : Register On Minion2");
	
	this->Initialize();
}

void CMinionMgr::SetFirstPositions(const D3DXVECTOR3 * pos)
{

}

	void CMinionMgr::SetHeightMap(CHeightMap ** pHeightMap)
{
	for (CMinion* it : m_vMinion)
		it->SetHeightMap(pHeightMap);
}

void CMinionMgr::Initialize()
{
	GET_SINGLE(SoundMgr)->PlayAnnouncerMention("createminion");
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

#include "BaseInclude.h"
#include "MinionMgr.h"
#include "Minion.h"
#include "SoundManager.h"
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
	m_vMinion.push_back(new CMeleeMinion());
	res = GET_SINGLE(CObjMgr)->AddObject(L"Minion", m_vMinion[0]);
	if (FAILED(res))
		ERR_MSG(g_hWnd, L"Fail : Register On Minion0");
	m_vMinion.push_back(new CMeleeMinion());
	res = GET_SINGLE(CObjMgr)->AddObject(L"Minion", m_vMinion[1]);
	if (FAILED(res))
		ERR_MSG(g_hWnd, L"Fail : Register On Minion1");
	m_vMinion.push_back(new CMeleeMinion());
	res = GET_SINGLE(CObjMgr)->AddObject(L"Minion", m_vMinion[2]);
	if (FAILED(res))
		ERR_MSG(g_hWnd, L"Fail : Register On Minion2");
	
	//GET_SINGLE(SoundManager)->PlayAnnouncerMention("createminion");
	
	this->Initialize();
}

void CMinionMgr::Initialize()
{
	for (auto & it : m_vMinion) {
		it->SetMinionMgr(this);
		int Pos = rand() % 10;
		it->SetPosition(&D3DXVECTOR3((float)Pos, 0.f, 0.f));
		if (FAILED(it->Initialize())) {
			ERR_MSG(g_hWnd, L"Fail : Minion Initialize");
		}
	}
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

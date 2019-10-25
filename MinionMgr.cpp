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
}

void CMinionMgr::CreateMinions()
{
	HRESULT res;
	m_vMinion.push_back(new CMeleeMinion());
	m_vMinion[0]->SetUp("Minion1", "./Resource/Test/", "Minion_Melee_Blue.x");
	res = GET_SINGLE(CObjMgr)->AddObject(m_vMinion[0]->GetName(), m_vMinion[0]);
	if (FAILED(res))
		ERR_MSG(g_hWnd, L"Fail : Register On Minion");
	m_vMinion.push_back(new CMeleeMinion());
	m_vMinion[1]->SetUp("Minion2", "./Resource/Test/", "Minion_Melee_Blue.x"); 
	res = GET_SINGLE(CObjMgr)->AddObject(m_vMinion[1]->GetName(), m_vMinion[1]);
	if (FAILED(res))
		ERR_MSG(g_hWnd, L"Fail : Register On Minion");
	m_vMinion.push_back(new CMeleeMinion());
	m_vMinion[2]->SetUp("Minion3", "./Resource/Test/", "Minion_Melee_Blue.x");
	res = GET_SINGLE(CObjMgr)->AddObject(m_vMinion[2]->GetName(), m_vMinion[2]);
	if (FAILED(res))
		ERR_MSG(g_hWnd, L"Fail : Register On Minion");
	
	GET_SINGLE(SoundManager)->PlayAnnouncerMention("createminion");
	
	this->Initialize();
}

void CMinionMgr::Initialize()
{
	for (auto & it : m_vMinion) {
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

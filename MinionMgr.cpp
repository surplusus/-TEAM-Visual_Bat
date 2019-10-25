#include "BaseInclude.h"
#include "MinionMgr.h"
#include "Minion.h"
#include "SoundManager.h"
#include "MeleeMinion.h"

CMinionMgr::CMinionMgr()
{

}


CMinionMgr::~CMinionMgr()
{
	for (auto & it : m_vMinion)
		it->Release();
	m_vMinion.clear();
}

void CMinionMgr::CreateMinions()
{
	m_vMinion.push_back(new CMeleeMinion());
	m_vMinion[0]->SetUp("Minion1", "./Resource/Test/", "Minion_Melee_Blue.x");
	m_vMinion.push_back(new CMeleeMinion());
	m_vMinion[1]->SetUp("Minion1", "./Resource/Test/", "Minion_Melee_Blue.x"); 
	m_vMinion.push_back(new CMeleeMinion());
	m_vMinion[2]->SetUp("Minion1", "./Resource/Test/", "Minion_Melee_Blue.x");
	
	GET_SINGLE(SoundManager)->PlayAnnouncerMention("createminion");
	
	this->Initialize();
}

void CMinionMgr::Initialize()
{
	for (auto & it : m_vMinion) {
		if (FAILED(it->Initialize()))
			ERR_MSG(g_hWnd, L"Fail : Minion Initialize");
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

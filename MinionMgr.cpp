#include "BaseInclude.h"
#include "MinionMgr.h"
#include "Minion.h"
#include "SoundManager.h"

MinionMgr::MinionMgr()
{
	Minion* pNewMinion1 = new Minion("m1", "minion.x");
	m_vMinion.push_back(pNewMinion1);
	Minion* pNewMinion2 = new Minion("m2", "minion.x");
	m_vMinion.push_back(pNewMinion2);
	Minion* pNewMinion3 = new Minion("m3", "minion.x");
	m_vMinion.push_back(pNewMinion3);
	//GET_SINGLE(SoundManager)->PlayAnnouncerMention("createminion");
}


MinionMgr::~MinionMgr()
{
	for (auto & it : m_vMinion)
		it->Release();
	m_vMinion.clear();
}

void MinionMgr::Initialize()
{
	for (auto & it : m_vMinion)
		it->Initialize();
}

void MinionMgr::Progress()
{
	for (auto & it : m_vMinion)
		it->Progress();
}

void MinionMgr::Render()
{
	for (auto & it : m_vMinion)
		it->Render();
}

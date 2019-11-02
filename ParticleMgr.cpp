#include "BaseInclude.h"
#include "ParticleMgr.h"
#include"ParticleObj.h"
#include"ColiderComponent.h"
CParticleMgr::CParticleMgr()
{

}


CParticleMgr::~CParticleMgr()
{
}

void CParticleMgr::AddParticle(CObj* pObjectName, CParticle * pParticle)
{
	if (m_MapParticle.empty())
	{
		list<CParticle*>* List = new list<CParticle*>;
		List->push_back(pParticle);
		m_MapParticle.insert(make_pair(pObjectName, List));
		return;
	}
	map<CObj*, list<CParticle*>*>::iterator iter = m_MapParticle.find(pObjectName);
	if (iter != m_MapParticle.end())
	{
		m_MapParticle[pObjectName]->push_back(pParticle);
	}
	else
	{
		list<CParticle*>* List = new list<CParticle*>;
		List->push_back(pParticle);
		m_MapParticle.insert(make_pair(pObjectName, List));
	}
}

void CParticleMgr::InsertColList(CObj* pObj,list<ColiderComponent*>* pColList)
{
	
	map<CObj*, list<ColiderComponent*>*>::iterator iter = m_pColiderMap.find(pObj);
	if (iter != m_pColiderMap.end())
	{
		m_pColiderMap.insert(make_pair(pObj,pColList));
	}
	else
	{
		m_pColiderMap[pObj] = pColList;
	}

}

void CParticleMgr::Initalize()
{
	map<CObj*, list<CParticle*>*>::iterator iter = m_MapParticle.begin();
	for (iter; iter != m_MapParticle.end(); ++iter)
	{
		list<CParticle*>::iterator iter2 = iter->second->begin();
		for (iter2; iter2 != iter->second->end(); iter2++)
		{
			(*iter2)->Initalize();
		}
	}
}

void CParticleMgr::Release()
{
}

void CParticleMgr::Render()
{
	map<CObj*, list<CParticle*>*>::iterator iter = m_MapParticle.begin();
	for (iter; iter != m_MapParticle.end(); ++iter)
	{
		list<CParticle*>::iterator iter2 = iter->second->begin();
		for (iter2; iter2!= iter->second->end(); iter2++)
		{
			(*iter2)->Render();
		}
	}
}

void CParticleMgr::Progress()
{
	map<CObj*, list<CParticle*>*>::iterator iter =  m_MapParticle.begin();
	for (iter; iter != m_MapParticle.end(); ++iter)
	{
		list<CParticle*>::iterator iter2 = m_MapParticle[iter->first]->begin();
		if (iter->second == NULL) continue;
		for (iter2; iter2 != iter->second->end(); )
		{
			if (!(*iter2)->Progress())
			{
				list<ColiderComponent*>::iterator it2 = find(m_pColiderMap[iter->first]->begin(), m_pColiderMap[iter->first]->end(), ((CParticleObj*)(*iter2))->GetColider());
				if (it2 != m_pColiderMap[iter->first]->end())
					it2 = m_pColiderMap[iter->first]->erase(it2);
					
			
				SAFE_DELETE(*iter2);				
				iter2 = m_MapParticle[iter->first]->erase(iter2);

			
			}
			else iter2++;
		}
	}
}

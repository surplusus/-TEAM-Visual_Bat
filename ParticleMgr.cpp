#include "BaseInclude.h"
#include "ParticleMgr.h"
#include "ParticleObj.h"
#include "ColiderComponent.h"
#include "EventMgr.h"
CParticleMgr::CParticleMgr()
{
	GET_SINGLE(EventMgr)->Subscribe(this, &CParticleMgr::InsertColliderList);
	GET_SINGLE(EventMgr)->Subscribe(this, &CParticleMgr::EraseColliderInList);
}


CParticleMgr::~CParticleMgr()
{
	GET_SINGLE(EventMgr)->Unsubscribe(this, &CParticleMgr::InsertColliderList);
	GET_SINGLE(EventMgr)->Unsubscribe(this, &CParticleMgr::EraseColliderInList);
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
		for (iter2; iter2 != iter->second->end(); )
		{
			if (!(*iter2)->Progress())
			{
				CParticleObj *pObj = dynamic_cast<CParticleObj*>(*iter2);
				if (pObj)
				{
					pObj->GetColider()->SetStateCol(true);
				}
				iter2 =m_MapParticle[iter->first]->erase(iter2);
			}
			else iter2++;
		}
	}
}

void CParticleMgr::InsertColliderList(INSERTCOLLIDEREVENT * evt)
{
	auto obj = reinterpret_cast<CObj*>(*evt->m_pNewObj);
	auto list = reinterpret_cast<std::list<ColiderComponent*>*>(*evt->m_pNewList);
	InsertColList(obj, list);
}

void CParticleMgr::EraseColliderInList(OBJDIEEVENT * evt)
{
	auto obj = reinterpret_cast<CObj*>(*evt->m_pObj);
	auto part_it = m_MapParticle.find(obj);
	auto coll_it = m_pColiderMap.find(obj);

	if ((part_it == m_MapParticle.end()) && (coll_it == m_pColiderMap.end()))
		cout << "콜라이더 지울게 없어용~\n";
	
	if (part_it != m_MapParticle.end())
		m_MapParticle.erase(obj);
	if (coll_it != m_pColiderMap.end())
		m_pColiderMap.erase(obj);
}

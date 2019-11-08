#include "BaseInclude.h"
#include "CollisionMgr.h"
#include"ColiderComponent.h"
#include"EventMgr.h"
#include"Obj.h"
#include"Input.h"
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::InsertColistion(CObj * pObj, list<ColiderComponent*>* pList)
{
	map<CObj*, list<ColiderComponent*>*>::iterator iter = m_ColMap.find(pObj);
	if (iter == m_ColMap.end())
	{
		list<ColiderComponent*>* List = pList;
		m_ColMap.insert(make_pair(pObj, List));
	}
	else
	{
		iter->second = pList;
	}
}

void CCollisionMgr::Progress()
{
	UpdateColistion();	
}

void CCollisionMgr::Render()
{
	map<CObj*, list<ColiderComponent*>*>::iterator iter1 = m_ColMap.begin();
	for (iter1; iter1 != m_ColMap.end(); ++iter1)
	{
		list<ColiderComponent*>::iterator ListIter1 = m_ColMap[iter1->first]->begin();
		for(ListIter1; ListIter1 != m_ColMap[iter1->first]->end(); ListIter1++) {			
			(*ListIter1)->Render();
		}
	}
}



void CCollisionMgr::UpdateColistion()
{
	for (map<CObj*, list<ColiderComponent*>*>::iterator iter1 = m_ColMap.begin();
		iter1 != m_ColMap.end(); ++iter1)
	{
		for (list<ColiderComponent*>::iterator pOrigin = m_ColMap[iter1->first]->begin();
			pOrigin != m_ColMap[iter1->first]->end();pOrigin++)
		{
			bool bCol = false;
		for (map<CObj*, list<ColiderComponent*>*>::iterator iter2 = m_ColMap.begin()
			;iter2 != m_ColMap.end(); ++iter2)
		{
			if (iter1->first == iter2->first)		
				continue;		

			
				for (list<ColiderComponent*>::iterator pTarget = m_ColMap[iter2->first]->begin();
					pTarget != m_ColMap[iter2->first]->end(); pTarget++)
				{
					if (m_ColMap[iter1->first]->size() == 0) break;
					if (pOrigin == m_ColMap[iter1->first]->end()) break;
					if ((*pOrigin) == (*pTarget))
					{
						pTarget++;	continue;
					}

					//origin이 파티클 임
					if ((*pOrigin)->GetType() == COLISION_TYPE_PARTICLE)
					{//target이 오브젝트임(챔피언)
						if ((*pOrigin)->CheckColision(*pTarget))
						{									//iter1 = origin , iter2 : Target
							GET_SINGLE(EventMgr)->Publish(new COLLISIONEVENT((iter2->first), (*pOrigin)));							
						}					
					}
				}			
			}
		}
	}
}

bool CCollisionMgr::PickColition()
{
	for (map<CObj*, list<ColiderComponent*>*>::iterator iter1 = m_ColMap.begin();
		iter1 != m_ColMap.end(); ++iter1)
	{
		for(list<ColiderComponent*>::iterator pOrigin = m_ColMap[iter1->first]->begin();
			pOrigin!=m_ColMap[iter1->first]->end();++pOrigin)
		
		if (GET_SINGLE(CInput)->CheckPickingOnSphere((*pOrigin)->GetSphere()))
		{
			return true;
		}
	}
	return false;
}

void CCollisionMgr::UpdateCollisionList(CObj * pObj, list<ColiderComponent*>* pList)
{
	map<CObj*, list<ColiderComponent*>*>::iterator iter = m_ColMap.find(pObj);
	if (iter == m_ColMap.end())
	{
		list<ColiderComponent*>* List = pList;
		m_ColMap.insert(make_pair(pObj, List));
	}
	else
	{
		iter->second = pList;
	}
}


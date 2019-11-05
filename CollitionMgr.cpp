#include "BaseInclude.h"
#include "CollitionMgr.h"
#include"ColiderComponent.h"
#include"EventMgr.h"
#include"Obj.h"
CCollitionMgr::CCollitionMgr()
{
}


CCollitionMgr::~CCollitionMgr()
{
}

void CCollitionMgr::InsertColistion(CObj * pObj, list<ColiderComponent*>* pList)
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

void CCollitionMgr::Progress()
{
	UpdateColistion();	
}

void CCollitionMgr::Render()
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



void CCollitionMgr::UpdateColistion()
{
	for (map<CObj*, list<ColiderComponent*>*>::iterator iter1 = m_ColMap.begin();
		iter1 != m_ColMap.end(); ++iter1)
	{
		list<ColiderComponent*>::iterator pOrigin = m_ColMap[iter1->first]->begin();

		for (map<CObj*, list<ColiderComponent*>*>::iterator iter2 = m_ColMap.begin()
			;iter2 != m_ColMap.end(); ++iter2)
		{
			if (iter1->first == iter2->first)		
				continue;		

			for (pOrigin; pOrigin != m_ColMap[iter1->first]->end();)
			{
				bool bCol = false;
				for (list<ColiderComponent*>::iterator pTarget = m_ColMap[iter2->first]->begin();
					pTarget != m_ColMap[iter2->first]->end(); pTarget++)
				{
					if ((*pOrigin) == (*pTarget)) continue;
					if ((*pOrigin)->GetType() == COLISION_TYPE_PARTICLE)
					{
						if ((*pOrigin)->CheckColision(*pTarget))
						{
							GET_SINGLE(EventMgr)->Publish(new COLLISIONEVENT((iter1->first), (iter2->first), (*pOrigin), (*pTarget)));
							pOrigin =m_ColMap[iter1->first]->erase(pOrigin);
							bCol = true;
							if (pOrigin == m_ColMap[iter1->first]->end()) break;

						}
					}
				}
				if (!bCol) pOrigin++;
			}
		}
	}


}

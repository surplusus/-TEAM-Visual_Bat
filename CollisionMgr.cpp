#include "BaseInclude.h"
#include "CollisionMgr.h"
#include "ColiderComponent.h"
#include "EventMgr.h"
#include "Obj.h"
#include "Input.h"

CCollisionMgr::CCollisionMgr()
{
	GET_SINGLE(EventMgr)->Subscribe(this, &CCollisionMgr::InsertColliderList);
	GET_SINGLE(EventMgr)->Subscribe(this, &CCollisionMgr::EraseColliderInList);
}


CCollisionMgr::~CCollisionMgr()
{
	GET_SINGLE(EventMgr)->Unsubscribe(this, &CCollisionMgr::InsertColliderList);
	GET_SINGLE(EventMgr)->Unsubscribe(this, &CCollisionMgr::EraseColliderInList);
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
			if((*ListIter1)!=NULL)
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
			pOrigin != m_ColMap[iter1->first]->end(); pOrigin++)
		{
			for (map<CObj*, list<ColiderComponent*>*>::iterator iter2 = m_ColMap.begin()
				; iter2 != m_ColMap.end(); ++iter2)
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
					if (*pTarget == NULL) continue;

					//origin이 파티클 임
					if ((*pOrigin)->GetType() == COLISION_TYPE_PARTICLE && (*pTarget)->GetType() == COLISION_TYPE_PARTICLE)
						continue;
					if ((*pOrigin)->CheckColision(*pTarget))
					{						
						//iter1 = origin , iter2 : Target
						GET_SINGLE(EventMgr)->Publish(new COLLISIONEVENT( (iter1->first), (*pOrigin),(iter2->first),(*pTarget)));
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

void CCollisionMgr::InsertColliderList(INSERTCOLLIDEREVENT * evt)
{
	auto obj = reinterpret_cast<CObj*>(*evt->m_pNewObj);
	auto list = reinterpret_cast<std::list<ColiderComponent*>*>(*evt->m_pNewList);
	InsertColistion(obj, list);
}

void CCollisionMgr::EraseColliderInList(OBJDIEEVENT * evt)
{
	auto obj = reinterpret_cast<CObj*>(*evt->m_pObj);
	auto it = m_ColMap.find(obj);
	if (it != m_ColMap.end())
		m_ColMap.erase(obj);
	else
		cout << "콜라이더 지울게 없어용~\n";
}

bool CCollisionMgr::IsCloseObjInRadius(OUT vector<CObj*>* vCloseObj, IN CObj* pMe, IN const D3DXVECTOR3 * vecMyPos, IN float fRadius)
{
	if (vCloseObj == nullptr || vecMyPos == nullptr)
		return false;

	for (auto & it : m_ColMap)
	{
		if (it.first == pMe)
			continue;

		for (auto & jt : *it.second)
		{
			auto pos = it.first->GetInfo()->vPos;
			float distance = D3DXVec3Length(&((*vecMyPos) - pos));
				if (fRadius >= distance)
					vCloseObj->push_back(it.first);
		}
	}

	if (vCloseObj->size() == 0)
		return false;

	return true;
}


bool CCollisionMgr::IsCloseSphereInRadius(OUT vector<SPHERE*>* vCloseSphere, IN CObj * pMe, IN const D3DXVECTOR3 * vecMyPos, IN float fRadius)
{
	if (vCloseSphere == nullptr || vecMyPos == nullptr)
		return false;

	for (auto & it : m_ColMap)
	{
		if (it.first == pMe)
			continue;

		for (auto & jt : *it.second)
		{
			SPHERE* spOthers = jt->GetSphere();
			D3DXVECTOR3 vecDist = (*vecMyPos) - (*spOthers->vpCenter);
			float distance = D3DXVec3Length(&vecDist);
			if (fRadius >= distance)
				vCloseSphere->push_back(spOthers);
		}
	}

	if (vCloseSphere->size() == 0)
		return false;

	return true;
}


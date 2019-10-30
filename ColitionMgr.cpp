#include "BaseInclude.h"
#include "ColitionMgr.h"
#include"ColiderComponent.h"
#include"Obj.h"
CColitionMgr::CColitionMgr()
{
}


CColitionMgr::~CColitionMgr()
{
}

void CColitionMgr::InsertColistion(CObj * pObj, ColiderComponent * pComponent)
{
	map<CObj*, list<ColiderComponent*>*>::iterator iter = m_ColMap.find(pObj);
	if (iter == m_ColMap.end())
	{
		list<ColiderComponent*>* List = new list<ColiderComponent*>;
		List->push_back(pComponent);
		m_ColMap.insert(make_pair(pObj, List));
	}
	else
	{
		iter->second->push_back(pComponent);
	}
}

void CColitionMgr::Progress()
{
	RemoveColiderComponent();
	map<CObj*, list<ColiderComponent*>*>::iterator iter1 = m_ColMap.begin();
	for (iter1; iter1 != m_ColMap.end(); ++iter1)
	{
		list<ColiderComponent*>::iterator ListIter1 = m_ColMap[iter1->first]->begin();
		for (ListIter1; ListIter1 != m_ColMap[iter1->first]->end(); ListIter1++) {
			
		}
	}
}

void CColitionMgr::Render()
{
	map<CObj*, list<ColiderComponent*>*>::iterator iter1 = m_ColMap.begin();
	for (iter1; iter1 != m_ColMap.end(); ++iter1)
	{
		list<ColiderComponent*>::iterator ListIter1 = m_ColMap[iter1->first]->begin();
		for(ListIter1; ListIter1 != m_ColMap[iter1->first]->end(); ListIter1++) {
			if ((*ListIter1)->GetObj() == NULL)
				(*ListIter1)->Render();
		}
	}
}

void CColitionMgr::RemoveColiderComponent()
{
	map<CObj*, list<ColiderComponent*>*>::iterator iter1 = m_ColMap.begin();
	for (iter1; iter1 != m_ColMap.end(); ++iter1)
	{
		list<ColiderComponent*>::iterator ListIter1 = m_ColMap[iter1->first]->begin();
		if (*ListIter1 == NULL) {
			m_ColMap[iter1->first]->erase(ListIter1);
		}
	}

}

void CColitionMgr::UpdateColistion()
{
	//����Ʈ�ȿ��� �ڽ��� �ٸ� ������Ʈ���� �浹��ų ��ü�� ���� �������� ����
	map<CObj*, list<ColiderComponent*>*>::iterator iter1 = m_ColMap.begin();
	//�浹ó���� ���
	map<CObj*, list<ColiderComponent*>*>::iterator iter2 = m_ColMap.begin();

	for (iter1; iter1 != m_ColMap.end(); ++iter1)
	{
		list<ColiderComponent*>::iterator ListIter1 = m_ColMap[iter1->first]->begin();
		for (iter2; iter2 != m_ColMap.end(); ++iter2)
		{
			if (iter1 == iter2) break;
			list<ColiderComponent*>::iterator ListIter2 = m_ColMap[iter1->first]->begin();
			if ((*ListIter2)->GetObj() != NULL)
			{
				if ((*ListIter1)->CheckColision((*ListIter2)))
				{
					//�浹�ߴ�	
				}
			}
		}
	}
}

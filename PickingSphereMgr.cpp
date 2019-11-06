#include "BaseInclude.h"
#include "PickingSphereMgr.h"
#include "EventMgr.h"

CPickingSphereMgr::CPickingSphereMgr()
{
}


CPickingSphereMgr::~CPickingSphereMgr()
{
}

bool CPickingSphereMgr::AddSphere(CObj * hash, SPHERE * sphere)
{
	if (hash == nullptr || sphere == nullptr)
		return false;
	
	m_vPickingSpheres.insert(make_pair(hash, sphere));
	return true;
}

bool CPickingSphereMgr::GetSpherePicked(CObj* me, OUT SPHERE** sphere)
{
	for (auto & it : m_vPickingSpheres) {
		if (it.first == me)
			continue;
		if (CheckPickingOnSphere(it.second)) {
			*sphere = it.second;
			GET_SINGLE(EventMgr)->Publish(new PICKSPHEREEVENT(it.first));
			return true;
		}
	}
	return false;
}

void CPickingSphereMgr::SelectEraseSphere(CObj * me, SPHERE * pSphere)
{
	unordered_map<CObj*, SPHERE*>::iterator iter = m_vPickingSpheres.find(me);
	if (iter != m_vPickingSpheres.end())
	{
		iter =m_vPickingSpheres.erase(iter);
	}
}

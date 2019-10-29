#pragma once
class CPickingSphereMgr
{
	DECLARE_SINGLETON(CPickingSphereMgr);
private:
	CPickingSphereMgr();
	~CPickingSphereMgr();
private:
	unordered_map<CObj*, SPHERE*> m_vPickingSpheres;
public:
	bool AddSphere(CObj* hash, SPHERE* sphere);
	bool GetSpherePicked(CObj* me, OUT SPHERE** sphere);
};


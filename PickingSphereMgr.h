#pragma once
class CPickingSphereMgr
{
	DECLARE_SINGLETON(CPickingSphereMgr);
private:
	CPickingSphereMgr();
	~CPickingSphereMgr();
private:
	unordered_map<string, SPHERE*> m_vPickingSpheres;
public:
	bool AddSphere(string hash, SPHERE* sphere);
	
};


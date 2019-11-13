#pragma once
class ColiderComponent;
class CCollisionMgr
{
	DECLARE_SINGLETON(CCollisionMgr)
private:
	CCollisionMgr();
public:
	~CCollisionMgr();
private:	
	map<CObj*, list<ColiderComponent*>*> m_ColMap;
public:
	void InsertColistion(CObj* pObj, list<ColiderComponent*>* pList);
	void Progress();
	void Render();
private:
	void UpdateColistion();
public:
	bool PickColition();
	void UpdateCollisionList(CObj* pObj,list<ColiderComponent*>*);
public:
	// 구현이 새로 제안하는 Collision 처리
	void InsertColliderList(INSERTCOLLIDEREVENT* evt);
	void EraseColliderInList(OBJDIEEVENT* evt);
	bool IsCloseObjInRadius(OUT vector<CObj*>* vCloseObj, IN CObj* pMe, IN const D3DXVECTOR3* vecMyPos, IN float fRadius = 0);
	bool IsCloseSphereInRadius(OUT vector<SPHERE*>* vCloseSphere, IN CObj* pMe, IN const D3DXVECTOR3* vecMyPos, IN float fRadius = 0);
};


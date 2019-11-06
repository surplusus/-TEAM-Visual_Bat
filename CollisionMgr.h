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

};


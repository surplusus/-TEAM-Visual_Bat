#pragma once
class ColiderComponent;
class CCollitionMgr
{
	DECLARE_SINGLETON(CCollitionMgr)
private:
	CCollitionMgr();
public:
	~CCollitionMgr();
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


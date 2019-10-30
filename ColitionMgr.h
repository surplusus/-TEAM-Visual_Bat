#pragma once
class ColiderComponent;
class CColitionMgr
{
	DECLARE_SINGLETON(CColitionMgr);
private:
	CColitionMgr();
public:
	~CColitionMgr();
private:
	map<CObj*, list<ColiderComponent*>*> m_ColMap;
public:
	void InsertColistion(CObj* pObj, ColiderComponent* pComponent);
	void Progress();
	void Render();
private:
	void RemoveColiderComponent();
	void UpdateColistion();
};


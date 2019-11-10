#pragma once
class CParticle;
class CObj;
class ColiderComponent;
class CParticleMgr
{
	DECLARE_SINGLETON(CParticleMgr);
private:
	CParticleMgr();
public:
	~CParticleMgr();
private:
	map<CObj*, list<CParticle*>*> m_MapParticle;
	map<CObj*,list<ColiderComponent*>*> m_pColiderMap;
public:
	void AddParticle(CObj*, CParticle* pParticle);
	void InsertColList(CObj* pObj,list<ColiderComponent*>* pColList);
public:
	void Initalize();
	void Release();
	void Render();
	void Progress();
	// 구현이 새로 제안하는 Collision 처리
private:
	void InsertColliderList(INSERTCOLLIDEREVENT* evt);
};


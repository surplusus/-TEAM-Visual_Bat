#pragma once
class CParticle;
class CParticleMgr
{
	DECLARE_SINGLETON(CParticleMgr);
private:
	CParticleMgr();
public:
	~CParticleMgr();
private:
	map<const TCHAR*, list<CParticle*>*> m_MapParticle;

public:
	void AddParticle(const TCHAR* pObjectName, CParticle* pParticle);
public:
	void Initalize();
	void Release();
	void Render();
	void Progress();

};


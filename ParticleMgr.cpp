#include "BaseInclude.h"
#include "ParticleMgr.h"
#include"Particle.h"

CParticleMgr::CParticleMgr()
{

}


CParticleMgr::~CParticleMgr()
{
}

void CParticleMgr::AddParticle(const TCHAR * pObjectName, CParticle * pParticle)
{
	if (m_MapParticle.empty())
	{
		list<CParticle*>* List = new list<CParticle*>;
		List->push_back(pParticle);
		m_MapParticle.insert(make_pair(pObjectName, List));
		return;
	}
	map<const TCHAR*, list<CParticle*>*>::iterator iter = m_MapParticle.find(pObjectName);	
	if (iter != m_MapParticle.end())
	{
		m_MapParticle[pObjectName]->push_back(pParticle);
	}
	else
	{
		list<CParticle*>* List = new list<CParticle*>;
		List->push_back(pParticle);
		m_MapParticle.insert(make_pair(pObjectName, List));
	}
}

void CParticleMgr::Initalize()
{
	map<const TCHAR*, list<CParticle*>*>::iterator iter = m_MapParticle.begin();
	for (iter; iter != m_MapParticle.end(); ++iter)
	{
		list<CParticle*>::iterator iter2 = iter->second->begin();
		for (iter2; iter2 != iter->second->end(); iter2++)
		{
			(*iter2)->Initalize();
		}
	}
}

void CParticleMgr::Release()
{
}

void CParticleMgr::Render()
{
	map<const TCHAR*, list<CParticle*>*>::iterator iter = m_MapParticle.begin();
	for (iter; iter != m_MapParticle.end(); ++iter)
	{
		list<CParticle*>::iterator iter2 = iter->second->begin();
		for (iter2; iter2!= iter->second->end(); iter2++)
		{
			(*iter2)->Render();
		}
	}
}

void CParticleMgr::Progress()
{
	map<const TCHAR*, list<CParticle*>*>::iterator iter =  m_MapParticle.begin();
	for (iter; iter != m_MapParticle.end(); ++iter)
	{
		list<CParticle*>::iterator iter2 = iter->second->begin();
		for (iter2; iter2 != iter->second->end(); iter2++)
		{
			(*iter2)->Progress();
		}
	}
}

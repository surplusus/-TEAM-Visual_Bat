#include "BaseInclude.h"
#include "ParticleMgr.h"
#include "LineLazer.h"

HRESULT CParticleMgr::AddParticle(LPDIRECT3DDEVICE9 pDevice, TCHAR * pParticleKey, PARTICLETYPE eType)
{
	map<const TCHAR*, CParticle*>::iterator iter = m_MapParticle.find(pParticleKey);
	if (iter != m_MapParticle.end()) return E_FAIL;

	CParticle* pParticle = NULL;

	switch (eType)
	{
		break;
	default:
		break;
	}
	if (FAILED(pParticle->InitParticleBuffer(pDevice))) return E_FAIL;

	m_MapParticle.insert(make_pair(pParticleKey, pParticle));
	return S_OK;
}

void CParticleMgr::Progress(const TCHAR* pParticleKey)
{
	map<const TCHAR*, CParticle*>::iterator	iter = m_MapParticle.find(pParticleKey);

	if (iter == m_MapParticle.end())
		return;

	iter->second->Progress();
}

void CParticleMgr::Render(LPDIRECT3DDEVICE9 pDevice
	, const TCHAR* pParticleKey)
{
	map<const TCHAR*, CParticle*>::iterator	iter = m_MapParticle.find(pParticleKey);

	if (iter == m_MapParticle.end())	return;

	iter->second->Render(pDevice);
}

void CParticleMgr::Release(void)
{
	for (map<const TCHAR*, CParticle*>::iterator	iter = m_MapParticle.begin();
		iter != m_MapParticle.end(); ++iter)
	{
		if (iter->second)
		{
			delete iter->second;
			iter->second = NULL;
		}
	}
	m_MapParticle.clear();

}

CParticleMgr::CParticleMgr()
{
}

CParticleMgr::~CParticleMgr()
{
	Release();
}


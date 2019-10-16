#pragma once
class CParticle;
class CParticleMgr
{
	DECLARE_SINGLETON(CParticleMgr);
private:
	map<const TCHAR*, CParticle*>	m_MapParticle;
public:
	HRESULT AddParticle(LPDIRECT3DDEVICE9 pDevice
		, TCHAR* pParticleKey
		, PARTICLETYPE eType);
	void Render(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pParticleKey);
	void Progress(const TCHAR* pParticleKey);
	void Release();
private:
	CParticleMgr();
public:
	~CParticleMgr();

};


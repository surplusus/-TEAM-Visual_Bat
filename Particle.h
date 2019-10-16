#pragma once
typedef struct tagAttribute
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3	vDirection;
	DWORD		dwColor;
	bool		bAlive;
}ATTRIBUTE;
class CParticle
{
protected:
	list<ATTRIBUTE*>		m_AttributeList;
	DWORD					m_dwParticleCnt;
protected:
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	DWORD					m_dwVtxSize;
	DWORD					m_dwTotalVtxCnt;

	DWORD					m_dwVtxFVF;
	DWORD					m_dwOffset;
	DWORD					m_dwBlockCnt;
	INFO					m_ObjInfo;
public:
	void AddParticle();//

protected:
	virtual void	SettingRender();//파티클 발생전에 랜더에서 해주어야할 설정
public:
	virtual HRESULT	InitParticleBuffer(LPDIRECT3DDEVICE9 pDevice);
	virtual void	Render(LPDIRECT3DDEVICE9 pDevice);
	virtual void	End_Render();
	virtual void	ResetParticle(ATTRIBUTE * pAttribute)	PURE;
	virtual void	Release();
	virtual void Progress(void) {}

public:
	CParticle();
	virtual ~CParticle();

};


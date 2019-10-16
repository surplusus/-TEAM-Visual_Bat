#include "BaseInclude.h"
#include "Particle.h"

CParticle::CParticle()
	:m_dwOffset(0)
{
}


CParticle::~CParticle()
{
	Release();
}


void CParticle::AddParticle()
{
	ATTRIBUTE*	pAttribute = new ATTRIBUTE;
	ResetParticle(pAttribute);
	m_AttributeList.push_back(pAttribute);
}

HRESULT CParticle::InitParticleBuffer(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(pDevice->CreateVertexBuffer(m_dwVtxSize* m_dwTotalVtxCnt
		, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS
		, m_dwVtxFVF, D3DPOOL_DEFAULT, &m_pVB, NULL)))
		return E_FAIL;
	return S_OK;
}

void CParticle::SettingRender()
{

	SetRenderState(D3DRS_LIGHTING, false);

	float				fSize = 1.f;

	SetRenderState(D3DRS_POINTSIZE, *(DWORD*)&fSize);

	SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);

	SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);

	float				fSizeA = 0.f;
	float				fSizeB = 0.f;
	float				fSizeC = 0.5f;

	SetRenderState(D3DRS_POINTSCALE_A, *(DWORD*)&fSizeA);
	SetRenderState(D3DRS_POINTSCALE_B, *(DWORD*)&fSizeB);
	SetRenderState(D3DRS_POINTSCALE_C, *(DWORD*)&fSizeC);

	SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	SetRenderState(D3DRS_ALPHAREF, TRUE);
	SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

void CParticle::Render(LPDIRECT3DDEVICE9 pDevice)
{
	if (m_AttributeList.empty()) return;
	const TEXINFO* pTexInfo = GetTexture(L"Particle",L"Snow");
	if (pTexInfo == NULL) return;

	SettingRender();

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	SetTransform(D3DTS_WORLD, &mat);
	pDevice->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	SetTexture(0, pTexInfo->pTexture);
	pDevice->SetFVF(m_dwVtxFVF);
	if (m_dwOffset >= m_dwTotalVtxCnt) m_dwOffset = 0;


	PARTICLEVTX * pVtx = NULL;

	m_pVB->Lock(m_dwOffset * m_dwVtxSize
		,m_dwBlockCnt * m_dwVtxSize
		,(void**)&pVtx
		,m_dwOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);
	int iCnt =0 ;
	
	for (list<ATTRIBUTE*>::iterator iter = m_AttributeList.begin();
		iter != m_AttributeList.end(); ++iter)
	{
		if ((*iter)->bAlive)
		{
			pVtx->vPosition = (*iter)->vPosition;
			pVtx->dwColor = (*iter)->dwColor;
			++pVtx;
			++iCnt;
			if ((DWORD)iCnt >= m_dwBlockCnt)
			{
				m_pVB->Unlock();
				pDevice->DrawPrimitive(D3DPT_POINTLIST, m_dwOffset, m_dwBlockCnt);
				m_dwOffset += m_dwBlockCnt;

				if (m_dwOffset >= m_dwTotalVtxCnt) m_dwOffset = 0;

				m_pVB->Lock(m_dwOffset *m_dwVtxSize
					, m_dwBlockCnt*m_dwVtxSize
					, (void**)&pVtx
					, m_dwOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);
				iCnt = 0;
			}
		}
	}
	m_pVB->Unlock();
	if (iCnt)
		pDevice->DrawPrimitive(D3DPT_POINTLIST, m_dwOffset, iCnt);
	
	m_dwOffset = 0;
	End_Render();
}

void CParticle::End_Render()
{

	SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CParticle::Release()
{

	for (list<ATTRIBUTE*>::iterator	iter = m_AttributeList.begin();
		iter != m_AttributeList.end(); ++iter)
	{
		if ((*iter))
		{
			delete *iter;
			*iter = NULL;
		}
	}
	m_AttributeList.clear();

	if (m_pVB)
		m_pVB->Release();
}

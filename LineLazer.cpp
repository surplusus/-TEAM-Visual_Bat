#include "BaseInclude.h"
#include "LineLazer.h"


CLineLazer::CLineLazer()
	: m_fSpeed(1.0f)
{
}

CLineLazer::CLineLazer(INFO & Info)
	: m_fSpeed(1.0f), m_Info(Info)
{
	AddParticle();
}


CLineLazer::~CLineLazer()
{

}

HRESULT CLineLazer::InitParticleBuffer(LPDIRECT3DDEVICE9 pDevice)
{
	m_dwVtxSize = sizeof(PARTICLEVTX);
	m_dwVtxFVF = VTXFVF_PARTICLE;
	m_dwTotalVtxCnt = 600;
	m_dwBlockCnt = 500;

	if (FAILED(CParticle::InitParticleBuffer(pDevice)))		return E_FAIL;
	
	return S_OK;
	
}
														
void CLineLazer::ResetParticle(ATTRIBUTE * pAttribute)
{
	pAttribute->bAlive = true;
	
	pAttribute->vPosition = m_Info.vPos;
	//캐릭터가 바라보는 방향을 집어넣어준다.
	pAttribute->vDirection = m_Info.vDir;

	D3DXVec3Normalize(&pAttribute->vDirection, &pAttribute->vDirection);

	pAttribute->dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}

void CLineLazer::Progress()
{

	for (list<ATTRIBUTE*>::iterator	iter = m_AttributeList.begin();
		iter != m_AttributeList.end();)
	{
		(*iter)->vPosition += (*iter)->vDirection *m_fSpeed* GetTime();


		float fDistance = D3DXVec3Length(&(m_Info.vPos - (*iter)->vPosition));
		if (fDistance > 2.f)
		{
			(*iter)->bAlive = false;
			iter = m_AttributeList.erase(iter);
		}
		else iter++;
	}
}

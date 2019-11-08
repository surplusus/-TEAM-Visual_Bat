#include "BaseInclude.h"
#include "ChampGauge.h"
#include "Image_Loader.h"
#include "ObjMgr.h"


CChampGauge::CChampGauge()
{
	m_MAXHP = 1.0f;
	m_fDmg = 1.0f;
	//m_fDmg = m_fDeal / m_MAXHP;
}


CChampGauge::~CChampGauge()
{
}

void CChampGauge::Initialize()
{
	VTXTEX v;
	v.vPosition = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	v.vTexture = D3DXVECTOR2(0, 1);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v.vTexture = D3DXVECTOR2(0, 0);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	v.vTexture = D3DXVECTOR2(1, 1);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);


	//À­ÂÊ »ï°¢Çü
	v.vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	v.vTexture = D3DXVECTOR2(1, 0);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	v.vTexture = D3DXVECTOR2(1, 1);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	v.vTexture = D3DXVECTOR2(0, 0);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);
}

void CChampGauge::Progress()
{	
	if (GetAsyncKeyState(VK_LSHIFT))
	{
		m_fDmg -= 0.01f;
		if (m_fDmg < 0.0f)
			m_fDmg = 0.0f;
	}
	if (GetAsyncKeyState(VK_RETURN))
	{
		m_fDmg += 0.01f;
		if (m_fDmg > 1.0f)
			m_fDmg = 1.0f;
	}
}

void CChampGauge::Render()
{
	RenderBlankGauge(m_vecMultiVertex, m_stInfo.vPos.y, D3DXVECTOR3(1.0f, 0.1f, 1.0f));
	RenderCellGauge (m_vecMultiVertex, m_stInfo.vPos.y, D3DXVECTOR3(1.0f, 0.1f, 1.0f), m_fDmg);
}

void CChampGauge::Release()
{
	SAFE_RELEASE(m_pBlank);
	SAFE_RELEASE(m_pCell);
}

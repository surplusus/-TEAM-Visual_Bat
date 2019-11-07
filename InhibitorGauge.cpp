#include "BaseInclude.h"
#include "InhibitorGauge.h"


CInhibitorGauge::CInhibitorGauge()
{
	//m_fDmg = m_fDeal / m_MAXHP;
	m_fDmg = 1.0f;
}


CInhibitorGauge::~CInhibitorGauge()
{
}

void CInhibitorGauge::Initialize()
{
	D3DXCreateTextureFromFile(GetDevice(), L"./Resource/choen/UI/BlankGauge.png", &m_pBlank);
	D3DXCreateTextureFromFile(GetDevice(), L"./Resource/choen/UI/GaugeCell.png", &m_pCell);
	SetLight();
	//¾Æ·§ÂÊ »ï°¢Çü
	VTXTEX v;
	v.vPosition = D3DXVECTOR3(1.0f, 1.0f, 0);
	v.vTexture = D3DXVECTOR2(0, 1);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(0.0f, 1.0f, 0);
	v.vTexture = D3DXVECTOR2(0, 0);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(1.f, 0.0f, 0.0f);
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

void CInhibitorGauge::Progress()
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

void CInhibitorGauge::Render()
{
	RenderBlankGauge(m_vecMultiVertex,  D3DXVECTOR3(m_stInfo.vPos.x, m_stInfo.vPos.y + 5.0f, m_stInfo.vPos.z), D3DXVECTOR3(2.0f, 0.2f, 1.0f));
	RenderCellGauge (m_vecMultiVertex,  D3DXVECTOR3(m_stInfo.vPos.x, m_stInfo.vPos.y + 5.0f, m_stInfo.vPos.z),  D3DXVECTOR3(2.0f * m_fDmg, 0.2f, 1.0f), m_fDmg);
}

void CInhibitorGauge::Release()
{
	SAFE_RELEASE(m_pBlank);
	SAFE_RELEASE(m_pCell);
}

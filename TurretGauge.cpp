#include "BaseInclude.h"
#include "TurretGauge.h"


CTurretGauge::CTurretGauge()
{
	//rest = MaxHP - curHP
	//m_fDmg -= rest / m_MAXHP;
	m_fDmg = 1.0f;
}


CTurretGauge::~CTurretGauge()
{
}

void CTurretGauge::Initialize()
{
	D3DXCreateTextureFromFile(GetDevice(), L"./Resource/choen/UI/BlankGauge.png", &m_pBlank);
	D3DXCreateTextureFromFile(GetDevice(), L"./Resource/choen/UI/GaugeCell.png", &m_pCell);
	SetLight();
	//¾Æ·§ÂÊ »ï°¢Çü
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

void CTurretGauge::Progress()
{
	m_fDmg = m_CurrentHP / m_MAXHP;

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

void CTurretGauge::Render()
{
	RenderBlankGauge(m_vecMultiVertex,m_stInfo.vPos.y + 5.0f, D3DXVECTOR3(3.0f, 0.1f, 1.0f));
	RenderCellGauge(m_vecMultiVertex, m_stInfo.vPos.y + 5.0f, D3DXVECTOR3(3.0f, 0.1f, 1.0f), m_fDmg);
}

void CTurretGauge::Release()
{
	SAFE_RELEASE(m_pBlank);
	SAFE_RELEASE(m_pCell);
}
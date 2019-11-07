#include "BaseInclude.h"
#include "MinionGauge.h"
#include "ObjMgr.h"


CMinionGauge::CMinionGauge()
{
	m_fDmg = 1.0f;
	//m_fDmg = m_fDeal / m_MAXHP;
}


CMinionGauge::~CMinionGauge()
{
}

void CMinionGauge::Initialize()
{
	SetLight();

	SetBlankGauge();
	SetGaugeCell();

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

void CMinionGauge::Progress()
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

void CMinionGauge::Render()
{
	RenderBlankGauge(m_vecMultiVertex, m_stInfo.vPos, D3DXVECTOR3(1.0f, 0.1f, 1.0f));
	RenderCellGauge (m_vecMultiVertex, m_stInfo.vPos, D3DXVECTOR3(1.0f * m_fDmg, 0.1f, 1.0f), m_fDmg);
}

void CMinionGauge::Release()
{
}

void CMinionGauge::SetBlankGauge()
{
	D3DXCreateTextureFromFile(
		GetDevice(),
		L"Resource/choen/UI/BlankGauge.png",
		&m_pBlank
	);
}

void CMinionGauge::SetGaugeCell()
{
	D3DXCreateTextureFromFile(
		GetDevice(),
		L"Resource/choen/UI/GaugeCell.png",
		&m_pCell
	);
}
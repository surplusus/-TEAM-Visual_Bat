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
	//�Ʒ��� �ﰢ��
	VTXTEX v;
	v.vPosition = D3DXVECTOR3(m_vPosition.x + 1.f, m_vPosition.y + 1.f, m_vPosition.z);
	v.vTexture = D3DXVECTOR2(0, 1);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 1.f, m_vPosition.z);
	v.vTexture = D3DXVECTOR2(0, 0);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(m_vPosition.x + 1.f, m_vPosition.y, m_vPosition.z);
	v.vTexture = D3DXVECTOR2(1, 1);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);


	//���� �ﰢ��
	v.vPosition = D3DXVECTOR3(m_vPosition.x, m_vPosition.y, m_vPosition.z);
	v.vTexture = D3DXVECTOR2(1, 0);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(m_vPosition.x + 1.f, m_vPosition.y, m_vPosition.z);
	v.vTexture = D3DXVECTOR2(1, 1);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 1.f, m_vPosition.z);
	v.vTexture = D3DXVECTOR2(0, 0);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);
}

void CInhibitorGauge::Progress()
{
	//if (GetAsyncKeyState(VK_LSHIFT))
	//{
	//	m_fDmg -= 0.01f;
	//	if (m_fDmg < 0.0f)
	//		m_fDmg = 0.0f;
	//}
	//if (GetAsyncKeyState(VK_RETURN))
	//{
	//	m_fDmg += 0.01f;
	//	if (m_fDmg > 1.0f)
	//		m_fDmg = 1.0f;
	//}
}

void CInhibitorGauge::Render()
{
	RenderBlankGauge(m_vecMultiVertex, m_vPosition, D3DXVECTOR3(2.0f, 0.2f, 1.0f));
	RenderCellGauge(m_vecMultiVertex, m_vPosition,  D3DXVECTOR3(2.0f * m_fDmg, 0.2f, 1.0f));
}

void CInhibitorGauge::Release()
{
	SAFE_RELEASE(m_pBlank);
	SAFE_RELEASE(m_pCell);
}

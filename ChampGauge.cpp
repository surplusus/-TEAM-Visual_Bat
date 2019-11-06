#include "BaseInclude.h"
#include "ChampGauge.h"
#include "Image_Loader.h"
#include "ObjMgr.h"


CChampGauge::CChampGauge()
{
	m_MAXHP = 1.0f;
	m_fDmg = 1.0f;
}


CChampGauge::~CChampGauge()
{
}

void CChampGauge::Initialize()
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
	v.vPosition = D3DXVECTOR3(m_vPosition.x , m_vPosition.y, m_vPosition.z);
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
	RenderBlankGauge(m_vecMultiVertex, m_matWorld, m_vPosition, D3DXVECTOR3(m_fDmg, 0.1f, 1.0f));
	RenderCellGauge(m_vecMultiVertex, m_matWorld, m_vPosition, D3DXVECTOR3(m_fDmg, 0.1f, 1.0f));
}

void CChampGauge::Release()
{
	SAFE_RELEASE(m_pBlank);
	SAFE_RELEASE(m_pCell);
}

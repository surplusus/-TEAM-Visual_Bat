#include "BaseInclude.h"
#include "ChampGauge.h"
#include "Image_Loader.h"
#include "ObjMgr.h"

CChampGauge::CChampGauge()
{
	m_MAXHP = 1.0f;
	m_fDmg = 1.0f;
}

CChampGauge::CChampGauge(D3DXVECTOR3 vPos)
{
	m_vPosition = vPos;
}


CChampGauge::~CChampGauge()
{
}

void CChampGauge::Initialize()
{
	SetLight();	
	SetBlankGauge();
	SetGaugeCell();
	//�Ʒ��� �ﰢ��
	VTXTEX v;
	v.vPosition = D3DXVECTOR3(m_vPosition.x - 0.5f, m_vPosition.y + 1.0f, m_vPosition.z);
	v.vTexture = D3DXVECTOR2(0, 1);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(m_vPosition.x - 0.5f, m_vPosition.y + 1.1f, m_vPosition.z);
	v.vTexture = D3DXVECTOR2(0, 0);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(m_vPosition.x + 0.5f, m_vPosition.y + 1.0f, m_vPosition.z);
	v.vTexture = D3DXVECTOR2(1, 1);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);


	//���� �ﰢ��
	v.vPosition = D3DXVECTOR3(m_vPosition.x + 0.5f, m_vPosition.y + 1.1f, m_vPosition.z);
	v.vTexture = D3DXVECTOR2(1, 0);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(m_vPosition.x + 0.5f, m_vPosition.y + 1.0f, m_vPosition.z);
	v.vTexture = D3DXVECTOR2(1, 1);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);

	v.vPosition = D3DXVECTOR3(m_vPosition.x - 0.5f, m_vPosition.y + 1.1f, m_vPosition.z);
	v.vTexture = D3DXVECTOR2(0, 0);
	v.vNormal = D3DXVECTOR3(0, 0, 1);
	m_vecMultiVertex.push_back(v);
}

void CChampGauge::Progress(D3DXVECTOR3 vPos)
{	
	SetPosition(vPos);
	if (GetAsyncKeyState(VK_SPACE))
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
	RenderBlankGauge();
	RenderCellGauge();
}

void CChampGauge::Release()
{
	SAFE_RELEASE(m_pBlank);
	SAFE_RELEASE(m_pCell);
}

void CChampGauge::SetBlankGauge()
{
	D3DXCreateTextureFromFile(GetDevice(), L"./Resource/choen/UI/BlankGauge.png", &m_pBlank);
}

void CChampGauge::SetGaugeCell()
{
	D3DXCreateTextureFromFile(GetDevice(), L"./Resource/choen/UI/GaugeCell.png", &m_pCell);
}

void CChampGauge::RenderBlankGauge()
{
	D3DXMATRIXA16 matWorld, matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y + 1.5f, m_vPosition.z);

	matWorld = matT;

	SetTransform(D3DTS_WORLD, &matWorld);


	SetTexture(0, m_pBlank);

	GET_DEVICE->SetFVF(VTXFVF_VTXTEX);

	HRESULT HR = GET_DEVICE->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		m_vecMultiVertex.size() / 3,
		&m_vecMultiVertex[0],
		sizeof(VTXTEX)
	);
	SetTexture(0, NULL);
}

void CChampGauge::RenderCellGauge()
{
	D3DXMATRIXA16 matWorld, matT, matS;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y + 1.5f, m_vPosition.z);
	D3DXMatrixScaling(&matS, m_fDmg, 1.0f, 1.0f);
	D3DXMatrixTranslation(&matT, m_vPosition.x + (m_fDmg / 2) - 0.5f, m_vPosition.y + 2.0f, m_vPosition.z);
	
		
	matWorld = matS* matT;

	SetTransform(D3DTS_WORLD, &matWorld);


	SetTexture(0, m_pCell);

	GET_DEVICE->SetFVF(VTXFVF_VTXTEX);

	HRESULT HR = GET_DEVICE->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		m_vecMultiVertex.size() / 3,
		&m_vecMultiVertex[0],
		sizeof(VTXTEX)
	);
	SetTexture(0, NULL);
}

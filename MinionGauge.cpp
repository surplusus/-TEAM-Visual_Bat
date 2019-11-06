#include "BaseInclude.h"
#include "MinionGauge.h"
#include "ObjMgr.h"


CMinionGauge::CMinionGauge()
{
	m_fDmg = 1.0f;
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


	//À­ÂÊ »ï°¢Çü
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

void CMinionGauge::Progress(D3DXVECTOR3 vPos)
{
	m_vPosition = vPos;
	SetPosition(m_vPosition);
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

void CMinionGauge::Render()
{
	RenderBlankGauge();
	RenderCell();
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

void CMinionGauge::RenderBlankGauge()
{
	D3DXMATRIXA16 matWorld, matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y + 1.0f, m_vPosition.z);

	matWorld = matT;

	SetTransform(D3DTS_WORLD, &matWorld);

	GET_DEVICE->SetFVF(VTXFVF_VTXTEX);

	HRESULT HR = GET_DEVICE->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		m_vecMultiVertex.size() / 3,
		&m_vecMultiVertex[0],
		sizeof(VTXTEX)
	);
	SetTexture(0, NULL);
}

void CMinionGauge::RenderCell()
{
	D3DXMATRIXA16 matWorld, matT, matS;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y + 1.0f, m_vPosition.z);
	D3DXMatrixScaling(&matS, m_fDmg, 1.0f, 1.0f);
	D3DXMatrixTranslation(&matT, m_vPosition.x + (m_fDmg / 2) - 0.5f, m_vPosition.y + 1.0f, m_vPosition.z);
	matWorld = matS * matT;

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

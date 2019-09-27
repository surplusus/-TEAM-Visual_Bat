#include "BaseInclude.h"
#include "Grid.h"
#include"Pyramid.h"

CGrid::CGrid()
{
}


CGrid::~CGrid()
{
	for (auto& p : m_vecPyramid)
		SAFE_DELETE(p);
	m_vecPyramid.clear();
}

void CGrid::SetUp(int nHalfTile, float fInterval)
{
	float fMax = nHalfTile * fInterval;
	float fMin = -fMax;
	ST_PC_VERTEX v;

	for (int i = 1; i <= nHalfTile; i++)
	{
		if (i % 5 == 0)
			v.c = D3DCOLOR_XRGB(255, 255, 255);
		else
			v.c = D3DCOLOR_XRGB(150, 150, 150);

		v.p = D3DXVECTOR3(fMin, 0, i * fInterval);	m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i * fInterval);	m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i * fInterval);	m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i * fInterval);	m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i * fInterval, 0, fMin);	m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(i * fInterval, 0, fMax);	m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i * fInterval, 0, fMin);	m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMax);	m_vecVertex.push_back(v);

	}
	// axisX
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(fMin, 0, 0);				m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0);				m_vecVertex.push_back(v);
	// axisY
	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin, 0);				m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0);				m_vecVertex.push_back(v);
	// axisZ
	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, fMin);				m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax);				m_vecVertex.push_back(v);

	// pyramid
	// X asix paramid
	CPyramid* pPyramid = nullptr;
	D3DXMATRIXA16 matR;
	pPyramid = new CPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.f);	// 90도 만큼 z축으로 회전 x 축이된다.
	pPyramid->SetUp(D3DCOLOR_XRGB(255, 0, 0), matR);
	m_vecPyramid.push_back(pPyramid);
	// Y asix paramid
	pPyramid = new CPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);	// 거기서 더 90도 만큼 z축으로 회전 y 축이 된다.
	pPyramid->SetUp(D3DCOLOR_XRGB(0, 255, 0), matR);
	m_vecPyramid.push_back(pPyramid);
	// X asix paramid
	pPyramid = new CPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.f);	// 90도 만큼 z축으로 회전
	pPyramid->SetUp(D3DCOLOR_XRGB(0, 0, 255), matR);
	m_vecPyramid.push_back(pPyramid);
}

void CGrid::Render()
{
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	SetTransform(D3DTS_WORLD, &matI);
	GetDevice()->SetFVF(CUSTOMVERTEX::FVF);
	GetDevice()->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2,
		&m_vecVertex[0], sizeof(CUSTOMVERTEX));

	for (auto& p : m_vecPyramid)
		p->Render();
}

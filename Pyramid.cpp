#include "BaseInclude.h"
#include "Pyramid.h"


CPyramid::CPyramid()
{
	D3DXMatrixIdentity(&m_matR);
}


CPyramid::~CPyramid()
{
}

void CPyramid::SetUp(D3DCOLOR c, D3DXMATRIXA16 & mat)
{

	m_matR = mat;

	CUSTOMVERTEX v;
	
	v.c = c;
	//front
	v.p = D3DXVECTOR3(0, 0, 0);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1);	m_vecVertex.push_back(v);
	//right
	v.p = D3DXVECTOR3(0, 0, 0);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1);	m_vecVertex.push_back(v);
	//back
	v.p = D3DXVECTOR3(0, 0, 0);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1);	m_vecVertex.push_back(v);
	//left
	v.p = D3DXVECTOR3(0, 0, 0);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1);	m_vecVertex.push_back(v);
	//bottom
	v.p = D3DXVECTOR3(-1, -1, -1);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(1, -1, -1);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1);	m_vecVertex.push_back(v);
}

void CPyramid::Render()
{
	D3DXMATRIXA16 matWorld, matS;
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);
	matWorld = matS * m_matR;
	GET_SINGLE(CDevice)->GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
	GET_SINGLE(CDevice)->GetDevice()->SetFVF(ST_PC_VERTEX::FVF);
	GET_SINGLE(CDevice)->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
}

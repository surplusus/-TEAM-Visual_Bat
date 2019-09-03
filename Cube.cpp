#include "BaseInclude.h"
#include "Cube.h"

CCube::CCube()
{
	m_vDirection = { 0.f, 0.f, 1 };
	m_vPosition = { 0.f, 0.f, 0.f };
	m_vRotation = { 0.f, 0.0f, 0.0f };
	D3DXMatrixIdentity(&m_matWorld);
}

CCube::CCube(D3DXVECTOR3 vPos, D3DXVECTOR3 vDir, D3DXVECTOR3 vRot)
	:CObj(vPos, vDir, vRot)
{
}


CCube::~CCube()
{
}

void CCube::SetUp()
{
	ST_PC_VERTEX v;
	srand(time(NULL));
	// front
	v.c = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, -1.f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	// back
	v.c = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, 1.f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f); m_vecVertex.push_back(v);
	// left
	v.c = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	//right
	v.c = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f); m_vecVertex.push_back(v);
	//top
	v.c = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, -1.f); m_vecVertex.push_back(v);
	//bottom
	v.c = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f); m_vecVertex.push_back(v);
}



void CCube::Update()
{
	if (GetKeyState('A') & 0x8000) {
		m_vRotation.y -= 0.1f;
	}
	if (GetKeyState('D') & 0x8000) {
		m_vRotation.y += 0.1f;
	}
	if (GetKeyState('W') & 0x8000) {
		m_vPosition += (m_vDirection * 0.1f);
	}
	if (GetKeyState('S') & 0x8000) {
		m_vPosition -= (m_vDirection * 0.1f);
	}

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_vRotation.y);
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;
}

void CCube::Render()
{
	GET_SINGLE(CDevice)->GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);
	GET_SINGLE(CDevice)->GetDevice()->SetFVF(CUSTOMVERTEX::FVF);
	GET_SINGLE(CDevice)->GetDevice()->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0], sizeof(CUSTOMVERTEX));
}

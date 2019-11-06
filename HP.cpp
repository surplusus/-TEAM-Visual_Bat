#include "BaseInclude.h"
#include "HP.h"


CHP::CHP()
{
}

CHP::CHP(const D3DXMATRIX * pMatrix)
	:m_pMatParent(pMatrix)
{
}


CHP::~CHP()
{
	Release();
}

HRESULT CHP::Initialize(void)
{
	m_Info.vPos = D3DXVECTOR3(0, 3.f, 0);
	return S_OK;
}

void CHP::Progress(void)
{
	D3DXMATRIX			matScale;
	D3DXMATRIX			matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 0.2f, 1.f);

	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);

	D3DXMATRIX			matView;

	GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixIdentity(&m_matBill);

	m_matBill = matView;
	m_matBill._41 = 0.f;
	m_matBill._42 = 0.f;
	m_matBill._43 = 0.f;

	m_matBill._11 = matView._11;
	m_matBill._31 = matView._31;
	m_matBill._13 = matView._13;
	m_matBill._33 = matView._33;
	

	D3DXMatrixInverse(&m_matBill, 0, &m_matBill);

	m_Info.matWorld = matScale * m_matBill * matTrans * (*m_pMatParent);

}

void CHP::Render(void)
{
	SetTexture(0, NULL);

	SetTransform(D3DTS_WORLD, &(m_Info.matWorld));

	Buffer_Render(GetDevice(), L"RectColor");

}

void CHP::Release(void)
{
}

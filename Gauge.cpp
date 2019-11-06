#include "BaseInclude.h"
#include "Gauge.h"


CGauge::CGauge()
	: m_pBlank(NULL)
	, m_pCell(NULL)
	, m_MAXHP(0)
	, m_MAXMP(0)
	, m_vPosition(0, 0, 0)
{
}


CGauge::~CGauge()
{
}

void CGauge::SetBillBoard()
{
	D3DXMATRIXA16	matView,matBillBoard;
	D3DXMatrixIdentity(&matView);

	GetDevice()->GetTransform(D3DTS_VIEW, &matView);
	m_matBillBoard = matView;
	m_matBillBoard._41 = 0.f;
	m_matBillBoard._42 = 0.f;
	m_matBillBoard._43 = 0.f;

	m_matBillBoard._11 = matView._11;
	m_matBillBoard._31 = matView._31;
	m_matBillBoard._13 = matView._13;
	m_matBillBoard._33 = matView._33;
	D3DXMatrixInverse(&m_matBillBoard, 0, &m_matBillBoard);

	//*Matrix = matBillBoard;
}

void CGauge::SetLight()
{
	{	// Make Light
		D3DLIGHT9 stLight;
		ZeroMemory(&stLight, sizeof(D3DLIGHT9));
		stLight.Type = D3DLIGHT_DIRECTIONAL;
		stLight.Ambient = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.f);
		stLight.Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.f);
		stLight.Specular = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.f);
		D3DXVECTOR3 vDir(1.f, -1.f, 1.f);
		D3DXVec3Normalize(&vDir, &vDir);
		stLight.Direction = vDir;
		GET_DEVICE->SetLight(0, &stLight);
		GET_DEVICE->LightEnable(0, true);
		GET_DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		SetRenderState(D3DRS_LIGHTING, true);
	}
}

void CGauge::RenderBlankGauge(vector<VTXTEX> vecMultiVertex, D3DXVECTOR3 vPosition, D3DXVECTOR3 vScale)
{
	D3DXMATRIXA16 matView, matS,matT, matWorld, matR;
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matR);
	SetBillBoard();

	//D3DXMatrixRotationX(&matR, D3DX_PI / 4.0f);

	D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);
	D3DXMatrixTranslation(&matT, 0, vPosition.y + 2.5f, 0);
	matWorld = matS * matR	* m_matBillBoard *matT;

	SetTransform(D3DTS_WORLD, &matWorld);

	SetTexture(0, m_pBlank);

	GET_DEVICE->SetFVF(VTXFVF_VTXTEX);

	HRESULT HR = GET_DEVICE->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		vecMultiVertex.size() / 3,
		&vecMultiVertex[0],
		sizeof(VTXTEX)
	);
	SetTexture(0, NULL);
}

void CGauge::RenderCellGauge(vector<VTXTEX> vecMultiVertex, D3DXVECTOR3 vPosition, D3DXVECTOR3 vScale)
{
	D3DXMATRIXA16 matView, matS, matT, matWorld, matR;
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matR);
	SetBillBoard();

	//D3DXMatrixRotationX(&matR, D3DX_PI / 4.0f);

	D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);
	D3DXMatrixTranslation(&matT, 0, vPosition.y + 2.5f, 0);
	matWorld = matS * matR	* m_matBillBoard *matT;


	SetTransform(D3DTS_WORLD, &matWorld);

	SetTexture(0, m_pCell);

	GET_DEVICE->SetFVF(VTXFVF_VTXTEX);

	HRESULT HR = GET_DEVICE->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		vecMultiVertex.size() / 3,
		&vecMultiVertex[0],
		sizeof(VTXTEX)
	);
	SetTexture(0, NULL);
}

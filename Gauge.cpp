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

void CGauge::SetBillBoard(D3DXMATRIXA16 * Matrix, float x, float y, float z)
{
	D3DXMATRIXA16	matWorld;
	D3DXMatrixIdentity(&matWorld);

	GetDevice()->GetTransform(D3DTS_VIEW, &matWorld);

	D3DXMatrixInverse(&matWorld, NULL, &matWorld);
	matWorld._41 = x;
	matWorld._42 = y;
	matWorld._43 = z;

	*Matrix = matWorld;
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
	D3DXMATRIXA16 matView, matS, World;
	D3DXMatrixIdentity(&matView);
	SetBillBoard(&matView, vPosition.x - 0.5f, vPosition.y + 2.5f, vPosition.z);

	D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);

	World = matS;
	World *= matView;

	SetTransform(D3DTS_WORLD, &World);

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
	D3DXMATRIXA16 matView, matS, World;
	D3DXMatrixIdentity(&matView);
	SetBillBoard(&matView, vPosition.x - 0.5f, vPosition.y + 2.5f, vPosition.z);

	D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);


	World = matS;
	World *= matView;

	SetTransform(D3DTS_WORLD, &World);

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

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

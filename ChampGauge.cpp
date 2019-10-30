#include "BaseInclude.h"
#include "ChampGauge.h"
#include "Image_Loader.h"
#include "ObjMgr.h"

CChampGauge::CChampGauge()
{
}


CChampGauge::~CChampGauge()
{
}

void CChampGauge::Initialize()
{
	CGauge::SetLight();
	D3DXCreateTextureFromFile(GetDevice(), L"./Resource/choen/UI/BlankGauge.png", &m_pBlank);
	D3DXCreateTextureFromFile(GetDevice(), L"./Resource/choen/UI/GaugeCell.png", &m_pCell);
	m_vPosition = D3DXVECTOR3(0, 0, 0);
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

void CChampGauge::Progress()
{	
	D3DXVECTOR3 pos = GET_SINGLE(CObjMgr)->GetInfo(L"Udyr")->vPos;
	SetPosition(pos);
	
}

void CChampGauge::Render()
{
	D3DXMATRIXA16 matWorld;
	SetBillBoard(&matWorld);
	D3DXMatrixTranslation(&matWorld, m_vPosition.x, m_vPosition.y + 2.0f, m_vPosition.z);
	
	SetTransform(D3DTS_WORLD, &matWorld);
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Ambient.r = mtrl.Diffuse.r = mtrl.Specular.r = 1;
	mtrl.Ambient.g = mtrl.Diffuse.g = mtrl.Specular.g = 1;
	mtrl.Ambient.b = mtrl.Diffuse.b = mtrl.Specular.b = 1;

	SetTexture(1, m_pBlank);
	SetTexture(0, m_pCell);

	GET_DEVICE->SetMaterial(&mtrl);
	GET_DEVICE->SetFVF(VTXFVF_VTXTEX);

	HRESULT HR = GET_DEVICE->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		m_vecMultiVertex.size() / 3,
		&m_vecMultiVertex[0],
		sizeof(VTXTEX)
	);
	SetTexture(0, NULL);
	SetTexture(1, NULL);
}

void CChampGauge::Release()
{
	SAFE_RELEASE(m_pBlank);
	SAFE_RELEASE(m_pCell);
}

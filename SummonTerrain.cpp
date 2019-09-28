#include "BaseInclude.h"
#include "SummonTerrain.h"
#include"ObjMgr.h"
#include"MathMgr.h"
#include"PipeLine.h"

CSummonTerrain::CSummonTerrain()
	: m_fCamDistance(1.f), m_pMesh(NULL)
{
	m_fAngle[ANGLE_X] = 0.0f;
	m_fAngle[ANGLE_Y] = 0.0f;
	m_fAngle[ANGLE_Z] = 0.0f;
}


CSummonTerrain::~CSummonTerrain()
{
}

HRESULT CSummonTerrain::Initialize(void)
{
	m_SortID = SORTID_NORMAL;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vPos = D3DXVECTOR3(1.f, -16.0f, 1.f);

	m_fCamDistance = 10.f;

	m_pOriVtx = new VTXTEX[4];
	m_pConVtx = new VTXTEX[4];
	ZeroMemory(m_pOriVtx, sizeof(VTXTEX));
	ZeroMemory(m_pConVtx, sizeof(VTXTEX));

	D3DXMatrixIdentity(&m_Info.matWorld);
	
	m_vMin = *(GetMin(BOUNDTYPE_CUBE));
	m_vMax = *(GetMax(BOUNDTYPE_CUBE));
	m_pMesh = GetMesh(L"Map");
	return S_OK;
}

void CSummonTerrain::Progress(void)
{

}

void CSummonTerrain::Render(void)
{	
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	GET_SINGLE(CDevice)->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Mesh_Render(GetDevice(), L"Map");
	
}

void CSummonTerrain::Release(void)
{

}
#include "BaseInclude.h"
#include "SommonTerrain.h"
#include"ObjMgr.h"
#include"MathMgr.h"
#include"PipeLine.h"

CSommonTerrain::CSommonTerrain()
	: m_fCamDistance(1.f), m_pMesh(NULL)
{
	m_fAngle[ANGLE_X] = 0.0f;
	m_fAngle[ANGLE_Y] = 0.0f;
	m_fAngle[ANGLE_Z] = 0.0f;
}


CSommonTerrain::~CSommonTerrain()
{
}

HRESULT CSommonTerrain::Initialize(void)
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

void CSommonTerrain::Progress(void)
{

	D3DXMatrixIdentity(&m_Info.matWorld);
	CPipeLine::MyVec3TransformNormal(&m_Info.vDir, &m_Info.vLook, &m_Info.matWorld);
	if (GetAsyncKeyState(VK_LBUTTON)) {
		if (IsPicking())
			int n = 0;
	}

	
	
}

void CSommonTerrain::Render(void)
{	
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	GET_SINGLE(CDevice)->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Mesh_Render(GetDevice(), L"Map");
	
}

void CSommonTerrain::Release(void)
{

}

bool CSommonTerrain::IsPicking()
{
	POINT pt;
	GetCursorPos(&pt);	ScreenToClient(g_hWnd, &pt);
	float fx = pt.x;	float fy = pt.y;
	SetRayViewSpace(fx, fy);
	SetRayWorldSpace(fx, fy);
	
	LPDIRECT3DVERTEXBUFFER9 pVB;
	LPDIRECT3DINDEXBUFFER9  pIB;
	if (SUCCEEDED(m_pMesh->GetVertexBuffer(&pVB)))
	{
		if (SUCCEEDED(m_pMesh->GetIndexBuffer(&pIB)))
		{

			int numNumFace = m_pMesh->GetNumFaces();
			VERT* pVertex = NULL;
			DWORD* pIndex = NULL;
			pVB->Lock(0, 0, (void**)&pVertex, 0);
			pIB->Lock(0, 0, (void**)&pIndex, 0);
			
			for (int i = 0; i < numNumFace; i+=3)
			{
				D3DXVECTOR3 v0 = pVertex[pIndex[i]].vPosition;
				D3DXVECTOR3 v1 = pVertex[pIndex[i+1]].vPosition;
				D3DXVECTOR3 v2 = pVertex[pIndex[i+2]].vPosition;

				//D3DXVECTOR3 v00, v01, v02;
				//D3DXVec3TransformCoord(&v00, &v0, &m_Info.matWorld);
				//D3DXVec3TransformCoord(&v01, &v1, &m_Info.matWorld);
				//D3DXVec3TransformCoord(&v02, &v2, &m_Info.matWorld);
				D3DXVECTOR3 PickedPos = {0.0f,0.0f,0.0f};
				if (IntersectTri(v0, v1, v2, PickedPos))
				{
					pVB->Unlock();		pIB->Unlock();
					pVB->Release();		pIB->Release();
					return true;
				}
			}
		}
	}

	pVB->Unlock();	pIB->Unlock();
	pVB->Release();	pIB->Release();
	return false;

}

void CSommonTerrain::SetRayViewSpace(float _fx, float _fy)
{
	LPDIRECT3DDEVICE9 pDevice =GET_SINGLE(CDevice)->GetDevice();
	pDevice->GetViewport(&m_ViewPort);
	pDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);
	pDevice->GetTransform(D3DTS_VIEW, &m_matView);
	float fx  = (((2.0f*_fx) / m_ViewPort.Width) - 1.0f) /m_matProj._11; 
	float fy  = (((2.0f*_fy) / m_ViewPort.Height) - 1.0f)/m_matProj._22;
	
	m_ray.vOrigin	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ray.vDirection = D3DXVECTOR3(fx, fy, 1.0f);
}
void CSommonTerrain::SetRayWorldSpace(float _fx, float _Fy)
{

	D3DXMATRIXA16 matViewInverse;

	D3DXMatrixInverse(&matViewInverse, NULL, &m_matView);

	D3DXVec3TransformCoord(&m_ray.vOrigin, &m_ray.vOrigin, &matViewInverse);
	D3DXVec3TransformNormal(&m_ray.vDirection, &m_ray.vDirection, &matViewInverse);
	D3DXVec3Normalize(&m_ray.vDirection, &m_ray.vDirection);
}

bool CSommonTerrain::IntersectTri(IN D3DXVECTOR3 & v0, IN D3DXVECTOR3 & v1, IN D3DXVECTOR3 & v2, OUT D3DXVECTOR3& vPickedPosition)
{
	float u=0.0f, v=0.0f, t=0.0f;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &m_ray.vOrigin, &m_ray.vDirection, &u, &v, &t);
	vPickedPosition = m_ray.vOrigin + (t* m_ray.vDirection);
	return b;
}

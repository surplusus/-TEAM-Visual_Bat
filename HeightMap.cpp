#include "BaseInclude.h"
#include "HeightMap.h"


CHeightMap::CHeightMap()
{
}


CHeightMap::~CHeightMap()
{
}

void CHeightMap::LoadData(string fileName)
{
	LPD3DXBUFFER pBuffer;	// Material �ε��
	DWORD materialNum;
	HRESULT hr = D3DXLoadMeshFromXA(fileName.c_str(), D3DXMESH_MANAGED, GET_DEVICE
		, NULL, &pBuffer, NULL, &materialNum, &m_pMesh);
	pBuffer->Release();

	m_VtxNum = m_pMesh->GetNumVertices();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuffer;
	VTXTEX* pVertex = NULL;
	if (SUCCEEDED(m_pMesh->GetVertexBuffer(&pVtxBuffer)))
	{
		pVtxBuffer->Lock(0, sizeof(VTXTEX) * m_pMesh->GetNumVertices(), (void**)&pVertex, 0);
		m_Vertices = pVertex;
	}
	pVtxBuffer->Unlock();
	pVtxBuffer->Release();
}

void CHeightMap::Render()
{
	D3DXMATRIXA16 matS,matWorld;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 1.f, 1.f, 1.f);
	D3DXMatrixIdentity(&matWorld);
	matWorld = matS;
	SetTransform(D3DTS_WORLD, &matWorld);
	//GET_DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	m_pMesh->DrawSubset(0);
}

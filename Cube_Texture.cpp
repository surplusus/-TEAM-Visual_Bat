#include "BaseInclude.h"
#include "Cube_Texture.h"


CCube_Texture::CCube_Texture()
{
}

CCube_Texture::~CCube_Texture()
{
}

HRESULT CCube_Texture::CreateVertexIndexBuffer(LPDIRECT3DDEVICE9 pDevice, const int & iVtxCntX, const int & iVtxCntZ, const float & fGap)
{
	m_iVtxSize = sizeof(CUBEVTXTEX);
	m_iVtxCnt = 8;
	m_dwVtxFVF = VTXFVF_CUBETEX;
	m_dwTriCnt = 12;

	m_iIdxSize = sizeof(INDEX);
	m_IdxFmt = D3DFMT_INDEX32;

	if (FAILED(CVIBuffer::CreateVertexIndexBuffer(pDevice)))
		return E_FAIL;

	CUBEVTXTEX*		pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	// 앞
	pVertex[0].vPosition = D3DXVECTOR3(-1.f, 1.f, -1.f);
	pVertex[0].vTexture = pVertex[0].vPosition;

	pVertex[1].vPosition = D3DXVECTOR3(1.f, 1.f, -1.f);
	pVertex[1].vTexture = pVertex[1].vPosition;

	pVertex[2].vPosition = D3DXVECTOR3(1.f, -1.f, -1.f);
	pVertex[2].vTexture = pVertex[2].vPosition;

	pVertex[3].vPosition = D3DXVECTOR3(-1.f, -1.f, -1.f);
	pVertex[3].vTexture = pVertex[3].vPosition;

	// 뒤
	pVertex[4].vPosition = D3DXVECTOR3(-1.f, 1.f, 1.f);
	pVertex[4].vTexture = pVertex[4].vPosition;

	pVertex[5].vPosition = D3DXVECTOR3(1.f, 1.f, 1.f);
	pVertex[5].vTexture = pVertex[5].vPosition;

	pVertex[6].vPosition = D3DXVECTOR3(1.f, -1.f, 1.f);
	pVertex[6].vTexture = pVertex[6].vPosition;

	pVertex[7].vPosition = D3DXVECTOR3(-1.f, -1.f, 1.f);
	pVertex[7].vTexture = pVertex[7].vPosition;


	m_pVB->Unlock();

	INDEX*			pIndex = NULL;

	int			iTriCnt = 0;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// +x
	pIndex[iTriCnt]._1 = 1; pIndex[iTriCnt]._2 = 5; pIndex[iTriCnt]._3 = 6;
	++iTriCnt;
	pIndex[iTriCnt]._1 = 1; pIndex[iTriCnt]._2 = 6; pIndex[iTriCnt]._3 = 2;
	++iTriCnt;

	// -x
	pIndex[iTriCnt]._1 = 4; pIndex[iTriCnt]._2 = 0; pIndex[iTriCnt]._3 = 3;
	++iTriCnt;
	pIndex[iTriCnt]._1 = 4; pIndex[iTriCnt]._2 = 3; pIndex[iTriCnt]._3 = 7;
	++iTriCnt;

	// +y
	pIndex[iTriCnt]._1 = 4; pIndex[iTriCnt]._2 = 5; pIndex[iTriCnt]._3 = 1;
	++iTriCnt;
	pIndex[iTriCnt]._1 = 4; pIndex[iTriCnt]._2 = 1; pIndex[iTriCnt]._3 = 0;
	++iTriCnt;

	// -y
	pIndex[iTriCnt]._1 = 7; pIndex[iTriCnt]._2 = 6; pIndex[iTriCnt]._3 = 2;
	++iTriCnt;
	pIndex[iTriCnt]._1 = 7; pIndex[iTriCnt]._2 = 2; pIndex[iTriCnt]._3 = 3;
	++iTriCnt;

	// +z
	pIndex[iTriCnt]._1 = 4; pIndex[iTriCnt]._2 = 5; pIndex[iTriCnt]._3 = 6;
	++iTriCnt;
	pIndex[iTriCnt]._1 = 4; pIndex[iTriCnt]._2 = 6; pIndex[iTriCnt]._3 = 7;
	++iTriCnt;

	// -z
	pIndex[iTriCnt]._1 = 0; pIndex[iTriCnt]._2 = 1; pIndex[iTriCnt]._3 = 2;
	++iTriCnt;
	pIndex[iTriCnt]._1 = 0; pIndex[iTriCnt]._2 = 2; pIndex[iTriCnt]._3 = 3;
	++iTriCnt;

	m_pIB->Unlock();

	return S_OK;
}

void CCube_Texture::Buffer_Render(LPDIRECT3DDEVICE9 pDevice)
{
	// 어떤 버텍스버퍼를 이용해서 렌더링할 것이냐
	pDevice->SetStreamSource(0, m_pVB, 0, m_iVtxSize);

	pDevice->SetIndices(m_pIB);

	// 그 버텍스 버퍼에는 어떤 버텍스들이 담겨있느냐
	pDevice->SetFVF(m_dwVtxFVF);

	// 도형을 어떤식으로 그려나갈 것이냐
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVtxCnt, 0, m_dwTriCnt);


}

void CCube_Texture::Release(void)
{
}

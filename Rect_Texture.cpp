#include "BaseInclude.h"
#include "Rect_Texture.h"


CRect_Texture::CRect_Texture()
{
}


CRect_Texture::~CRect_Texture()
{
}

HRESULT CRect_Texture::CreateVertexIndexBuffer(LPDIRECT3DDEVICE9 pDevice, const int & iVtxCntX, const int & iVtxCntZ, const float & fGap)
{

	m_iVtxSize = sizeof(VTXTEX);
	m_iVtxCnt = 4;
	m_dwVtxFVF = VTXFVF_VTXTEX;
	m_dwTriCnt = 2;

	m_iIdxSize = sizeof(INDEX);
	m_IdxFmt = D3DFMT_INDEX32;


	if (FAILED(CVIBuffer::CreateVertexIndexBuffer(pDevice)))
	{
		return E_FAIL;
	}

	VTXTEX*		pVtxTex = NULL;

	m_pVB->Lock(0, 0, (void**)&pVtxTex, NULL);

	pVtxTex[0].vPosition = D3DXVECTOR3(-1.f, 1.f, 0.f);
	pVtxTex[0].vTexture = D3DXVECTOR2(0.f, 0.f);

	pVtxTex[1].vPosition = D3DXVECTOR3(1.f, 1.f, 0.f);
	pVtxTex[1].vTexture = D3DXVECTOR2(1.f, 0.f);

	pVtxTex[2].vPosition = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVtxTex[2].vTexture = D3DXVECTOR2(1.f, 1.f);

	pVtxTex[3].vPosition = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVtxTex[3].vTexture = D3DXVECTOR2(0.f, 1.f);

	m_pVB->Unlock();

	INDEX*			pIndex = NULL;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._1 = 0;
	pIndex[0]._2 = 1;
	pIndex[0]._3 = 2;

	pIndex[1]._1 = 0;
	pIndex[1]._2 = 2;
	pIndex[1]._3 = 3;

	m_pIB->Unlock();

	return S_OK;
}

void CRect_Texture::Buffer_Render(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetStreamSource(0, m_pVB, 0, m_iVtxSize);

	pDevice->SetIndices(m_pIB);

	// 그 버텍스 버퍼에는 어떤 버텍스들이 담겨있느냐
	pDevice->SetFVF(m_dwVtxFVF);

	// 도형을 어떤식으로 그려나갈 것이냐
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVtxCnt, 0, m_dwTriCnt);

}

void CRect_Texture::Release(void)
{
}

#include "BaseInclude.h"
#include "RectColor.h"


CRectColor::CRectColor()
{
}


CRectColor::~CRectColor()
{
}

HRESULT CRectColor::CreateVertexIndexBuffer(LPDIRECT3DDEVICE9 pDevice
	, const int& iVtxCntX/* = 0*/
	, const int& iVtxCntZ/* = 0*/
	, const float& fGap/* = 1*/)
{
	m_iVtxSize = sizeof(VTXCOL);
	m_iVtxCnt = 4;
	m_dwVtxFVF = VTXFVF_VTXCOL;
	m_dwTriCnt = 2;

	m_iIdxSize = sizeof(INDEX);
	m_IdxFmt = D3DFMT_INDEX32;


	if (FAILED(CVIBuffer::CreateVertexIndexBuffer(pDevice)))
	{
		return E_FAIL;
	}

	VTXCOL*		pVtxCol = NULL;

	m_pVB->Lock(0, 0, (void**)&pVtxCol, NULL);

	pVtxCol[0].vPosition = D3DXVECTOR3(-1.f, 1.f, 0.f);
	pVtxCol[0].dwDiffuse = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVtxCol[1].vPosition = D3DXVECTOR3(1.f, 1.f, 0.f);
	pVtxCol[1].dwDiffuse = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVtxCol[2].vPosition = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVtxCol[2].dwDiffuse = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVtxCol[3].vPosition = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVtxCol[3].dwDiffuse = D3DCOLOR_ARGB(255, 255, 0, 0);

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

void CRectColor::Buffer_Render(LPDIRECT3DDEVICE9 pDevice)
{
	// � ���ؽ����۸� �̿��ؼ� �������� ���̳�
	pDevice->SetStreamSource(0, m_pVB, 0, m_iVtxSize);

	pDevice->SetIndices(m_pIB);

	// �� ���ؽ� ���ۿ��� � ���ؽ����� ����ִ���
	pDevice->SetFVF(m_dwVtxFVF);

	// ������ ������� �׷����� ���̳�
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVtxCnt, 0, m_dwTriCnt);
}

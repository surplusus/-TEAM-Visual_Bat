#pragma once
class CVIBuffer
{
public:
	CVIBuffer();
	virtual ~CVIBuffer();
protected:
	LPDIRECT3DVERTEXBUFFER9				m_pVB;
	UINT							    m_iVtxSize;
	UINT								m_iVtxCnt;
	DWORD								m_dwVtxFVF;
protected:
	LPDIRECT3DINDEXBUFFER9				m_pIB;
	UINT								m_iIdxSize;
	D3DFORMAT							m_IdxFmt;
	
	//Æú¸®°ïÀÇ °¹¼ö
	DWORD								m_dwTriCnt;
public:
	void PasteVertexInfo(VTXTEX* pConVtx)
	{
		VTXTEX* pVertex = NULL;
		m_pVB->Lock(0, 0, (void**)&pVertex, 0);
		memcpy(pVertex, pConVtx, m_iVtxCnt*m_iVtxSize);
		m_pVB->Unlock();
	}
	void CopyVertexInfo(VTXTEX* pOriVtx)
	{
		VTXTEX*pVertex = NULL;
		m_pVB->Lock(0, 0, (void**)&pVertex, 0);
		memcpy(pOriVtx, pVertex, m_iVtxCnt*m_iVtxSize);
		m_pVB->Unlock();
	}
	void CopyIndeXInfo(INDEX* pIndex, const int& iTrieCnt)
	{
		INDEX* pOriIndex = NULL;
		m_dwTriCnt = iTrieCnt;

		m_pIB->Lock(0, 0, (void**)&pOriIndex, 0);
		memcpy(pOriIndex, pIndex, iTrieCnt*m_iIdxSize);
		m_pIB->Unlock();
	}
public:
	virtual HRESULT CreateVertexIndexBuffer(LPDIRECT3DDEVICE9 pDevice
		, const int& iVtCntX = 0
		, const int& iVtxCntZ = 0
		, const float& fGap = 1);
	virtual void Buffer_Render(LPDIRECT3DDEVICE9 pDevice);
	virtual void Release();
};


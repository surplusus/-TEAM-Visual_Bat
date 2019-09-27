#pragma once
class CVIBuffer;
class CBufferMgr
{
	DECLARE_SINGLETON(CBufferMgr)
private:
	map<const TCHAR*, CVIBuffer*>  m_MapBuffer;
public:
	HRESULT AddBuffers(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pBufferKey
		, BUFFERTYPE Type
		, const int& iVtxCntX = 0
		, const int& iVtxCntZ = 0
		, const float& fGap = 1.f);

	void CopyVertexInfo(const TCHAR* pBufferKey
		, VTXTEX* pOriVtx);
	void CopyIndexBuffer(const TCHAR* pBufferKey
		, INDEX* pIndex, const int& iTriCnt);
	void PasteVertexInfo(const TCHAR* pBufferKey
		, VTXTEX* pConVtx);
	void Buffer_Render(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pBufferKey);
public:
	void Release();
private:
	CBufferMgr();
public:
	~CBufferMgr();
};


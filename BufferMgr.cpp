#include "BaseInclude.h"
#include "BufferMgr.h"
#include"Cube_Texture.h"
#include"Rect_Texture.h"
#include"Terrain.h"
HRESULT CBufferMgr::AddBuffers(LPDIRECT3DDEVICE9 pDevice, const TCHAR * pBufferKey, BUFFERTYPE Type, const int & iVtxCntX, const int & iVtxCntZ, const float & fGap)
{
	map<const TCHAR*, CVIBuffer*>::iterator	iter = m_MapBuffer.find(pBufferKey);

	if (iter != m_MapBuffer.end())
	{
		ERR_MSG(g_hWnd,L"추가하려고하는 버퍼가 이미 존재합니다.");
		return E_FAIL;
	}

	CVIBuffer*		pVIBuffer = NULL;

	switch (Type)
	{
	case BUFFERTYPE_TRICOL:
	//	pVIBuffer = new CTriangle_Color;
		break;
	case BUFFERTYPE_RCCOL:
		//pVIBuffer = new CRectColor;
		break;
	case BUFFERTYPE_RCTEX:
		pVIBuffer = new CRect_Texture;
		break;
	case BUFFERTYPE_CUBE:
		pVIBuffer = new CCube_Texture;
		break;

	case BUFFERTYPE_TERRAIN:
		pVIBuffer = new CTerrain;
		if (FAILED(pVIBuffer->CreateVertexIndexBuffer(pDevice, iVtxCntX, iVtxCntZ, fGap)))
		{
			ERR_MSG(g_hWnd,L"VertexIndexBuffer Create Failed");
			return E_FAIL;
		}
		goto	Pass;
		break;
	}

	if (pVIBuffer == NULL)
		return E_FAIL;
	if (FAILED(pVIBuffer->CreateVertexIndexBuffer(pDevice)))
	{
		ERR_MSG(g_hWnd,L"VertexIndexBuffer Create Failed");
		return E_FAIL;
	}

Pass:
	m_MapBuffer.insert(map<const TCHAR*, CVIBuffer*>::value_type(pBufferKey, pVIBuffer));

	return S_OK;
}

void CBufferMgr::CopyVertexInfo(const TCHAR * pBufferKey, VTXTEX * pOriVtx)
{
	map<const TCHAR*, CVIBuffer*>::iterator	iter = m_MapBuffer.find(pBufferKey);

	if (iter == m_MapBuffer.end())
	{
		return;
	}

	iter->second->CopyVertexInfo(pOriVtx);
}

void CBufferMgr::CopyIndexBuffer(const TCHAR * pBufferKey, INDEX * pIndex, const int & iTriCnt)
{
	map<const TCHAR*, CVIBuffer*>::iterator	iter = m_MapBuffer.find(pBufferKey);

	if (iter == m_MapBuffer.end())
	{
		return;
	}

	iter->second->CopyIndeXInfo(pIndex, iTriCnt);
}

void CBufferMgr::PasteVertexInfo(const TCHAR * pBufferKey, VTXTEX * pConVtx)
{
	map<const TCHAR*, CVIBuffer*>::iterator	iter = m_MapBuffer.find(pBufferKey);

	if (iter == m_MapBuffer.end())
	{
		return;
	}

	iter->second->PasteVertexInfo(pConVtx);
}

void CBufferMgr::Buffer_Render(LPDIRECT3DDEVICE9 pDevice, const TCHAR * pBufferKey)
{
	map<const TCHAR*, CVIBuffer*>::iterator iter = m_MapBuffer.find(pBufferKey);

	if (iter == m_MapBuffer.end())
	{
		ERR_MSG(g_hWnd,L"렌더링할 버퍼가 없습니다.");
		return;
	}
	iter->second->Buffer_Render(pDevice);
}

void CBufferMgr::Release()
{
	for (map<const TCHAR*, CVIBuffer*>::iterator	iter = m_MapBuffer.begin();
		iter != m_MapBuffer.end(); ++iter)
	{
		if (iter->second)
		{
			delete iter->second;
			iter->second = NULL;
		}
	}
	m_MapBuffer.clear();
}

CBufferMgr::CBufferMgr()
{
}


CBufferMgr::~CBufferMgr()
{
	Release();
}

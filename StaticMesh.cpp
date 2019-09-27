#include "BaseInclude.h"
#include "StaticMesh.h"


CStaticMesh::CStaticMesh()
	: CMesh()
	
{
}


CStaticMesh::~CStaticMesh()
{
}

HRESULT CStaticMesh::CreateMesh(LPDIRECT3DDEVICE9 pDevice, const TCHAR * pPath, const TCHAR * pFileName)
{
	TCHAR szPath[128] = L"";

	ID3DXBuffer* adjBuffer;
	lstrcpy(szPath, pPath);
	lstrcat(szPath, pFileName);
	if (FAILED(D3DXLoadMeshFromX(szPath, D3DXMESH_MANAGED, pDevice, &adjBuffer,
		&m_pSubSetbuffer, NULL, &m_dwSubSetCnt, &m_pMesh)))
	{
		return E_FAIL;
	}
	m_pSubSets = (D3DXMATERIAL*)m_pSubSetbuffer->GetBufferPointer();
	m_pTextures = new LPDIRECT3DTEXTURE9[m_dwSubSetCnt];
	m_pMtrls = new D3DMATERIAL9[m_dwSubSetCnt];

	
	for (DWORD i = 0; i < m_dwSubSetCnt; ++i)
	{
		TCHAR szBuff[128] = L"";

		m_pMtrls[i] = m_pSubSets[i].MatD3D;
		lstrcpy(szPath, pPath);

		MultiByteToWideChar(CP_ACP, 0, m_pSubSets[i].pTextureFilename,
			strlen(m_pSubSets[i].pTextureFilename),
			szBuff, 128);

		lstrcat(szPath, szBuff);

		D3DXIMAGE_INFO info;
		D3DXGetImageInfoFromFile(szPath, &info);

		if (FAILED(D3DXCreateTextureFromFileEx(pDevice, szPath, info.Width, info.Height, 1, 0, D3DFMT_DXT1,
			D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &m_pTextures[i])))
		{
			ERR_MSG(g_hWnd,L"CtaticMesh : CreatTexture- FAILED");
			return E_FAIL;
		}
	}
	HRESULT hr = m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjBuffer->GetBufferPointer(),
		(DWORD*)adjBuffer->GetBufferPointer(), 0, 0);
	if (FAILED(hr))
	{
		ERR_MSG(g_hWnd, L"Optimizeplace - FALED");
		adjBuffer->Release();
	}

	return S_OK;
}

void CStaticMesh::Render(LPDIRECT3DDEVICE9 pDevice, const BONE * pRootBone)
{
	for (DWORD i = 0; i < m_dwSubSetCnt; ++i)
	{
		pDevice->SetTexture(0, m_pTextures[i]);
		m_pMesh->DrawSubset(i);
	}
}

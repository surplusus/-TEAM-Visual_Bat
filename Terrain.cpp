#include "BaseInclude.h"
#include "Terrain.h"


CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
}

HRESULT CTerrain::CreateVertexIndexBuffer(LPDIRECT3DDEVICE9 pDevice, const int & iVtxCntX, const int & iVtxCntZ, const float & fGap)
{
	HANDLE		hFile;
	DWORD		dwByte;

	hFile = CreateFile(L"./Terrain/Height.bmp"
		, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, &m_fh, sizeof(m_fh), &dwByte, NULL);
	ReadFile(hFile, &m_ih, sizeof(m_ih), &dwByte, NULL);
	m_pPixel = new DWORD[m_ih.biWidth * m_ih.biHeight];

	ReadFile(hFile, m_pPixel, sizeof(DWORD) * m_ih.biWidth * m_ih.biHeight
		, &dwByte, NULL);

	m_iVtxSize = sizeof(VTXTEX);
	m_iVtxCnt = iVtxCntX * iVtxCntZ;
	m_dwVtxFVF = VTXFVF_VTXTEX;
	m_dwTriCnt = (iVtxCntX - 1) * (iVtxCntZ - 1) * 2;
	m_iIdxSize = sizeof(INDEX);
	m_IdxFmt = D3DFMT_INDEX32;

	if (FAILED(CVIBuffer::CreateVertexIndexBuffer(pDevice)))
	{
		return E_FAIL;
	}

	VTXTEX*		pVtxTex = NULL;

	m_pVB->Lock(0, 0, (void**)&pVtxTex, NULL);

	int			iIndex = 0;

	for (int z = 0; z < iVtxCntZ; ++z)
	{
		for (int x = 0; x < iVtxCntX; ++x)
		{
			iIndex = z * iVtxCntX + x;

			pVtxTex[iIndex].vPosition = D3DXVECTOR3(x * fGap, (m_pPixel[iIndex] & 0x000000ff) / 3.f, z * fGap);

			pVtxTex[iIndex].vNormal = D3DXVECTOR3(0.f, 0.f, 0.f);
			pVtxTex[iIndex].vTexture = D3DXVECTOR2(x / float(iVtxCntX - 1.f)
				, (z / float(iVtxCntZ - 1.f)));
		}
	}


	INDEX*			pIndex = NULL;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	int			iTriCnt = 0;

	D3DXVECTOR3		vDestNor, vSourNor;
	D3DXVECTOR3		vNormal;

	DWORD*			pdwCnt = new DWORD[m_iVtxCnt];
	ZeroMemory(pdwCnt, sizeof(DWORD) * m_iVtxCnt);

	for (int z = 0; z < iVtxCntZ - 1; ++z)
	{
		for (int x = 0; x < iVtxCntX - 1; ++x)
		{
			iIndex = z * iVtxCntX + x;

			// 삼각형 두개를 그리기위한 인덱스를 셋팅
			pIndex[iTriCnt]._1 = iIndex + iVtxCntX;
			++pdwCnt[pIndex[iTriCnt]._1];
			pIndex[iTriCnt]._2 = iIndex + iVtxCntX + 1;
			++pdwCnt[pIndex[iTriCnt]._2];
			pIndex[iTriCnt]._3 = iIndex + 1;
			++pdwCnt[pIndex[iTriCnt]._3];

			vDestNor = pVtxTex[pIndex[iTriCnt]._2].vPosition
				- pVtxTex[pIndex[iTriCnt]._1].vPosition;
			vSourNor = pVtxTex[pIndex[iTriCnt]._3].vPosition
				- pVtxTex[pIndex[iTriCnt]._1].vPosition;

			D3DXVec3Cross(&vNormal, &vDestNor, &vSourNor);
			D3DXVec3Normalize(&vNormal, &vNormal);

			pVtxTex[pIndex[iTriCnt]._1].vNormal += vNormal;
			pVtxTex[pIndex[iTriCnt]._2].vNormal += vNormal;
			pVtxTex[pIndex[iTriCnt]._3].vNormal += vNormal;
			++iTriCnt;

			pIndex[iTriCnt]._1 = iIndex + iVtxCntX;
			++pdwCnt[pIndex[iTriCnt]._1];
			pIndex[iTriCnt]._2 = iIndex + 1;
			++pdwCnt[pIndex[iTriCnt]._2];
			pIndex[iTriCnt]._3 = iIndex;
			++pdwCnt[pIndex[iTriCnt]._3];

			vDestNor = pVtxTex[pIndex[iTriCnt]._2].vPosition
				- pVtxTex[pIndex[iTriCnt]._1].vPosition;
			vSourNor = pVtxTex[pIndex[iTriCnt]._3].vPosition
				- pVtxTex[pIndex[iTriCnt]._1].vPosition;

			D3DXVec3Cross(&vNormal, &vDestNor, &vSourNor);
			D3DXVec3Normalize(&vNormal, &vNormal);

			pVtxTex[pIndex[iTriCnt]._1].vNormal += vNormal;
			pVtxTex[pIndex[iTriCnt]._2].vNormal += vNormal;
			pVtxTex[pIndex[iTriCnt]._3].vNormal += vNormal;

			++iTriCnt;
		}
	}
	m_pIB->Unlock();

	for (unsigned int i = 0; i < m_iVtxCnt; ++i)
	{
		pVtxTex[i].vNormal /= float(pdwCnt[i]);
		//pVtxTex[i].vNormal = D3DXVECTOR3(0.f, 1.f, 0.f);
		D3DXVec3Normalize(&pVtxTex[i].vNormal, &pVtxTex[i].vNormal);
	}

	delete[] pdwCnt;
	pdwCnt = NULL;

	m_pVB->Unlock();

	delete[] m_pPixel;
	m_pPixel = NULL;

	return S_OK;
}

void CTerrain::Buffer_Render(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetStreamSource(0, m_pVB, 0, m_iVtxSize);

	pDevice->SetIndices(m_pIB);

	// 그 버텍스 버퍼에는 어떤 버텍스들이 담겨있느냐
	pDevice->SetFVF(m_dwVtxFVF);

	// 도형을 어떤식으로 그려나갈 것이냐
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVtxCnt, 0, m_dwTriCnt);
}

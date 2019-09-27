#include "BaseInclude.h"
#include "Mesh.h"


CMesh::CMesh()
	: m_pMesh(NULL)
	, m_pSubSetbuffer(NULL)
	, m_pTextures(NULL)
	, m_pMtrls(NULL)	
{
}


CMesh::~CMesh()
{
}


void CMesh::Release()
{

	if (m_pMesh)
		m_pMesh->Release();

	if (m_pSubSetbuffer)
		m_pSubSetbuffer->Release();

	if (m_pTextures)
	{
		for (DWORD i = 0; i < m_dwSubSetCnt; ++i)
			m_pTextures[i]->Release();

		delete[] m_pTextures;
		m_pTextures = NULL;
	}

	if (m_pMtrls)
	{
		delete[] m_pMtrls;
		m_pMtrls = NULL;
	}
}


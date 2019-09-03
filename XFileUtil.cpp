#include "BaseInclude.h"
#include "XFileUtil.h"
#include "Include.h"


CXFileUtil::CXFileUtil()
{
	m_pMesh = NULL;
	m_pMeshMaterials = NULL;
	m_pMeshTexture = NULL;
	m_dwNumMaterials = NULL;
	pD3DDevice = GET_SINGLE(CDevice)->GetDevice();
}


CXFileUtil::~CXFileUtil()
{
}

int CXFileUtil::XFileRender()
{
	for (DWORD i = 0; i < m_dwNumMaterials; i++)
	{
		pD3DDevice->SetMaterial(&m_pMeshMaterials[i]);
		pD3DDevice->SetTexture(0, m_pMeshTexture[i]);
		m_pMesh->DrawSubset(i);
	}
	pD3DDevice->SetTexture(0, NULL);
	return 0;
}

CXFileUtil* CXFileUtil::XFileLoad(const char * xFileName)
{
	LPD3DXBUFFER dD3DXMtrlBuffer;
	if (FAILED(D3DXLoadMeshFromXA(xFileName, D3DXMESH_SYSTEMMEM, pD3DDevice,
		NULL, &dD3DXMtrlBuffer, NULL, &m_dwNumMaterials, &m_pMesh)))
	{
		ERR_MSG(NULL, L"X파일 로드 실패 & Mesh로드 실패");
		return NULL;
	}
	char Texture_Path[256] = {0};
	if (strchr(xFileName, '/') == NULL)
		wsprintfA(Texture_Path, "./");
	else
	{
		char temp[256], *pChar;
		strcpy(temp, xFileName);
		_strrev(temp);
		pChar = strchr(temp,'/');
		strcpy(Texture_Path, pChar);
		strcpy(Texture_Path, pChar);
		_strrev(Texture_Path);
	}
	//x파일로드
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)dD3DXMtrlBuffer->GetBufferPointer();
	m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	m_pMeshTexture = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];
	for (DWORD i = 0; i < m_dwNumMaterials; i++)
	{
		//재질 복사
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		//재질에 대한 엠비언트 색상 설정
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;
		m_pMeshTexture[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			//경로 + 텍스쳐 파일 이름 만들기
			char tempFile[256] = {0};
			wsprintfA(tempFile, "%s%s", Texture_Path, d3dxMaterials[i].pTextureFilename);
			if (FAILED(D3DXCreateTextureFromFileA(pD3DDevice, tempFile, &m_pMeshTexture[i])))
			{
				m_pMeshTexture[i] = NULL;
			}
		}
	}
	dD3DXMtrlBuffer->Release();
	return this;
}

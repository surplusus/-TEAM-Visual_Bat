#pragma once
class CXFileUtil
{
public:
	CXFileUtil();
	virtual ~CXFileUtil();
private:
	LPD3DXMESH m_pMesh;//매쉬 객체
	D3DMATERIAL9* m_pMeshMaterials;//매쉬에 대한 재질
	LPDIRECT3DTEXTURE9* m_pMeshTexture;//매쉬 텍스쳐
	DWORD m_dwNumMaterials;//재질의 수
	LPDIRECT3DDEVICE9 pD3DDevice;
public:
	int XFileRender();
	CXFileUtil* XFileLoad(const char * xFileName);
};


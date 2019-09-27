#pragma once
#include "Mesh.h"
class CStaticMesh :
	public CMesh
{
public:
	CStaticMesh();
	~CStaticMesh();
public:
	virtual HRESULT CreateMesh(LPDIRECT3DDEVICE9 pDevice
		, const TCHAR* pPath
		, const TCHAR* pFileName);
	virtual void Render(LPDIRECT3DDEVICE9 pDevice
		, const BONE* pRootBone = NULL);

};


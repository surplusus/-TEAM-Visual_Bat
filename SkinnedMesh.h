#pragma once
#include"DynamicMesh.h"
#include"HierachyLoader.h"
class CSkinnedMesh
	: public CDynamicMesh
{
public:
	CSkinnedMesh(string name);
	~CSkinnedMesh(void);
	string m_MeshName;
public:
	HRESULT CreateMesh(LPDIRECT3DDEVICE9 pDevice
		, const TCHAR* pPathName, const TCHAR* pFileName);

	virtual void InvalidateMesh(D3DXMATRIX* pMatWorld);

	void UpdateMatrix(BONE* pParentBone, D3DXMATRIX* pMatrix);
	void SetUpBoneMatrixPointer(BONE* pBone);
	virtual void Render(LPDIRECT3DDEVICE9 pDevice, const BONE* pBone = NULL);
	void Release(void);
};

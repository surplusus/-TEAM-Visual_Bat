#pragma once
#include"DynamicMesh.h"
#include"HierachyLoader.h"
class CSkinnedMesh
	: public CDynamicMesh
{
public:
	CSkinnedMesh();
	~CSkinnedMesh(void);
public:
	HRESULT CreateMesh(LPDIRECT3DDEVICE9 pDevice
		, const TCHAR* pPathName, const TCHAR* pFileName);

	virtual void InvalidateMesh(D3DXMATRIX* pMatWorld);
private:
	void UpdateMatrix(BONE* pParentBone, D3DXMATRIX* pMatrix);
	void SetUpBoneMatrixPointer(BONE* pBone);
public:
	virtual void Render(LPDIRECT3DDEVICE9 pDevice, const BONE* pBone = NULL);
	void Release(void);
};

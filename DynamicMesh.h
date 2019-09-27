#pragma once
#include "Mesh.h"
#include"HierachyLoader.h"
class CAnimationCtrl;
class CDynamicMesh
	: public CMesh
{
protected:
	CHierachyLoader*			m_pLoader;
	D3DXFRAME*					m_pRootBone;
	CAnimationCtrl*				m_pAniCtrl;
public:
	virtual void GetBoneMatrix(const CHAR* pBoneName, D3DXMATRIX* pOut);
	void FindBone(const CHAR* pBoneName, BONE* pBone, D3DXMATRIX* pOut);
public:
	virtual HRESULT CreateMesh(LPDIRECT3DDEVICE9 pDevice
		, const TCHAR* pPath
		, const TCHAR* pFileName);
	virtual HRESULT CloneMesh(LPDIRECT3DDEVICE9 pDevice
		, CAnimationCtrl** ppAniCtrl);
	virtual void InvalidateMesh(D3DXMATRIX* pMatWorld) {}

	virtual void Render(LPDIRECT3DDEVICE9 pDevice
		, const BONE* pRootBone = NULL);
public:
	CDynamicMesh(void);
	~CDynamicMesh(void);
};

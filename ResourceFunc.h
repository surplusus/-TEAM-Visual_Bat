#ifndef _RESOURCEFUNC_H
#define _RESOURCEFUNC_H

#define RESOURCE_EXPORT

class CAnimationCtrl;
//=============== Buffer 14.05.14 By Burger ===============//
extern HRESULT Insert_Buffer(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pBufferKey
	, BUFFERTYPE Type
	, const int& iVtxCntX = 0
	, const int& iVtxCntZ = 0
	, const float& fGap = 1.f);

extern  void CopyVertexInfo(const TCHAR* pBufferKey
	, VTXTEX* pOriVtx);
extern  void CopyIndexBuffer(const TCHAR* pBufferKey
	, INDEX* pIndex, const int& iTriCnt);
extern  void PasteVertexInfo(const TCHAR* pBufferKey
	, VTXTEX* pConVtx);


extern  void Buffer_Render(LPDIRECT3DDEVICE9 pDevice
	, const TCHAR* pBufferKey);

//=============== Texture 14.05.14 By Burger ===============//
extern  HRESULT		InsertTexture(LPDIRECT3DDEVICE9 pDevice
	, TEXTYPE Type
	, const TCHAR* pFileName
	, const TCHAR* pObjectKey
	, const TCHAR* pStateKey
	, const int& iCnt = 1, TERRIAN_INSERTTYPE = INSERTTYPE_ENGLISH);

//=============== Texture :: Getter 14.05.14 By Burger ===============//
extern  const TEXINFO*	GetTexture(const TCHAR* pObjectKey
	, const TCHAR* pStateKey
	, const int& iCnt = 0);
//=============== Bounding ===================//
extern  HRESULT AddBounding(LPDIRECT3DDEVICE9 pDevice, BOUNDTYPE Type);
extern  void    Bound_Render(BOUNDTYPE Type);
extern  const D3DXVECTOR3* GetMin(BOUNDTYPE Type);
extern const  D3DXVECTOR3* GetMax(BOUNDTYPE Type);


//=============== Mesh =============== //
extern  HRESULT AddMesh(LPDIRECT3DDEVICE9 pDevice
	, const TCHAR* pPath
	, const TCHAR* pFileName
	, const TCHAR* pMeshKey
	, MESHTYPE Type);

extern  HRESULT CloneMesh(LPDIRECT3DDEVICE9 pDevice
	, const TCHAR* pMeshKey
	, CAnimationCtrl** ppAniCtrl);

extern  void Mesh_Render(LPDIRECT3DDEVICE9 pDevice
	, const TCHAR* pMeshKey);

extern  void GetBoneMatrix(const TCHAR* pMeshKey
	, const CHAR* pBoneName
	, D3DXMATRIX* pOut);
extern LPD3DXMESH GetMesh(const TCHAR* pMeshKey);
extern  void Resource_Release(void);
#endif
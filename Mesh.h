#pragma once
class CMesh
{
public:
	CMesh();
	virtual ~CMesh();
protected:
	LPD3DXMESH				m_pMesh;//매쉬정보
	LPD3DXBUFFER			m_pSubSetbuffer;//버퍼
	DWORD					m_dwSubSetCnt;

	LPD3DXMATERIAL			m_pSubSets;//머터리얼 정보
	LPDIRECT3DTEXTURE9*		m_pTextures;//텍스처 정보	
	D3DMATERIAL9*			m_pMtrls;

public:
	virtual void			GetBonMatrix(const CHAR* pBoneName, D3DXMATRIX* pOut) {};
public:
	virtual void			InvalidateMesh(D3DXMATRIX* pMatWorld) {}
public:
	virtual HRESULT			CreateMesh(LPDIRECT3DDEVICE9 pDevice
										, const TCHAR* pPath
										, const TCHAR* pFileName)PURE;

	virtual HRESULT			CloneMesh(LPDIRECT3DDEVICE9 pDevice
									 ,CAnimationCtrl** ppAniCtrl) {return S_OK;}

	virtual void			Render(LPDIRECT3DDEVICE9 pDevice, const BONE* pRootBone = NULL) PURE;
	virtual void			Release();
	LPD3DXMESH				GetMesh() { return m_pMesh; }




};


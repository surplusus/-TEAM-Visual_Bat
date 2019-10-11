#pragma once
#include "Obj.h"
class CSummonTerrain :
	public CObj
{
public:
	CSummonTerrain();
	~CSummonTerrain();
private:
	LPD3DXMESH m_pMesh;
	INDEX* m_pIndex;
	LPDIRECT3DTEXTURE9 m_pAlphtexture;
private:
	void InitVertex();
public:
	virtual HRESULT			Initialize(void) override;
	virtual void			Progress(void)   override;
	virtual void			Render(void)     override;
	virtual void			Release(void)    override;
};


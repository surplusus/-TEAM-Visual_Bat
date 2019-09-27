#pragma once
class CBound;
class CBoundingMgr
{
	DECLARE_SINGLETON(CBoundingMgr)
public:
	CBoundingMgr();
	~CBoundingMgr();
private:
	map<BOUNDTYPE, CBound*> m_MapBounding;
public:
	HRESULT AddBounding(LPDIRECT3DDEVICE9 pDevice, BOUNDTYPE Type);
	void Bound_Render(BOUNDTYPE Type);
	void Release();
	const D3DXVECTOR3* GetMin(BOUNDTYPE Type);
	const D3DXVECTOR3* GetMax(BOUNDTYPE Type);
};


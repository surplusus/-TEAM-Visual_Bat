#pragma once
class CFrustum
{
	DECLARE_SINGLETON(CFrustum);
private:
	// 절두체를 생성하겠다.
	D3DXVECTOR3			m_vPoint[8];
	D3DXPLANE			m_Plane[6];
public: // Make Frustum
	void InitFrustum(void);
	void ConvertFrustum(VTXTEX* pVtxTex, const D3DXMATRIX* pMatrix);
public:
	int Culling(VTXTEX* pVtxTex, INDEX* pIndex);
	bool VertexInFrustum(const D3DXVECTOR3* pPoint);
	bool SphereInFrustum(float fRadius, const D3DXVECTOR3* pPoint);
	bool SphereInFrustum(SPHERE* pSphere);
private:
	CFrustum(void);
public:
	~CFrustum(void);
};


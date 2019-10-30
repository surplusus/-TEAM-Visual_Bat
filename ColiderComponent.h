#pragma once
class CBoundingBox;
class CObj;
class CParticle;
class ColiderComponent
{
public:
	ColiderComponent();
	ColiderComponent(CObj* pObj);
	ColiderComponent(CParticle* pParticle);


	~ColiderComponent();
private:
	CObj* m_pObj;
	CParticle* m_pParticle;
	D3DXMATRIX m_matWorld;
	D3DXVECTOR3 m_pvPosition;	
	float m_fRadius;	bool m_bColision;
	vector<VTXTEX> m_VerTexBuffer;
	CBoundingBox* m_pBoudingBox;


	LPD3DXMESH m_pMesh;
	LPD3DXMESH m_pSphareMesh;
public:
	void SetUp(D3DXVECTOR3 vPos, float fRadius, D3DXMATRIX BoneMatrix);

	void Render();
	bool CheckColision(ColiderComponent* pEnemy);
	void InitColider();
	void SetCollison(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax);
	void Update(D3DXVECTOR3 vPos);
	CObj* GetObj() { return m_pObj; }
};


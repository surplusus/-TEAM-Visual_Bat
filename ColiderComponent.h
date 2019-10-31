#pragma once
class CBoundingBox;

class ColiderComponent
{
public:
	ColiderComponent();
	~ColiderComponent();
protected:
	D3DXMATRIX m_matWorld;
	INFO m_Info;	
	float m_fRadius;	bool m_bColision;
	vector<VTXTEX> m_VerTexBuffer;
	CBoundingBox* m_pBoudingBox;
	LPD3DXMESH m_pMesh;
	LPD3DXMESH m_pSphareMesh;
public:
	void SetUp(INFO tInfo, float fRadius, D3DXMATRIX BoneMatrix);

	void Render();
	bool CheckColision(ColiderComponent* pEnemy);
	void InitColider();
	void SetCollison(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax);
	virtual void Update(D3DXVECTOR3 vPos);
public:	
	virtual COLISION_TYPE GetType() {return COLISION_TYPE_End;};
	void SetStateCol(bool bCol) { m_bColision = bCol; }
	bool GetStateCol() { return m_bColision; }
	void Release();
};


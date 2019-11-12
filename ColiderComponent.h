#pragma once
#include"BoundingSphere.h"
class CBound;
class ColiderComponent
{
public:
	ColiderComponent();
	~ColiderComponent();
protected:
	INFO m_Info;
	float m_fRadius;
	bool m_bColision;
	bool m_bErase;//지워질것인가;
	D3DXMATRIX m_ParentMatrix;
	SPHERE m_SphereInfo;
	vector<VTXTEX> m_VerTexBuffer;
	CBound * m_pBoxMesh;
	CBound* m_SphereMesh;
	float m_fAngle[ANGLE_END];
private:
	D3DXVECTOR3 m_vCenter;
public:
	virtual void SetUp(INFO tInfo, float fRadius, CBound* pMesh);
	virtual void Render();
	virtual void Update(D3DXVECTOR3 vPos);


	virtual bool CheckColision(ColiderComponent* pEnemy);
public:
	virtual COLISION_TYPE GetType() { return COLISION_TYPE_End; };
	void SetStateCol(bool bCol) { m_bColision = bCol; }
	bool GetStateCol() { return m_bColision; }
	bool GetStateErase() { return m_bErase; }
	void SetStateErase(bool bErase) { m_bErase = bErase; }
	void Release();
	void WorldSetting();
	SPHERE* GetSphere() { return &m_SphereInfo; }
};


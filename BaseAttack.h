#pragma once
#include"ParticleObj.h"
class CBaseAttack
	: public CParticleObj
{
public:
	CBaseAttack(INFO tInfo, float fRadius, D3DXVECTOR3 vAngle,STATUSINFO Status);
	~CBaseAttack();
public:

	virtual void Initalize();
	virtual bool Progress();
	virtual void Render();
	virtual void Release();
private:
	float m_fRadius;
	float m_fAngle[ANGLE_END];
	float m_fSize;
	float m_fMaxDistance;
	float m_fSpeed;
	float m_fLength;
	CUSTOMVERTEX m_VerTexInfo;
	D3DXVECTOR3 m_vMin;
	D3DXVECTOR3 m_vMax;
	D3DXMATRIX m_matWorld;
private:
	float m_fBaseDamage;
	
private:
	virtual void Setup_MultiTexture() override;
	virtual void SetUp_Particle() override;
	virtual void Render_Particle() override;
	virtual void RenderEnd_Particle() override;
	virtual void InitRenderState() override;
public:
	bool AddTail();

};


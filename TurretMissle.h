#pragma once
#include "ParticleObj.h"
class CTurretMissle :
	public CParticleObj
{
public:
	CTurretMissle(INFO tInfo, float Radius, D3DXVECTOR3 vAngle,CObj* pTarget);
	~CTurretMissle();

public:
	virtual void Initalize() ;
	virtual bool Progress()	 ;
	virtual void Render() 	 ;
	virtual void Release() 	 ;
private:
	float m_fRadius;
	float m_fSize;
	float m_fMaxDistance;
	float m_fSpeed;
	float m_fLength;
	CUSTOMVERTEX m_VerTexInfo;
	D3DXMATRIX m_matWorld;
	float m_fDamge;
private:
	CObj* m_pTarget;
	float m_BaseDamge;
private:
	virtual void SetUp_Particle()		override;
	virtual void Setup_MultiTexture()	override;
	virtual void Render_Particle()		override;
	virtual void RenderEnd_Particle()	override;
	virtual void InitRenderState()		override;
	
private:
	virtual bool Move_Chase(const D3DXVECTOR3* pDestPoint, const float& fSpeed);
	bool UpdateParticleDirection();
	void InitTail();
};


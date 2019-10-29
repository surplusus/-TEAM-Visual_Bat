#pragma once
#include"Particle.h"
class CEzealQ_Particle : public CParticle
{
public:
	CEzealQ_Particle();
	CEzealQ_Particle( INFO tInfo, float fRadius, D3DXVECTOR3 vAngle);
	~CEzealQ_Particle();
private:
	float m_fRadius;
	float m_fAngle[ANGLE_END];
	float m_fSize;
	float m_fMaxDistance;
	float m_fSpeed;
	float m_fLength;
	CUSTOMVERTEX m_VerTexInfo;
public:
	virtual void Initalize()override;
	virtual void Progress()	override;
	virtual void Render()	override;
	virtual void Release()	override;
private:
	virtual void SetUp_Particle() override;
	virtual void Setup_MultiTexture()override;
	virtual void Render_Particle() override;
	virtual void RenderEnd_Particle() override;
	virtual void InitRenderState() override;

	bool AddTail();

};


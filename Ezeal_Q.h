#pragma once
#include"Skill.h"
class CEzeal_Q :
	public CSkill
{
public:
	CEzeal_Q();
	~CEzeal_Q();
	CEzeal_Q(INFO& tInfo);
private:
	float m_fHeight;
	float m_fWidth;
	float m_ParticleExp;
	D3DXVECTOR3 m_vStartPosition;
	float m_fDistance;
	float m_fSpeed;
public:
	virtual HRESULT LoadAsset(const TCHAR* pFileName);
	virtual void RenderSetting();
	void Render_End();
	void WorldSetting();
public:
	virtual HRESULT Initialize()	;
	virtual void	Progress()		;
	virtual void	Render()		;
	virtual void	Release()		;
public:
	
};


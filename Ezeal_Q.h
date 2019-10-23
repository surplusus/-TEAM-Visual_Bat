#pragma once
#include"Skill.h"
class CEzeal_Q :
	public CSkill
{
public:
	CEzeal_Q();
	~CEzeal_Q();
private:
	float m_fHeight;
	float m_fWidth;
	float m_ParticleExp;
public:
	virtual HRESULT LoadAsset(const TCHAR* pFileName);
	virtual void RenderSetting();
	virtual LPD3DXMESH LoadModel(const TCHAR * pFileName);
	void Render_End();
	void WorldSetting();
public:
	virtual HRESULT Initialize()	;
	virtual void	Progress()		;
	virtual void	Render()		;
	virtual void	Release()		;
};


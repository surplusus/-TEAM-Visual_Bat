#pragma once
#include "Shader.h"
class CSkill  : public CShader	
{
public:
	CSkill();
	CSkill(INFO& tInfo);
	~CSkill();
protected:
	CShader * m_pShader;
	INFO			m_Info;
	float			m_fAngle[ANGLE_END];
protected:
	virtual HRESULT LoadAsset(const TCHAR* pFileName) { return S_OK; }
	virtual void RenderScene() {};
public:
	virtual HRESULT Initialize()	PURE;
	virtual void	Progress()		PURE;
	virtual void	Render()		PURE;
	virtual void	Release()		PURE;
};


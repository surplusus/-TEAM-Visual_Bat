#pragma once
#include"Obj.h"
#include"Shader.h"
class CSkill : public CObj, public CShader
{
public:
	CSkill();
	~CSkill();
protected:
	virtual HRESULT LoadAsset(const TCHAR* pFileName) { return S_OK; }
	virtual void RenderScene() {};
	virtual LPD3DXMESH LoadModel(const TCHAR * pFileName) { return NULL; }
public:
	virtual HRESULT Initialize()	PURE;
	virtual void	Progress()		PURE;
	virtual void	Render()		PURE;
	virtual void	Release()		PURE;

};


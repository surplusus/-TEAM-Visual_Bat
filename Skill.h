#pragma once
class CShader;
class CSkill 	
{
public:
	CSkill();
	CSkill(INFO& tInfo);
	~CSkill();
protected:
	CShader * m_pShader;
protected:
	virtual HRESULT LoadAsset(const TCHAR* pFileName) { return S_OK; }
	virtual void RenderScene() {};
public:
	virtual HRESULT Initialize()	PURE;
	virtual void	Progress()		PURE;
	virtual void	Render()		PURE;
	virtual void	Release()		PURE;
};


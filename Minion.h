#pragma once
#include "Dynamic.h"
class CMinion : public CDynamic
{
public:
	CMinion();
	virtual ~CMinion();

	bool				SetUp(string sName, string sFolderPath, string sFilePath);
	void				UpdateWorldMatrix();
	virtual HRESULT		Initialize() PURE;
	virtual void		Progress() PURE;
	virtual void		Render() PURE;
	virtual void		Release() PURE;
protected:
	basic_string<TCHAR>	m_sName;
	float				m_fSize;
	SPHERE				m_SphereForPick;
	LPD3DXMESH			m_pMeshSphere;
protected:
	bool			SetUpPickingShere(const float r, const D3DXVECTOR3 v);
	bool			Render_PickingShere();
public:
	const TCHAR*	GetName();
};


#pragma once
#include "Dynamic.h"
class Minion : public CDynamic
{
public:
	Minion();
	virtual ~Minion();

	void				SetUp(string sName, string sFolderPath, string sFilePath);
	void				UpdateWolrdMatrix();
	virtual HRESULT		Initialize() PURE;
	virtual void		Progress() PURE;
	virtual void		Render() PURE;
	virtual void		Release() PURE;
private:
	string		m_sName;
	float		m_fSize;
	SPHERE					m_SphereForPick;
	LPD3DXMESH				m_MeshSphere;
protected:
	bool		SetUpPickingShere(const float r, const D3DXVECTOR3 v);
	bool		Render_PickingShere();
};


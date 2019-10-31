#pragma once
#include"Obj.h"
#include"AnimationCtrl.h"
class CDynamic
	:public CObj
{
public:
	CDynamic();
	virtual ~CDynamic();
protected:
	CAnimationCtrl*		m_pAnimationCtrl;
	bool				m_bMove;
	float				m_fHeight;

public:
	bool				Update_vPos_ByDestPoint(const D3DXVECTOR3* pDestPoint, const float&fSpeed);

public:

	virtual HRESULT		Initialize() PURE;
	virtual void		Progress()	 PURE;
	virtual void		Render()	 PURE;
	virtual void		Release()	 PURE;
public:
	
};


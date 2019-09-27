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
	bool				m_bMove;
	CAnimationCtrl*		m_pAnimationCtrl;
public:
	bool				Move_Chase(const D3DXVECTOR3* pDestPoint, const float&fSpeed);
public:

	virtual HRESULT		Initialize() PURE;
	virtual void		Progress()PURE;
	virtual void		Render() PURE;
	virtual void		Release() ;

};


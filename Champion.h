#pragma once
#include "Dynamic.h"
class CObjMgr;
class CChampion :
	public CDynamic
{
public:
	CChampion();
	~CChampion() {}
protected:
	TCHAR*					m_strChampionName;
	CObjMgr*				m_ObjMgr;
	D3DXVECTOR3				m_vecMouseHitPoint;
protected:
	bool				MouseCheck();		// ���콺 ��ŷ����Ʈ�� ã������ true;
public:
	virtual	HRESULT		Initialize()	PURE;
	virtual void		Progress()		PURE;
	virtual void		Render()		PURE;
	virtual void		Release()		PURE;
};


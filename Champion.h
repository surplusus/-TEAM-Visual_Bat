#pragma once
#include "Dynamic.h"
class CObjMgr;
class CChampion :
	public CDynamic
{
public:
	CChampion();
	~CChampion();
protected:
	CObjMgr*				m_ObjMgr;
	float					m_fSize = 1.f;
	D3DXVECTOR3				m_MouseHitPoint;
	bool					m_bPicked;
protected:
	// Update
	void		UpdateWorldMatrix();
	void		SetDirectionToMouseHitPoint();
	//bool		EnqueueMousePickingFunc();		// ���콺 ��ŷ����Ʈ�� ã������ true /  g_MouseHitPoint �� g_bHitFloor �� ����� �޴´�
	// Algorithm

//private:
	// Thread or ������ ���� ���̶� �׳� ���� è�Ǿ��� �θ�
	bool	MapCheckThreadLoop(int number, const VTXTEX* vtx);
public:
	virtual	HRESULT		Initialize()	PURE;
	virtual void		Progress()		PURE;
	virtual void		Render()		PURE;
	virtual void		Release()		PURE;
};


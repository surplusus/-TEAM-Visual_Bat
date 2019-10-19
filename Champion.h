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
protected:
	// Update
	void		UpdateWorldMatrix();
	void		SetDirectionToMouseHitPoint();
	bool		EnqueueMousePickingFunc();		// ���콺 ��ŷ����Ʈ�� ã������ true /  g_MouseHitPoint �� g_bHitFloor �� ����� �޴´�
	// Algorithm
	void		
//private:
	// Thread or ������ ���� ���̶� �׳� ���� è�Ǿ��� �θ�
	static bool	MapCheckThreadLoop(int number, const VTXTEX* vtx);
	static bool					bPick;
protected:
	static D3DXVECTOR3			g_MouseHitPoint;
	static std::atomic<bool>	g_bHitFloor;
public:
	virtual	HRESULT		Initialize()	PURE;
	virtual void		Progress()		PURE;
	virtual void		Render()		PURE;
	virtual void		Release()		PURE;
};


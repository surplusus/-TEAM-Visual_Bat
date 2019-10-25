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
	float					m_fSize;
	D3DXVECTOR3				m_MouseHitPoint;
	bool					m_bPicked;
	SPHERE					m_SphereForPick;
	LPD3DXMESH				m_MeshSphere;
protected:
	// Update
	void		UpdateWorldMatrix();
	void		SetDirectionToMouseHitPoint();
	bool		SetUpPickingShere(const float r, const D3DXVECTOR3 v);
	bool		Render_PickingShere();
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


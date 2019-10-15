#pragma once
#include "StateObj.h"
class CObj : public CStateObj
{
public:
	CObj();
	virtual ~CObj();
protected:
	SORTID		m_SortID;//정렬 순서 지정

	INFO		m_Info;//오브젝트 정보 (pos : 캐릭터 위치, look : 카메라 방향, dir : 캐릭터 전방, matWorld
	float		m_fAngle[ANGLE_END];//각도(x,y,z)
protected:
	VTXTEX*		m_pOriVtx;//원본 버텍스 (mesh 정보에 있는 vertex)
	VTXTEX*		m_pConVtx;//변화된 버텍스
	int			m_FaceNum;// <- 지환이 새로추가한 맴버(Champion, map을 위해 만듦)
	int			m_VtxNum;
protected:
	D3DXVECTOR3 m_vMin;//최소 최대값
	D3DXVECTOR3 m_vMax;//최소 최대값
	bool		m_bColl;//충돌여부 검사 변수
public:
	const D3DXVECTOR3* GetMinData() const {
		return &m_vMin;
	}
	const D3DXVECTOR3* GetMaxData() const
	{
		return &m_vMax;
	}
public:
	SORTID GetSortID(void) {
		return m_SortID;
	}
	const INFO* GetInfo() const
	{
		return &m_Info;
	}
	const VTXTEX* GetVtxInfo() const
	{
		return m_pOriVtx;
	}
	const int GetVtxNumber()
	{
		return m_FaceNum * 3;
	}
public:
	virtual void SetContantTable() {}
public:
	virtual HRESULT Initialize() PURE;
	virtual void Progress()PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	
};
#pragma once
#include "StateObj.h"
class CObj : public CStateObj
{
public:
	CObj();
	virtual ~CObj();
protected:
	SORTID		m_SortID;//정렬 순서 지정
	
	INFO		m_Info;//오브젝트 정보
	float		m_fAngle[ANGLE_END];//각도(x,y,z)
protected:
	VTXTEX*		m_pOriVtx;//원본 버텍스
	VTXTEX*		m_pConVtx;//변화된 버텍스
	int			m_FaceNum;// <- 지환이 새로추가한 맴버(Champion을 위해 만듦)
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
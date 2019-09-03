#pragma once
class CObj
{
public:
	CObj();
	CObj(D3DXVECTOR3 vPos, D3DXVECTOR3 vDir, D3DXVECTOR3 vRot)
		:m_vPosition(vPos),m_vDirection(vDir),m_vRotation(vRot){}
	virtual ~CObj();
protected:
	D3DXMATRIXA16 m_matWorld;
	D3DXVECTOR3   m_vRotation;
	D3DXVECTOR3   m_vDirection;
	D3DXVECTOR3	  m_vPosition;
public:
	virtual void SetUp()  =0;
	virtual void Update() =0;
	virtual void Render() =0;
	D3DXVECTOR3& GetPosition() { return m_vPosition; }
};


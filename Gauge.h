#pragma once
class CImage_Loader;
class CGauge
{
public:
	CGauge();
	virtual ~CGauge();
public:
	virtual void Initialize() = 0;
	virtual void Progress()	  = 0;
	virtual void Render()	  = 0;
	virtual void Release()	  = 0;

protected:
	int				m_HP;
	int				m_MP;
	D3DXVECTOR3		m_vPosition;
	CImage_Loader*	m_Loader;
};

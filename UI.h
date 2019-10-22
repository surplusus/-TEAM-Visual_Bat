#pragma once
class CImage_Loader;
class CUI
{
public:
	CUI();
	CUI(string name, string FileName, D3DXVECTOR3 pos, D3DXVECTOR3 vScale)
		:m_name(name)
		, m_vPosition(pos)
		, m_FileName(FileName)
		, m_vScale(vScale)	{	
		m_Rect = { 0,0,0,0 };

	}
	~CUI();
public:
	virtual void Initialize() = 0;
	virtual int Progress() =0;
	virtual void Render() = 0;
	virtual void Render(D3DXVECTOR3 pos, D3DXVECTOR3 scale) = 0;
	virtual void Release() = 0;

protected:
	D3DXVECTOR3				m_vPosition;
	D3DXVECTOR3				m_vScale;
	D3DXVECTOR3				m_vCenter;
	string					m_FileName;
	RECT					m_Rect;
	CImage_Loader*			m_ImageLoader;
	string					m_name;

public:
	RECT GetRect();
	string GetName();
	D3DXVECTOR3 GetPosition() { 
		return m_vPosition; }
	void SetCenterPos();

public:
	string GetFileName() { return m_FileName; }
};


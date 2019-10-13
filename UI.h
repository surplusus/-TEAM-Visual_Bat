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
	virtual void Render(D3DXVECTOR3 pos) = 0;

protected:
	D3DXVECTOR3				m_vPosition;
	D3DXVECTOR3				m_vScale;
	string					m_FileName;
	RECT					m_Rect;
	CImage_Loader*			m_ImageLoader;
	string					m_name;

public:

	RECT GetRect()    { return m_Rect; }
	string GetName() { return m_name; }
	D3DXVECTOR3 GetPosition() { return m_vPosition; }

};


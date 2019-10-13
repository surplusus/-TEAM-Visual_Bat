#pragma once
#include "Obj.h"
using std::vector;

class CFloor :
	public CObj
{
public:
	CFloor();
	virtual ~CFloor();
private:
	vector<ST_PNT_VERTEX>		m_vecVertex;
	vector<WORD>				m_vecIndice;
	D3DMATERIAL9				m_material;
	LPDIRECT3DTEXTURE9			m_texture;
	IDirect3DVertexBuffer9*		m_VertexBuffer;
	IDirect3DIndexBuffer9*		m_IndexBuffer;
	D3DXMATRIXA16				m_matWorld;
private:
	virtual HRESULT Initialize() override;
	virtual void Progress()		 override;
	virtual void Render()		 override;
	virtual void Release()		 override;
public:
	const D3DXVECTOR3& GetVertexPosition(IN int index, OUT int& vertexSize);
	D3DXVECTOR3		   GetPickingPoint();
};


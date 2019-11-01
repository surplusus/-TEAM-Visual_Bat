#pragma once

#include "Defines.h"

class CParticle 
{
public:
	CParticle();
	virtual ~CParticle();
protected:
	vector<CUSTOMVERTEX>	m_vecVertexParticle;
	vector<PARTICLE_VERTEX> m_vecVertex_Multi;	
	LPDIRECT3DTEXTURE9 m_pTex0;
	LPDIRECT3DTEXTURE9 m_pTex1;
	LPDIRECT3DTEXTURE9 m_pTex2;
	INFO m_Info;
	vector<DWORD> m_vecRenderInitData;
	bool m_bCol;//자신이 삭제 되어야할 객체인가를 판단한다.
public:
	virtual void Initalize();
	virtual bool Progress();
	virtual void Render();
	virtual void Release();

protected:
	virtual void SetUp_Particle();
	virtual void Render_Particle();
	virtual void RenderEnd_Particle();
	virtual void Update_Particle();
	virtual void Setup_MultiTexture();
	virtual void InitRenderState();
public:
	DWORD fword(float f)
	{
		return *((DWORD*)&f);
	}
public:
	void SetStateCol(bool bErase) { m_bCol = bErase; }
	

};

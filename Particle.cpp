#include"BaseInclude.h"
#include "Particle.h"


CParticle::CParticle(void)
{
}

CParticle::~CParticle(void)
{
}

void CParticle::Render_Particle()
{
	D3DXMATRIXA16	matWorld;
	D3DXMatrixIdentity(&matWorld);
	SetTransform(D3DTS_WORLD, &matWorld);

	SetRenderState(D3DRS_LIGHTING, false);
	SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	SetRenderState(D3DRS_ZWRITEENABLE, false);

	{
		SetRenderState(D3DRS_POINTSCALEENABLE, true);
		SetRenderState(D3DRS_POINTSIZE, fword(10.0f));

		SetRenderState(D3DRS_POINTSCALE_A, fword(0.0f));
		SetRenderState(D3DRS_POINTSCALE_B, fword(0.0f));
		SetRenderState(D3DRS_POINTSCALE_C, fword(1.0f));

		SetRenderState(D3DRS_POINTSPRITEENABLE, true);

		SetRenderState(D3DRS_POINTSIZE_MIN, fword(0.0f));
		SetRenderState(D3DRS_POINTSIZE_MAX, fword(100.0f));

		GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

		SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	GetDevice()->SetFVF(ST_PC_VERTEX::FVF);
	SetTexture(0, GetTexture(L"alpha_tex.tga"));

	GetDevice()->DrawPrimitiveUP(D3DPT_POINTLIST,
		m_vecVertexPArticle.size(),
		&m_vecVertexPArticle[0],
		sizeof(ST_PC_VERTEX));

	SetRenderState(D3DRS_ZWRITEENABLE, true);
	SetRenderState(D3DRS_ALPHATESTENABLE, false);
	SetRenderState(D3DRS_LIGHTING, true);
}

void CParticle::Setup_MultiTexture()
{
	D3DXCreateTextureFromFile(GetDevice(), L"./Resource/Shader/alpha_tex.tga", &m_pTex1);

	PARTICLE_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex_Multi.push_back(v);

	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex_Multi.push_back(v);

	v.p = D3DXVECTOR3(2, 0, 0);
	v.t = D3DXVECTOR2(1, 1);
	m_vecVertex_Multi.push_back(v);



	v.p = D3DXVECTOR3(2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex_Multi.push_back(v);

	v.p = D3DXVECTOR3(2, 0, 0);
	v.t = D3DXVECTOR2(1, 1);
	m_vecVertex_Multi.push_back(v);

	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex_Multi.push_back(v);


}

#include"BaseInclude.h"
#include "Particle.h"


CParticle::CParticle(void)
{
}

CParticle::~CParticle(void)
{
	Release();
}

void CParticle::Initalize()
{
	Setup_MultiTexture();
	SetUp_Particle();
	InitRenderState();
}

void CParticle::Progress()
{
	Update_Particle();
}

void CParticle::Render()
{
	Render_Particle();
}

void CParticle::Release()
{
	m_pTex0->Release();	m_pTex0 = NULL;
	m_pTex1->Release();	m_pTex1 = NULL;
	m_pTex2->Release();	m_pTex2 = NULL;
	m_vecRenderInitData.clear();
}

void CParticle::SetUp_Particle()
{
	m_vecVertexParticle.resize(100);

	for (int i = 0; i < m_vecVertexParticle.size(); i++)
	{
		float fRadius = rand() % 100 / 10.f;
		m_vecVertexParticle[i].p = D3DXVECTOR3(0, 0, fRadius);
		D3DXVECTOR3 vAngle = D3DXVECTOR3(
			D3DXToRadian(rand() % 3600 / 10.f),
			D3DXToRadian(rand() % 3600 / 10.f),
			D3DXToRadian(rand() % 3600 / 10.f)
		);
		D3DXMATRIXA16 matR, matWorld;
		D3DXQUATERNION quatR(vAngle.x, vAngle.y, vAngle.z, 1.f);
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixRotationQuaternion(&matR, &quatR);
		matWorld *= matR;

		D3DXVec3TransformCoord(&m_vecVertexParticle[i].p, &m_vecVertexParticle[i].p, &matWorld);
		m_vecVertexParticle[i].c = D3DCOLOR_ARGB(255, 100, 70, 20);
	}
}

void CParticle::Render_Particle()
{

	SetTransform(D3DTS_WORLD, &m_Info.matWorld);

	
	

	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

	GetDevice()->SetRenderState(D3DRS_BLENDOP,	D3DBLENDOP_ADD);
	GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);



	SetRenderState(D3DRS_LIGHTING,		    false);
	SetRenderState(D3DRS_ALPHABLENDENABLE,  true);
	SetRenderState(D3DRS_ZWRITEENABLE,		false);

	{
		SetRenderState(D3DRS_POINTSCALEENABLE,	true);
		SetRenderState(D3DRS_POINTSIZE,			fword(10.f));

		SetRenderState(D3DRS_POINTSCALE_A, fword(0.f));
		SetRenderState(D3DRS_POINTSCALE_B, fword(0.f));
		SetRenderState(D3DRS_POINTSCALE_C, fword(0.f));

		SetRenderState(D3DRS_POINTSPRITEENABLE, true);

		SetRenderState(D3DRS_POINTSIZE_MIN, fword(0.f));
		SetRenderState(D3DRS_POINTSIZE_MAX, fword(100.f));

		GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
		
		GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	SetTexture(0, m_pTex0);
	SetTexture(1, m_pTex1);
	SetTexture(2, m_pTex2);
	

	GetDevice()->SetFVF(CUSTOMVERTEX::FVF);

	GetDevice()->DrawPrimitiveUP(D3DPT_POINTLIST,
		m_vecVertexParticle.size(),
		&m_vecVertexParticle[0],
		sizeof(CUSTOMVERTEX));

	RenderEnd_Particle();

}

void CParticle::RenderEnd_Particle()
{
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP,	m_vecRenderInitData[0]);
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1,	m_vecRenderInitData[1]);
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2,	m_vecRenderInitData[2]);
	GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP,	m_vecRenderInitData[3]);
	GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1,	m_vecRenderInitData[4]);

	GetDevice()->SetRenderState(D3DRS_BLENDOP,				m_vecRenderInitData[5]);
	GetDevice()->SetRenderState(D3DRS_SRCBLEND,				m_vecRenderInitData[6]);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND,			m_vecRenderInitData[7]);

	SetRenderState(D3DRS_LIGHTING,							m_vecRenderInitData[8]);
	SetRenderState(D3DRS_ALPHABLENDENABLE,					m_vecRenderInitData[9]);
	SetRenderState(D3DRS_ZWRITEENABLE,						m_vecRenderInitData[10]);
	SetRenderState(D3DRS_POINTSCALEENABLE,					m_vecRenderInitData[11]);
	SetRenderState(D3DRS_POINTSIZE,							m_vecRenderInitData[12]);
	SetRenderState(D3DRS_POINTSCALE_A,						m_vecRenderInitData[13]);
	SetRenderState(D3DRS_POINTSCALE_B,						m_vecRenderInitData[14]);
	SetRenderState(D3DRS_POINTSCALE_C,						m_vecRenderInitData[15]);
	SetRenderState(D3DRS_POINTSPRITEENABLE,					m_vecRenderInitData[16]);
	SetRenderState(D3DRS_POINTSIZE_MIN,						m_vecRenderInitData[17]);
	SetRenderState(D3DRS_POINTSIZE_MAX,						m_vecRenderInitData[18]);

	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP,	m_vecRenderInitData[19]);
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1,	m_vecRenderInitData[20]);
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2,	m_vecRenderInitData[21]);
	GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP,	m_vecRenderInitData[22]);
	GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1,	m_vecRenderInitData[23]);
	GetDevice()->SetRenderState(D3DRS_BLENDOP,				m_vecRenderInitData[24]);
	GetDevice()->SetRenderState(D3DRS_SRCBLEND,				m_vecRenderInitData[25]);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND,			m_vecRenderInitData[26]);
	

}

void CParticle::Update_Particle()
{
	static int nAlpha = 0;
	static int nDelta = 4;
	nAlpha += nDelta;
	if (nAlpha > 255)
	{
		nAlpha = 255;
		nDelta *= -1;
	}
	if (nAlpha < 0)
	{
		nAlpha = 0;
		nDelta *= -1;
	}

	for (int i = 0; i < m_vecVertexParticle.size(); i++)
	{
		if (i % 2) continue;
		m_vecVertexParticle[i].c = D3DCOLOR_ARGB(255, 100, 70, 20);
	}
}

void CParticle::Setup_MultiTexture()
{

	D3DXCreateTextureFromFileA(GetDevice(), "./Resource/Shader/Albedo00.jpg", &m_pTex0);
	D3DXCreateTextureFromFileA(GetDevice(), "./Resource/Shader/Fieldstone_DM.tga", &m_pTex1);
	D3DXCreateTextureFromFileA(GetDevice(), "./Resource/Shader/alpha_tex.tga", &m_pTex2);
	
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

void CParticle::InitRenderState()
{
	DWORD pWord;

	GetDevice()->GetTextureStageState(0, D3DTSS_ALPHAOP,	&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_ALPHAARG1,	&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_ALPHAARG2,	&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_COLOROP,	&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_COLORARG1,	&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_BLENDOP,				&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_SRCBLEND,				&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_DESTBLEND,			&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_LIGHTING,				&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_ALPHABLENDENABLE,		&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_ZWRITEENABLE,			&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSCALEENABLE,		&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSIZE,			&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSCALE_A,			&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSCALE_B,			&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSCALE_C,			&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSPRITEENABLE,	&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSIZE_MIN,		&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSIZE_MAX,		&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_ALPHAOP,	&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_ALPHAARG1,	&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_ALPHAARG2,	&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_COLOROP,	&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_COLORARG1,	&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_BLENDOP,				&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_SRCBLEND,				&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_DESTBLEND,			&pWord);m_vecRenderInitData.push_back(pWord);
}

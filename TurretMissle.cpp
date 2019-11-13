#include "BaseInclude.h"
#include "TurretMissle.h"
#include"Obj.h"
#include"ParticleColider.h"
#include"BoundingBox.h"
#include"MathMgr.h"
CTurretMissle::CTurretMissle(INFO tInfo, float fRadius, D3DXVECTOR3 vAngle,CObj* pTarget)
	:m_fRadius(fRadius), m_fSize(5.0f), m_fMaxDistance(2.0f), m_fSpeed(0.1f), m_fLength(1.0f), m_BaseDamge(30.0f), m_pTarget(pTarget)
{
	m_pTex0 = NULL; m_pTex1 = NULL; m_pTex2 = NULL;	m_pColider = NULL;
	m_Info = tInfo;
	m_fAngle[ANGLE_X] = vAngle.x; m_fAngle[ANGLE_Y] = vAngle.y; m_fAngle[ANGLE_Z] = vAngle.z;
	m_VerTexInfo.p = m_Info.vPos;
	m_StatusInfo.fBase_Attack = 30.0f;
}


CTurretMissle::~CTurretMissle()
{
}

void CTurretMissle::Initalize()
{

	Setup_MultiTexture();
	InitRenderState();
	D3DXMATRIX matWorld;

	//콜라이더 설정
	m_pColider = new CParticleColider(this);
	m_pColider->SetUp(m_Info, 1.0f, new CBoundingBox);
	UpdateParticleDirection();
	AddTail();
}

bool CTurretMissle::Progress()
{

	if(m_pTarget)
		Move_Chase(&m_pTarget->GetInfo()->vPos, 2.0f);

	UpdateMatrix();
	UpdateParticleDirection();
	Update_Particle();
	
	if (m_pColider->GetStateCol())		
		return false;

	return true;
}

void CTurretMissle::Render()
{
	Render_Particle();
}

void CTurretMissle::Release()
{

	if (m_pColider) { SAFE_DELETE(m_pColider);	m_pColider = NULL; }
	if (m_pTex0) { m_pTex0->Release();		m_pTex0 = NULL; }
	if (m_pTex1) { m_pTex1->Release();		m_pTex1 = NULL; }
	if (m_pTex2) { m_pTex2->Release();		m_pTex2 = NULL; }
}

void CTurretMissle::SetUp_Particle()
{

	D3DXMATRIXA16 matR, matWorld, matTrans, matScale;
	m_VerTexInfo.c = D3DCOLOR_ARGB(255, 100, 70, 20);
	m_vecVertexParticle.push_back(m_VerTexInfo);
}

void CTurretMissle::Setup_MultiTexture()
{

	D3DXCreateTextureFromFileA(GetDevice(), "./Resource/Ez/Particles/common_Flare-Rainbow_blue_green_02.dds", &m_pTex0);
	D3DXCreateTextureFromFileA(GetDevice(), "./Resource/Ez/Particles/Ezreal_Base_R_Bow_Arrow.dds", &m_pTex1);
	D3DXCreateTextureFromFileA(GetDevice(), "./Resource/Ez/Particle/Ezreal_Base_Z_solar_tag.dds", &m_pTex2);

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

void CTurretMissle::Render_Particle()
{
	if (m_vecVertexParticle.empty())
		return;

	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	{
		//Stage1
		GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		GetDevice()->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_ADD);
		GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	}
	{
		//Stage2
		GetDevice()->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		GetDevice()->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		GetDevice()->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
		GetDevice()->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);
		GetDevice()->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		GetDevice()->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


	}
	{
		//Stage3
		GetDevice()->SetSamplerState(2, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		GetDevice()->SetSamplerState(2, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

		GetDevice()->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, 0);
		GetDevice()->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_ADD);
		GetDevice()->SetTextureStageState(2, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		GetDevice()->SetTextureStageState(2, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	}


	{
		SetRenderState(D3DRS_POINTSCALEENABLE, true);
		SetRenderState(D3DRS_POINTSIZE, fword(m_fSize));

		SetRenderState(D3DRS_POINTSCALE_A, fword(100.f));
		SetRenderState(D3DRS_POINTSCALE_B, fword(100.f));
		SetRenderState(D3DRS_POINTSCALE_C, fword(100.f));

		SetRenderState(D3DRS_POINTSPRITEENABLE, true);

		SetRenderState(D3DRS_POINTSIZE_MIN, fword(0.f));
		SetRenderState(D3DRS_POINTSIZE_MAX, fword(100.f));

		SetRenderState(D3DRS_LIGHTING, false);
		SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		SetRenderState(D3DRS_ZWRITEENABLE, false);


		GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	}
	GetDevice()->SetFVF(CUSTOMVERTEX::FVF);
	SetTexture(2, m_pTex0);		SetTexture(1, m_pTex1);		SetTexture(0, m_pTex2);

	GetDevice()->DrawPrimitiveUP(D3DPT_POINTLIST,
		m_vecVertexParticle.size(),
		&m_vecVertexParticle[0],
		sizeof(CUSTOMVERTEX));
	RenderEnd_Particle();
	SetTexture(0, NULL);	SetTexture(1, NULL);	SetTexture(2, NULL);
}

void CTurretMissle::RenderEnd_Particle()
{
	int i = 0;
	GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, m_vecRenderInitData[i++]);
	GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, m_vecRenderInitData[i++]);

	GetDevice()->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, m_vecRenderInitData[i++]);
	GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, m_vecRenderInitData[i++]);
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, m_vecRenderInitData[i++]);
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, m_vecRenderInitData[i++]);

	//Stage2	 													
	GetDevice()->SetSamplerState(1, D3DSAMP_MINFILTER, m_vecRenderInitData[i++]);
	GetDevice()->SetSamplerState(1, D3DSAMP_MAGFILTER, m_vecRenderInitData[i++]);

	GetDevice()->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, m_vecRenderInitData[i++]);
	GetDevice()->SetTextureStageState(1, D3DTSS_COLOROP, m_vecRenderInitData[i++]);
	GetDevice()->SetTextureStageState(1, D3DTSS_ALPHAARG1, m_vecRenderInitData[i++]);
	GetDevice()->SetTextureStageState(1, D3DTSS_ALPHAARG2, m_vecRenderInitData[i++]);
	//Stage3
	GetDevice()->SetSamplerState(2, D3DSAMP_MINFILTER, m_vecRenderInitData[i++]);
	GetDevice()->SetSamplerState(2, D3DSAMP_MAGFILTER, m_vecRenderInitData[i++]);

	GetDevice()->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, m_vecRenderInitData[i++]);
	GetDevice()->SetTextureStageState(2, D3DTSS_COLOROP, m_vecRenderInitData[i++]);
	GetDevice()->SetTextureStageState(2, D3DTSS_ALPHAARG1, m_vecRenderInitData[i++]);
	GetDevice()->SetTextureStageState(2, D3DTSS_ALPHAARG2, m_vecRenderInitData[i++]);


	GetDevice()->SetRenderState(D3DRS_BLENDOP, m_vecRenderInitData[i++]);
	GetDevice()->SetRenderState(D3DRS_SRCBLEND, m_vecRenderInitData[i++]);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND, m_vecRenderInitData[i++]);

	SetRenderState(D3DRS_POINTSCALEENABLE, m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSIZE, m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSCALE_A, m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSCALE_B, m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSCALE_C, m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSPRITEENABLE, m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSIZE_MIN, m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSIZE_MAX, m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_LIGHTING, m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_ZWRITEENABLE, true);
	SetRenderState(D3DRS_ALPHABLENDENABLE, false);

}

void CTurretMissle::InitRenderState()
{
	DWORD pWord;

	GetDevice()->GetSamplerState(0, D3DSAMP_MINFILTER, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetSamplerState(0, D3DSAMP_MAGFILTER, &pWord); m_vecRenderInitData.push_back(pWord);

	GetDevice()->GetTextureStageState(0, D3DTSS_TEXCOORDINDEX, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_COLOROP, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_ALPHAARG1, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_ALPHAARG2, &pWord); m_vecRenderInitData.push_back(pWord);

	//Stage2	 												
	GetDevice()->GetSamplerState(1, D3DSAMP_MINFILTER, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetSamplerState(1, D3DSAMP_MAGFILTER, &pWord); m_vecRenderInitData.push_back(pWord);

	GetDevice()->GetTextureStageState(1, D3DTSS_TEXCOORDINDEX, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(1, D3DTSS_COLOROP, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(1, D3DTSS_ALPHAARG1, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(1, D3DTSS_ALPHAARG2, &pWord); m_vecRenderInitData.push_back(pWord);

	//Stage3											
	GetDevice()->GetSamplerState(2, D3DSAMP_MINFILTER, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetSamplerState(2, D3DSAMP_MAGFILTER, &pWord); m_vecRenderInitData.push_back(pWord);

	GetDevice()->GetTextureStageState(2, D3DTSS_TEXCOORDINDEX, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(2, D3DTSS_COLOROP, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(2, D3DTSS_ALPHAARG1, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(2, D3DTSS_ALPHAARG2, &pWord); m_vecRenderInitData.push_back(pWord);

	GetDevice()->GetRenderState(D3DRS_BLENDOP, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_SRCBLEND, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_DESTBLEND, &pWord); m_vecRenderInitData.push_back(pWord);


	GetDevice()->GetRenderState(D3DRS_POINTSCALEENABLE, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSIZE, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSCALE_A, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSCALE_B, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSCALE_C, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSPRITEENABLE, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSIZE_MIN, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSIZE_MAX, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_LIGHTING, &pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_ZWRITEENABLE, &pWord); m_vecRenderInitData.push_back(pWord);

}

bool CTurretMissle::AddTail()
{


}

bool CTurretMissle::UpdateParticleDirection()
{
	return true;

}
#include "BaseInclude.h"
#include "EzealQ_Particle.h"
#include"ParticleColider.h"
#include"BoundingBox.h"
CEzealQ_Particle::CEzealQ_Particle()
	:m_fRadius(0), m_fSize(0)
{
	m_pTex0 = NULL; m_pTex1 = NULL; m_pTex2 = NULL;
	m_VerTexInfo.p = { 0,0,0 };
	m_VerTexInfo.c = D3DCOLOR_ARGB( 0,0,0,0 );
	m_fAngle[ANGLE_X] = 0; m_fAngle[ANGLE_Y] = 0; m_fAngle[ANGLE_X] = 0;
}

CEzealQ_Particle::CEzealQ_Particle(INFO tInfo, float fRadius, D3DXVECTOR3 vAngle)
	:m_fRadius(fRadius), m_fSize(5.0f), m_fMaxDistance(2.0f), m_fSpeed(2.0f), m_fLength(1.0f), m_BaseDamge(30.0f)
{
	m_pTex0 = NULL; m_pTex1 = NULL; m_pTex2 = NULL;	m_pColider = NULL;
	m_Info = tInfo;
	m_fAngle[ANGLE_X] = vAngle.x; m_fAngle[ANGLE_Y] = vAngle.y; m_fAngle[ANGLE_Z] = vAngle.z;
	m_VerTexInfo.p = m_Info.vPos;
	
}


CEzealQ_Particle::~CEzealQ_Particle()
{
	Release();
}




bool CEzealQ_Particle::StatusInit(STATUSINFO * Status, SKILL_LEVEL lv)
{
	m_BaseDamge += Status->fBase_Attack + Status->fMagic_Attack;
	m_StatusInfo.fBase_Attack = m_BaseDamge;
	switch (lv)
	{
		case SKILL_LEVEL0:
			return false;
		case SKILL_LEVEL1:
			Status->fMana -= 50.0f; return true;
		case SKILL_LEVEL2:

			Status->fMana -= 60.0f; return true;
		case SKILL_LEVEL3:

			Status->fMana -= 70.0f; return true;
		case SKILL_LEVEL4:
			Status->fMana -= 80.0f; return true;
	}
}

void CEzealQ_Particle::Initalize()
{
	Setup_MultiTexture();
	SetUp_Particle();
	InitRenderState();
	
	//콜라이더 설정
	m_pColider = new CParticleColider(this);
	m_pColider->SetUp(m_Info, 0.5f,new CBoundingBox);
	
}

bool CEzealQ_Particle::Progress()
{
	Update_Particle();
	if (m_bCol)
		return false;
	if (!AddTail()) return false;

	return true;

}

void CEzealQ_Particle::Render()
{
	Render_Particle();	
}

void CEzealQ_Particle::Release()
{
	if (m_pColider)		{ SAFE_DELETE(m_pColider);	m_pColider = NULL;	 }
	if (m_pTex0)		{ m_pTex0->Release();		m_pTex0	   = NULL;   }
	if (m_pTex1)		{ m_pTex1->Release();		m_pTex1	   = NULL;   }
	if (m_pTex2)		{ m_pTex2->Release();		m_pTex2	   = NULL;   }

}

void CEzealQ_Particle::SetUp_Particle()
{	
	
	D3DXMATRIXA16 matR, matWorld,matTrans,matScale;
	m_VerTexInfo.c = D3DCOLOR_ARGB(255, 100, 70, 20);
	m_vecVertexParticle.push_back(m_VerTexInfo);	
}

void CEzealQ_Particle::Setup_MultiTexture()
{

	D3DXCreateTextureFromFileA(GetDevice(), "./Resource/Ez/Particles/Ezreal_Base_R_trail.dds", &m_pTex0);
	D3DXCreateTextureFromFileA(GetDevice(), "./Resource/Ez/Particles/Ezreal_Base_Q_mis_trail.dds", &m_pTex1);
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

void CEzealQ_Particle::Render_Particle()
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
		GetDevice()->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD );
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
		
		SetRenderState(D3DRS_POINTSIZE_MIN,		fword(0.f));
		SetRenderState(D3DRS_POINTSIZE_MAX,		fword(100.f));

		SetRenderState(D3DRS_LIGHTING,			false);
		SetRenderState(D3DRS_ALPHABLENDENABLE,	true);
		SetRenderState(D3DRS_ZWRITEENABLE,		false);


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

void CEzealQ_Particle::RenderEnd_Particle()
{
	int i = 0;
	GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER,				m_vecRenderInitData[i++]); 
	GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER,				m_vecRenderInitData[i++]); 
				 													
	GetDevice()->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX,		m_vecRenderInitData[i++]); 
	GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP,			m_vecRenderInitData[i++]); 
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1,			m_vecRenderInitData[i++]);
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2,			m_vecRenderInitData[i++]);
				 													
	//Stage2	 													
	GetDevice()->SetSamplerState(1, D3DSAMP_MINFILTER,				m_vecRenderInitData[i++]); 
	GetDevice()->SetSamplerState(1, D3DSAMP_MAGFILTER,				m_vecRenderInitData[i++]); 
				 																		
	GetDevice()->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX,		m_vecRenderInitData[i++]); 
	GetDevice()->SetTextureStageState(1, D3DTSS_COLOROP,			m_vecRenderInitData[i++]); 
	GetDevice()->SetTextureStageState(1, D3DTSS_ALPHAARG1,			m_vecRenderInitData[i++]);	 
	GetDevice()->SetTextureStageState(1, D3DTSS_ALPHAARG2,			m_vecRenderInitData[i++]);
	//Stage3
	GetDevice()->SetSamplerState(2, D3DSAMP_MINFILTER,				m_vecRenderInitData[i++]); 
	GetDevice()->SetSamplerState(2, D3DSAMP_MAGFILTER,				m_vecRenderInitData[i++]); 
				 																		
	GetDevice()->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX,		m_vecRenderInitData[i++]); 
	GetDevice()->SetTextureStageState(2, D3DTSS_COLOROP,			m_vecRenderInitData[i++]); 
	GetDevice()->SetTextureStageState(2, D3DTSS_ALPHAARG1,			m_vecRenderInitData[i++]);
	GetDevice()->SetTextureStageState(2, D3DTSS_ALPHAARG2,			m_vecRenderInitData[i++]);


	GetDevice()->SetRenderState(D3DRS_BLENDOP,				m_vecRenderInitData[i++]);
	GetDevice()->SetRenderState(D3DRS_SRCBLEND,				m_vecRenderInitData[i++]);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND,			m_vecRenderInitData[i++]);

	SetRenderState(D3DRS_POINTSCALEENABLE,					m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSIZE,							m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSCALE_A,						m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSCALE_B,						m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSCALE_C,						m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSPRITEENABLE,					m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSIZE_MIN,						m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_POINTSIZE_MAX,						m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_LIGHTING,							m_vecRenderInitData[i++]);
	SetRenderState(D3DRS_ZWRITEENABLE,						true);
	SetRenderState(D3DRS_ALPHABLENDENABLE,					false);

}

void CEzealQ_Particle::InitRenderState()
{
	DWORD pWord;

	GetDevice()->GetSamplerState(0, D3DSAMP_MINFILTER,			&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetSamplerState(0, D3DSAMP_MAGFILTER,			&pWord); m_vecRenderInitData.push_back(pWord);
				 												
	GetDevice()->GetTextureStageState(0, D3DTSS_TEXCOORDINDEX,	&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_COLOROP,		&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_ALPHAARG1,		&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(0, D3DTSS_ALPHAARG2,		&pWord); m_vecRenderInitData.push_back(pWord);
				 												
	//Stage2	 												
	GetDevice()->GetSamplerState(1, D3DSAMP_MINFILTER,			&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetSamplerState(1, D3DSAMP_MAGFILTER,			&pWord); m_vecRenderInitData.push_back(pWord);
				 												
	GetDevice()->GetTextureStageState(1, D3DTSS_TEXCOORDINDEX,	&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(1, D3DTSS_COLOROP,		&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(1, D3DTSS_ALPHAARG1,		&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(1, D3DTSS_ALPHAARG2,		&pWord); m_vecRenderInitData.push_back(pWord);

	//Stage3											
	GetDevice()->GetSamplerState(2, D3DSAMP_MINFILTER,			&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetSamplerState(2, D3DSAMP_MAGFILTER,			&pWord); m_vecRenderInitData.push_back(pWord);
				 												
	GetDevice()->GetTextureStageState(2, D3DTSS_TEXCOORDINDEX,	&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(2, D3DTSS_COLOROP,		&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(2, D3DTSS_ALPHAARG1,		&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetTextureStageState(2, D3DTSS_ALPHAARG2,		&pWord); m_vecRenderInitData.push_back(pWord);

	GetDevice()->GetRenderState(D3DRS_BLENDOP,					&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_SRCBLEND,					&pWord); m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_DESTBLEND,				&pWord); m_vecRenderInitData.push_back(pWord);


	GetDevice()->GetRenderState(D3DRS_POINTSCALEENABLE,			&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSIZE,				&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSCALE_A,				&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSCALE_B,				&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSCALE_C,				&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSPRITEENABLE,		&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSIZE_MIN,			&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_POINTSIZE_MAX,			&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_LIGHTING,					&pWord);m_vecRenderInitData.push_back(pWord);
	GetDevice()->GetRenderState(D3DRS_ZWRITEENABLE,				&pWord);m_vecRenderInitData.push_back(pWord);

}


bool CEzealQ_Particle::AddTail()
{
	D3DXVECTOR3 vDirection = m_VerTexInfo.p - m_Info.vPos;
	float fDistance =D3DXVec3Length(&vDirection);

	if (fDistance > m_fMaxDistance)
	{
		if (m_vecVertexParticle.empty()) {
			return false;
		}
		m_vecVertexParticle.erase(m_vecVertexParticle.begin());
		m_fSize -= 0.1f;	
	}
	else 
	{
		int size = m_vecVertexParticle.size();
		m_fLength -= 0.1f;
		for (int i = 0; i < size; i++)
		{
			m_vecVertexParticle[i].p += (m_Info.vLook * g_fDeltaTime* (m_fSpeed));
		}
		m_VerTexInfo.p = m_vecVertexParticle[size -1].p + (m_Info.vLook * g_fDeltaTime* (m_fSpeed));
		m_Info.vPos += (m_Info.vLook * g_fDeltaTime*m_fSpeed);
		if (m_pColider != NULL)	m_pColider->Update(m_VerTexInfo.p);
		m_vecVertexParticle.push_back(m_VerTexInfo);
	}
	if (m_vecVertexParticle.empty()) {
		return false;
	}
	return true;
}


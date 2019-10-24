#include "BaseInclude.h"
#include "Ezeal_Q.h"


CEzeal_Q::CEzeal_Q()
	:m_fHeight(4.0),m_fWidth(0.1),m_ParticleExp(0.5f), m_fDistance(1.0f),m_vStartPosition(0,0,0), m_fSpeed(1.0f)
{
	m_fAngle[ANGLE_X] = 0;		m_fAngle[ANGLE_Y] = 0;		m_fAngle[ANGLE_Z] = 0;
}


CEzeal_Q::~CEzeal_Q()
{
	Release();
}

CEzeal_Q::CEzeal_Q(INFO & tInfo)
	: m_fHeight(4.0), m_fWidth(0.1), m_ParticleExp(0.5f), m_fDistance(1.0f),CSkill(tInfo),m_fSpeed(1.0f)
{
	m_fAngle[ANGLE_X] = 0;		m_fAngle[ANGLE_Y] = 0;		m_fAngle[ANGLE_Z] = 0;
	m_vStartPosition = m_Info.vPos;
	

}

HRESULT CEzeal_Q::LoadAsset(const TCHAR * pFileName)
{
	gTextureMappingShader = LoadShader(pFileName);
	if (!gTextureMappingShader) return E_FAIL;

	gpEarthDM = GetTexture(L"Effect", L"Arrow2")->pTexture;
	gpEarthDM2 = GetTexture(L"Effect", L"Arrow")->pTexture;

	if ((!gpEarthDM) || (!gpEarthDM2))
	{
		return E_FAIL;
	}
	gModel = LoadModel(L"./Resource/Shader/Quad_Array.x");
	if (gModel == NULL)		
		return E_FAIL;
	return S_OK;
}
HRESULT CEzeal_Q::Initialize()
{

	HRESULT hr = LoadAsset(L"./Resource/Shader/test3.fx");	

	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.0f);
	m_Info.vDir = D3DXVECTOR3(1.f, 0.f, 1.f);
	m_Info.vPos = D3DXVECTOR3(-10.0f, 18.0f, -10.0f);

	m_pOriVtx = new VTXTEX[4];
	m_pConVtx = new VTXTEX[4];
	m_fAngle[ANGLE_X] = 0;		m_fAngle[ANGLE_Y] = 0;		m_fAngle[ANGLE_Z] = 0;
	WorldSetting();
	return S_OK;
}
void CEzeal_Q::WorldSetting()
{
	D3DXMATRIX matRotX, matRotY, matRotZ, matTrans, matScale;
	D3DXMatrixRotationX(&matRotX, m_fAngle[ANGLE_X]);
	D3DXMatrixRotationY(&matRotY, m_fAngle[ANGLE_Y]);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle[ANGLE_Z]);
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);
	m_Info.matWorld = matScale*matRotX*matRotY*matRotZ*matTrans;	
}

void CEzeal_Q::RenderSetting()
{
	SetRenderState(D3DRS_LIGHTING, false);
	if (gTextureMappingShader)
	{
		D3DXMATRIX matProj, matWorld, matView;
		D3DXVECTOR4 vDirection = { m_Info.vDir.x,m_Info.vDir.y,m_Info.vDir.z,1 };
	
		
		GetTransform(D3DTS_PROJECTION, &matProj);
		GetTransform(D3DTS_VIEW, &matView);
		D3DXVec4Normalize(&vDirection, &vDirection);
		vDirection.w = 1.0f;

		HRESULT hr;
		float fTime = GetTime() / 30.0f;		
		//텍스쳐 설정
		hr = gTextureMappingShader->SetTexture("Flame_Tex", gpEarthDM);
		hr = gTextureMappingShader->SetTexture("Texture1_Tex", gpEarthDM2);

		//Proj,World,View 설정
		hr = gTextureMappingShader->SetMatrix("matProjection", &matProj);
		hr = gTextureMappingShader->SetMatrix("matWorld", &m_Info.matWorld);
		hr = gTextureMappingShader->SetMatrix("matView", &matView);

		//꼬리선과 넓이 조정
		hr = gTextureMappingShader->SetFloat("fWidth", m_fWidth);
		hr = gTextureMappingShader->SetFloat("fHeight",m_fHeight);

		//광의 세기
		hr = gTextureMappingShader->SetFloat("particleExp", m_ParticleExp);
		//방향
		hr = gTextureMappingShader->SetVector("vDirection", &vDirection);
	}
}



void CEzeal_Q::Render_End()
{
	SetRenderState(D3DRS_ZWRITEENABLE, true);
	SetRenderState(D3DRS_SRCBLEND,false);
	SetRenderState(D3DRS_DESTBLEND, false);
	SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}




void CEzeal_Q::Progress()
{
	D3DXVECTOR3 vDirection =  m_vStartPosition- m_Info.vPos;
	float fDistance = D3DXVec3Length(&vDirection);

	D3DXVec3Normalize(&vDirection, &vDirection);

	m_Info.vPos += vDirection * m_fSpeed*GetTime();
	if (fDistance > m_fDistance)
	{

	}

}

void CEzeal_Q::Render()
{
	RenderSetting();
	UINT numPasses = 0;

	if (gTextureMappingShader) {
		gTextureMappingShader->Begin(&numPasses, NULL);
		for (UINT i = 0; i < numPasses; ++i)
		{
			gTextureMappingShader->BeginPass(i);
			
			if (gModel)	gModel->DrawSubset(0);

			gTextureMappingShader->EndPass();
		}
		gTextureMappingShader->End();
	}
	Render_End();
}

void CEzeal_Q::Release()
{
	CShader::Release();
}

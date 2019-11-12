#include "BaseInclude.h"
#include "ChaosTurret.h"
#include "TurretGauge.h"

CChaosTurret::CChaosTurret()
{
}


CChaosTurret::~CChaosTurret()
{
}

CChaosTurret::CChaosTurret(D3DXVECTOR3 pos, TCHAR * TurretName, float Rotation_Radian)
	:m_name(TurretName), m_RotRadian(Rotation_Radian)
{
	m_fSize = 1.0f;

	fill(&m_fAngle[0], &m_fAngle[ANGLE_END], 0.f);
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vPos = pos;
	m_fHeight = 0.0f;
}

HRESULT CChaosTurret::Initialize()
{
	CloneMesh(GetDevice(), m_name, &m_pAnimationCtrl);

	if (!m_pAnimationCtrl) return S_FALSE;

	UpdateWorldMatrix(m_RotRadian);
	m_pAnimationCtrl->SetAnimationSet(NULL);

	m_pGauge = new CTurretGauge;
	m_pGauge->SetInfo(m_Info);
	m_pGauge->SetParentWorld(m_Info.matWorld);
	m_pGauge->Initialize();
	return S_OK;
}

void CChaosTurret::Progress()
{
	m_pAnimationCtrl->FrameMove(m_name, g_fDeltaTime);

	m_pGauge->Progress();
}

void CChaosTurret::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), m_name);
	m_pGauge->Render();
}

void CChaosTurret::Release()
{
	SAFE_RELEASE(m_pAnimationCtrl);
}

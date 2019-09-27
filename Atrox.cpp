#include "BaseInclude.h"
#include "Atrox.h"
#include"PipeLine.h"
CAtrox::CAtrox()
{
}


CAtrox::~CAtrox()
{
}

void CAtrox::KeyCheck()
{
	if (CheckPushKey(DIK_UP))
	{
		m_Info.vPos += m_Info.vDir * 0.007f;
	}

	if (CheckPushKey(DIK_DOWN))
	{
		m_Info.vPos -= m_Info.vDir * 0.007f;
	}

	// Y축회전
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fAngle[ANGLE_Y] += 0.001f;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_fAngle[ANGLE_Y] -= 0.001f;
	}
}

void CAtrox::MouseCheck()
{
}

void CAtrox::SetCameraPos()
{

}

void CAtrox::SetContantTable()
{

	D3DXMATRIX		matView, matProj;
	GetTransform(D3DTS_VIEW, &matView);
	GetTransform(D3DTS_PROJECTION, &matProj);
}

void CAtrox::WorldSetting()
{
	D3DXMATRIX matRotX, matRotY, matRotZ, matTrans, matScale;
	D3DXMatrixRotationX(&matRotX, m_fAngle[ANGLE_X]);
	D3DXMatrixRotationY(&matRotY, m_fAngle[ANGLE_Y]);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle[ANGLE_Z]);
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	m_Info.matWorld = matScale*matRotX*matRotY*matRotZ*matTrans;
	CPipeLine::MyVec3TransformNormal(&m_Info.vDir, &m_Info.vLook, &m_Info.matWorld);
}


HRESULT CAtrox::Initialize()
{
	m_SortID = SORTID_LAST;
	m_Info.vLook = D3DXVECTOR3(0.f, 0.f, 1.0f);
	m_Info.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Info.vPos = D3DXVECTOR3(-10.f, 1.5f, -10.f);

	m_fCamDistance = 10.f;

	m_pOriVtx = new VTXTEX[4];
	m_pConVtx = new VTXTEX[4];


	D3DXMatrixIdentity(&m_Info.matWorld);
	CloneMesh(GetDevice(), L"Atrax", &m_pAnimationCtrl);

	m_vMin = *(GetMin(BOUNDTYPE_CUBE));
	m_vMax = *(GetMax(BOUNDTYPE_CUBE));
	return S_OK;
}

void CAtrox::Progress()
{
	WorldSetting();
	KeyCheck();
	SetCameraPos();	
}

void CAtrox::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	//몇개의 애니메이션이 돌지에 대해 설정한다.
	m_pAnimationCtrl->SetAnimationSet(9);
	m_pAnimationCtrl->FrameMove(L"Atrax", GetTime());
	Mesh_Render(GetDevice(), L"Atrax");
}

void CAtrox::Release()
{
	
}

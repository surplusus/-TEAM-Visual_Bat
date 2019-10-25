#include "BaseInclude.h"
#include "Minion.h"
#include "ObjMgr.h"
#include "Factory.h"

CMinion::CMinion()
{
	m_sName = L"None";
}

CMinion::~CMinion()
{
}

bool CMinion::SetUp(string sName, string sFolderPath, string sFilePath)
{
	basic_string<TCHAR> szFolder(sFolderPath.begin(), sFolderPath.end());
	basic_string<TCHAR> szFile(sFilePath.begin(), sFilePath.end());
	//basic_string<TCHAR> szName(sName.begin(), sName.end());
	m_sName = basic_string<TCHAR>(sName.begin(), sName.end());
	
	if (FAILED(AddMesh(GetDevice(), szFolder.c_str(), szFile.c_str(), m_sName.c_str(), MESHTYPE_DYNAMIC))) {
		ERR_MSG(g_hWnd, L"Minion Load Failed");
		return false;
	}
	return true;
}

void CMinion::UpdateWorldMatrix()
{
	D3DXMATRIX matScale, matRot, matTrans;
	D3DXMatrixScaling(&matScale, m_fSize, m_fSize, m_fSize);
	D3DXQUATERNION quat; D3DXQuaternionIdentity(&quat);
	D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.f, 1.f, 0.f), m_fAngle[ANGLE_Y]);
	D3DXMatrixRotationQuaternion(&matRot, &quat);
	D3DXVec3TransformNormal(&m_Info.vDir, &D3DXVECTOR3(0.f, 0.f, -1.f), &matRot);
	D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
	m_Info.matWorld = matScale * matRot * matTrans;
}

bool CMinion::SetUpPickingShere(const float r, const D3DXVECTOR3 v)
{
	m_SphereForPick.fRadius = r;
	m_SphereForPick.vCenter.x = v.x;
	m_SphereForPick.vCenter.y = v.y;
	m_SphereForPick.vCenter.z = v.z;
	// 관리자에게 등록??????
	m_SphereForPick = SPHERE(r, v);
	HRESULT result = D3DXCreateSphere(GET_DEVICE, r, 10, 10, &m_pMeshSphere, NULL);
	return false;
}

bool CMinion::Render_PickingShere()
{
	if (m_pMeshSphere != NULL) {
		m_pMeshSphere->DrawSubset(0);
		return true;
	}
	return false;
}

const TCHAR * CMinion::GetName()
{
	return m_sName.c_str();
}

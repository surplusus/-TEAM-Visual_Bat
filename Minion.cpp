#include "BaseInclude.h"
#include "Minion.h"
#include "ObjMgr.h"
#include "Factory.h"
#include <random>

Minion::Minion()
{
}


Minion::Minion(string name, string filePath)
{
	basic_string<TCHAR> convertedFile(filePath.begin(), filePath.end());
	basic_string<TCHAR> convertedName(name.begin(), name.end());
	m_sName = &convertedName[0];

	if (SUCCEEDED(AddMesh(GetDevice(), L"./Resource/Mesh/Dynamic/Minion/"
			, convertedFile.c_str(), L"Minion", MESHTYPE_DYNAMIC)))
		GET_SINGLE(CObjMgr)->AddObject(convertedName.c_str(), CFactory<CObj, Minion>::CreateObject());
	else
		ERR_MSG(g_hWnd, L"Minion Load Failed");
}

Minion::~Minion()
{
}

HRESULT Minion::Initialize()
{
	random_device random_device;
	uniform_int_distribution<int> dist(0, 10);
	num = dist(random_device);
	return S_OK;
}

void Minion::Progress()
{
	m_fAngle[ANGLE_Y] = D3DXToRadian(60);
	m_Info.vPos += D3DXVECTOR3(0.f, 0.f, 0.01f);
	{
		D3DXMATRIX matScale, matRot, matTrans;
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXQUATERNION quat; D3DXQuaternionIdentity(&quat);
		D3DXQuaternionRotationAxis(&quat, &D3DXVECTOR3(0.f, 1.f, 0.f), m_fAngle[ANGLE_Y]);
		D3DXMatrixRotationQuaternion(&matRot, &quat);
		D3DXVec3TransformNormal(&m_Info.vDir, &D3DXVECTOR3(0.f, 0.f, -1.f), &matRot);
		D3DXMatrixTranslation(&matTrans, m_Info.vPos.x, m_Info.vPos.y, m_Info.vPos.z);
		m_Info.matWorld = matScale * matRot * matTrans;
	}
}

void Minion::Render()
{
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), m_sName);
}

void Minion::Release()
{
}

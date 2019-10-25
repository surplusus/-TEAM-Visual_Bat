#include "BaseInclude.h"
#include "MeleeMinion.h"
#include "ObjMgr.h"
#include "Factory.h"
#include <random>

CMeleeMinion::CMeleeMinion()
	: Minion(this)
{
}


CMeleeMinion::~CMeleeMinion()
{
}

HRESULT CMeleeMinion::Initialize()
{
	if (m_sName == "None")
	{
		Minion::SetUp("Minion", "./Resource/Test/", "Minion_Melee_Blue.x")
	}
	//random_device random_device;
	//uniform_int_distribution<int> dist(0, 10);
	//num = dist(random_device);
	return S_OK;
}

void CMeleeMinion::Progress()
{
}

void CMeleeMinion::Render()
{
	basic_string<TCHAR> szName(m_sName.begin(), m_sName.end());
	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	Mesh_Render(GetDevice(), szName.c_str());
}

void CMeleeMinion::Release()
{
}

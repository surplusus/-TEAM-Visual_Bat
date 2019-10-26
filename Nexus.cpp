#include "BaseInclude.h"
#include "Nexus.h"
#include "Ray.h"
#include "ObjMgr.h"
#include "HeightMap.h"
#include "SoundManager.h"

CNexus::CNexus()
{
}


CNexus::~CNexus()
{
	Release();
}

HRESULT CNexus::Initialize()
{
	CloneMesh(GetDevice(), L"Zealot", &m_pAnimationCtrl);
	if (!m_pAnimationCtrl) return S_FALSE;

	

	return E_NOTIMPL;
}

void CNexus::Progress()
{
}

void CNexus::Render()
{
}

void CNexus::Release()
{
}


void CNexus::SetHeightMap(CHeightMap * pHeightMap)
{
}

float CNexus::lerp(float p1, float p2, float d)
{
	return 0.0f;
}

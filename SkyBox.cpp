#include "BaseInclude.h"
#include "SkyBox.h"
#include "SystemFunc.h"
#include "ResourceFunc.h"

#include "ObjMgr.h"

CSkyBox::CSkyBox(void)
{
}

CSkyBox::~CSkyBox(void)
{
}

HRESULT CSkyBox::Initialize(void)
{
	m_SortID = SORTID_FIRST;

	return S_OK;
}
void CSkyBox::Progress(void)
{
	D3DXMATRIX			matScale;
	D3DXMATRIX			matTrans;

	const INFO* pPlayerInfo = GET_SINGLE(CObjMgr)->GetInfo(L"SkyBox");

	if (pPlayerInfo == NULL)
		return;

	D3DXMatrixTranslation(&matTrans, pPlayerInfo->vPos.x, pPlayerInfo->vPos.y, pPlayerInfo->vPos.z);

	D3DXMatrixScaling(&matScale, 100.f, 100.f, 100.f);

	m_Info.matWorld = matScale * matTrans;
}

void CSkyBox::PreRender(void)
{
	SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	SetRenderState(D3DRS_ZENABLE, FALSE);
	SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void CSkyBox::Render(void)
{
	const TEXINFO* pTexInfo = GetTexture(L"SkyBox", L"Cube", 2);
	if (pTexInfo == NULL)
		return;

	SetTransform(D3DTS_WORLD, &m_Info.matWorld);
	SetCubeTexture(0, pTexInfo->pCubeTexture);

	PreRender();

	Buffer_Render(GetDevice(), L"CubeTexture");

	EndRender();
}

void CSkyBox::EndRender(void)
{
	SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	SetRenderState(D3DRS_ZENABLE, TRUE);
	SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
void CSkyBox::Release(void)
{

}
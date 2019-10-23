#include "BaseInclude.h"
#include "Shader.h"
#include"CameraMgr.h"
CShader::CShader()
{
}


CShader::~CShader()
{
	Release();
}

HRESULT CShader::LoadAsset(const TCHAR* pFileName)
{

	gTextureMappingShader = LoadShader(pFileName);
	if (!gTextureMappingShader) return E_FAIL;

	gpEarthDM = GetTexture(L"Effect",L"Arrow2")->pTexture;
	gpEarthDM2 = GetTexture(L"Effect", L"Arrow")->pTexture;
	gModel = LoadModel(L"./Resource/Shader/Quad_Array.x");
	
	if ((!gpEarthDM) || (!gpEarthDM2)) 
	{
		return E_FAIL;
	}
	return S_OK;
}

void CShader::Release()
{
	if (gTextureMappingShader) {
		gTextureMappingShader->Release();
		gTextureMappingShader = NULL;
	}
	if(gpEarthDM)
	{
		gpEarthDM->Release();
		gpEarthDM = NULL;
	}
}

LPD3DXEFFECT CShader::LoadShader(const TCHAR * pFileName)
{
	LPD3DXEFFECT ret = NULL;
	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;
#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFile(GetDevice(), pFileName, NULL, NULL, dwShaderFlags, NULL, &ret, &pError);
	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();
		if (ack)
		{
			char* str = new char[size];
			sprintf(str, (const char*)ack, size);
			OutputDebugStringA(str);
			delete[] str;
		}
	}
	return ret;
}

void CShader::RenderScene()
{
	SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	UINT numPasses = 0;
	SetRenderState(D3DRS_LIGHTING, false);
	if (gTextureMappingShader)
	{
		D3DXMATRIX matProj, matWorld, matView;
		D3DXMATRIX matScale, matTrans;
		D3DXVECTOR3 vScale,vPos;
		D3DXMATRIX matWorld2;
		D3DXVECTOR4 vDirection = {1,0,1,1};
		vScale = { 1.0,1.0,1.0f };
		vPos = { 1.0,18,0 };
		D3DXMatrixIdentity(&matTrans);
		D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, vPos.z);
		D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);

		GetTransform(D3DTS_PROJECTION, &matProj);
		GetTransform(D3DTS_VIEW, &matView);
		
		matWorld2 = matScale * matTrans;

		D3DXVec4Normalize(&vDirection, &vDirection);
		vDirection.w = 1.0f;
		HRESULT hr;
		
		float fTime = GetTime()/30.0f;
		float fWidth = 0.1;

		float fHeight = 4.0f;
		float Exp = 0.5;
		
		//텍스쳐 설정
		hr = gTextureMappingShader->SetTexture("Flame_Tex"    , gpEarthDM);
		hr = gTextureMappingShader->SetTexture("Texture1_Tex" , gpEarthDM2);

		//Proj,World,View 설정
		hr = gTextureMappingShader->SetMatrix( "matProjection", &matProj);
		hr = gTextureMappingShader->SetMatrix( "matWorld"     , &matWorld2);
		hr = gTextureMappingShader->SetMatrix( "matView"	  , &matView);

		//꼬리선과 넓이 조정
		hr = gTextureMappingShader->SetFloat(  "fWidth"		  , fWidth);
		hr = gTextureMappingShader->SetFloat(  "fHeight"	  , fHeight);

		//광의 세기
		hr = gTextureMappingShader->SetFloat(  "particleExp"  , Exp);	
		//방향
		hr = gTextureMappingShader->SetVector( "vDirection"   , &vDirection);


		gTextureMappingShader->Begin(&numPasses, NULL);

		for (UINT i = 0; i < numPasses; ++i)
		{
			gTextureMappingShader->BeginPass(i);
			if (gModel)	gModel->DrawSubset(0);

			gTextureMappingShader->EndPass();
		}
		gTextureMappingShader->End();
		//SetTransform(D3DTS_WORLD, &matWorld2);
		//if (gModel)	gModel->DrawSubset(0);
	}
	

}

	


LPD3DXMESH CShader::LoadModel(const TCHAR *filename)
{
	LPD3DXMESH ret = NULL;
	if (FAILED(D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM, GetDevice(),
		NULL, NULL, NULL, NULL, &ret)))
	{
		OutputDebugString(L"모델 로딩 실패: ");
		OutputDebugString(filename);
		OutputDebugString(L"\n");
	};

	return ret;
}

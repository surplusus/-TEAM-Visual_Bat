#include "BaseInclude.h"
#include "Shader.h"


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
//	D3DXCreateBox(GetDevice(), 10, 10, 10, &gModel, NULL);
	if ((!gpEarthDM) || (!gpEarthDM2)) 
	{
		return E_FAIL;
	}
	D3DXMATRIX matProj, matWorld, matView;
	GetTransform(D3DTS_PROJECTION, &matProj);
	GetTransform(D3DTS_VIEW, &matView);
	GetTransform(D3DTS_WORLD, &matWorld);

	HRESULT hr =gTextureMappingShader->SetTexture("Flame_Tex", gpEarthDM);
	hr		  = gTextureMappingShader->SetTexture("Texture1_Tex", gpEarthDM2);

	hr =gTextureMappingShader->SetMatrix("matProjection", &matProj);
	hr= gTextureMappingShader->SetMatrix("matWorld",&matWorld);
	hr =gTextureMappingShader->SetMatrix("matView",&matView);

	hr =gTextureMappingShader->SetFloat("time_0_X", 10.0f);

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
	D3DXMATRIXA16 matView;
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -200.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);

	UINT numPasses = 0;
	SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	SetTransform(D3DTS_WORLD, &matWorld);
	
	gTextureMappingShader->Begin(&numPasses, NULL);
	{
		for (UINT i = 0; i < numPasses; ++i)
		{
			gTextureMappingShader->BeginPass(i);
			{
				
				gModel->DrawSubset(0);
			}
			gTextureMappingShader->EndPass();
		}
	}
	gTextureMappingShader->End();
	
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

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

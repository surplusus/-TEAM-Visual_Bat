#include "BaseInclude.h"
#include "CubeTexture.h"


CCubeTexture::CCubeTexture()
{
}


CCubeTexture::~CCubeTexture()
{
}

HRESULT CCubeTexture::InsertTexture(LPDIRECT3DDEVICE9 pDevice, const TCHAR * pFileName, const TCHAR * pStateKey, const int & iCnt, TERRIAN_INSERTTYPE)
{
	map<const TCHAR*, vector<TEXINFO*>>::iterator iter = m_MapTexture.find(pStateKey);

	if (iter == m_MapTexture.end())
	{
		vector<TEXINFO*> vecTexture;
		vecTexture.reserve(iCnt);

		for (int i = 0; i < iCnt; ++i)
		{
			TEXINFO* pTexInfo = new TEXINFO;
		
			TCHAR    szPath[128] = L"";
			
			wsprintf(szPath, pFileName, i);

			//텍스쳐 정보
			if (FAILED(D3DXGetImageInfoFromFile(szPath, &(pTexInfo)->TexInfo)))
			{
				return E_FAIL;
			}
			if (FAILED(D3DXCreateCubeTextureFromFile(pDevice, szPath, &(pTexInfo->pCubeTexture))))
			{
				return E_FAIL;
			}
			vecTexture.push_back(pTexInfo);
		}
		m_MapTexture.insert(map<const TCHAR*, vector<TEXINFO*>>::value_type(pStateKey, vecTexture));
	}
	else return E_FAIL;
	return S_OK;
}

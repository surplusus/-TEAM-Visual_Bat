#include "BaseInclude.h"
#include "NormalTexture.h"


CNormalTexture::CNormalTexture()
{
}


CNormalTexture::~CNormalTexture()
{
}

HRESULT CNormalTexture::InsertTexture(LPDIRECT3DDEVICE9 pDevice, const TCHAR * pFileName, const TCHAR * pStateKey, const int & iCnt, TERRIAN_INSERTTYPE Type)
{
	map<const TCHAR*, vector<TEXINFO*>>::iterator iter = m_MapTexture.find(pStateKey);
	if (iter == m_MapTexture.end())
	{
		vector<TEXINFO*>  vecTexture;
		vecTexture.reserve(iCnt);
		for (int i = 0; i < iCnt; ++i)
		{
			TEXINFO* pTexInfo = new TEXINFO;
			TCHAR szPath[128] = L"";
			if (Type == INSERTTYPE_ENGLISH)
			{
				wsprintf(szPath, pFileName, 'a'+i);
			}
			else	wsprintf(szPath, pFileName, i);

			//텍스쳐의 정보
			if (FAILED(D3DXGetImageInfoFromFile(szPath, &(pTexInfo->TexInfo))))
				return E_FAIL;
				if (FAILED(D3DXCreateTextureFromFile(pDevice, szPath, &(pTexInfo->pTexture))))
					return E_FAIL;
				vecTexture.push_back(pTexInfo);
		}
		m_MapTexture.insert(map<const TCHAR*, vector<TEXINFO*>>::value_type(pStateKey, vecTexture));
	}
	else return E_FAIL;
	
	return S_OK;
}

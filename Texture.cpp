#include "BaseInclude.h"
#include "Texture.h"


CTexture::CTexture()
{
}


CTexture::~CTexture()
{
	Release();
}
//키값으로 텍스트의 정보를가져온다.
const TEXINFO * CTexture::GetTexture(const TCHAR * pStateKey, const int & iCnt)
{
	map<const TCHAR*, vector<TEXINFO*>>::iterator iter = m_MapTexture.find(pStateKey);
	if (iter == m_MapTexture.end()) return NULL;
	TEXINFO* pTex = iter->second[iCnt];
	return iter->second[iCnt];
}

void CTexture::Release()
{
	for (map<const TCHAR*, vector<TEXINFO*>>::iterator iter = m_MapTexture.begin();
		iter != m_MapTexture.end(); ++iter)
	{
		for (unsigned int i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->pTexture)
			{
				iter->second[i]->pTexture->Release();
				iter->second[i]->pTexture = NULL;
			}
			if (iter->second[i])
			{
				delete iter->second[i];
				iter->second[i] = NULL;
			}
		}
		iter->second.clear();
	}
	m_MapTexture.clear();

}

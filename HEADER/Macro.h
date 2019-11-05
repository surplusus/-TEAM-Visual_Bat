#pragma once
//��ũ���Լ�

//TEMPLATE�� ���ǵ� �̱��� ���Ǹ� ���� ��ũ���Լ�
#define DECLARE_SINGLETON(type)public:\
		static type** GetInstance()\
		{\
			static type* pInstance = new type;\
			if(pInstance == nullptr)\
				pInstance = new type;\
			return &pInstance;\
		}\
		static void DestroyInstance(void)\
		{\
			type** ppInstance = GetInstance();\
			if(*ppInstance != nullptr)\
			{\
				delete *ppInstance;\
				*ppInstance = nullptr;\
			}\
		}
#define SAFE_DELETE(p) {if(p) delete p;}
#define SAFE_RELEASE(p) {if (p) p->Release(); p = nullptr;}
#define GET_SINGLE(type) (*type::GetInstance())
#define ERR_MSG(hWnd, sz) MessageBox(hWnd, sz, L"system err", MB_OK)//������ ���� �޽����ڽ� ��� ��ũ��
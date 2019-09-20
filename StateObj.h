#pragma once
class CStateObj
{
public:
	CStateObj();
	~CStateObj();
public:
	virtual HRESULT Initalize() =0;
	virtual void Progress()  =0;
	virtual void Render()    =0;
	virtual void Release()   =0;
};


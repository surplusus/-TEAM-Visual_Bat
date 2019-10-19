#pragma once
class CAlgorithm
{
public:
	CAlgorithm();
	virtual ~CAlgorithm();
public:
	virtual void SubscribeEvent() = 0;
};



CAlgorithm::CAlgorithm()
{
}


CAlgorithm::~CAlgorithm()
{
}

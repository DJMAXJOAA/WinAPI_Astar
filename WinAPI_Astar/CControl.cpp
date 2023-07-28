#include "pch.h"
#include "CControl.h"
#include "CNode.h"

bool cmp::operator() (CNode* a, CNode* b)
{
	if (a->getFValue() == b->getFValue())
	{
		return (a->getHValue() > b->getHValue());
	}
	else
	{
		return (a->getFValue() > b->getFValue());
	}
}

void CControl::Init()
{
}

void CControl::Update()
{
}

CControl::CControl()
	: vecControlList(YSIZE, vector<CNode*>(0))
{
	
}

CControl::~CControl()
{
}

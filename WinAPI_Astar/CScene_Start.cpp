#include "pch.h"
#include "CScene_Start.h"

#include "CNode.h"

#include "CCore.h"
#include "CControl.h"

void CScene_Start::Enter()
{
	POINT ptResolution = CCore::GetInstance()->GetResolution();
	
	float xScale = (float)ptResolution.x / XSIZE;
	float yScale = (float)ptResolution.y / YSIZE;
	Vec2 Scale(xScale, yScale);

	for (int i = 0; i < YSIZE; i++)
	{
		for (int j = 0; j < XSIZE; j++)
		{
			Vec2 temp(j * xScale, i * yScale);
			CNode* add = new CNode(temp, Scale);
			add->setIndex(j, i);
			CControl::GetInstance()->AddNodeList(add, i);
			AddObject(add, GROUP_TYPE::DEFAULT);
		}
	}
}

void CScene_Start::Exit()
{

}

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

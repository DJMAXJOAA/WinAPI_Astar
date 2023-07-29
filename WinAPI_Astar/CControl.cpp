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

void CControl::AStar()
{
	POINT ptrIndex = ptrCurrent->getIndex();
	int minX = ptrIndex.x - 1, maxX = ptrIndex.x + 1;
	int minY = ptrIndex.y - 1, maxY = ptrIndex.y + 1;

	if (ptrIndex.x == 0)
		minX = 0;
	if (ptrIndex.x == XSIZE - 1)
		maxX = XSIZE - 1;
	if (ptrIndex.y == 0)
		minY = 0;
	if (ptrIndex.y == YSIZE - 1)
		maxY = YSIZE - 1;

	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			if (ptrIndex.x == x && ptrIndex.y == y
			 ||	vecControlList[y][x]->getState() == (int)NODE_STATE::BLOCK
			 || vecControlList[y][x]->getState() == (int)NODE_STATE::ARRIVAL)
			{
				continue;
			}

			if (vecControlList[y][x]->getState() == (int)NODE_STATE::DEPARTURE)
			{
				ptrCurrent = ptrDeparture;
				printf("도착!\n");
				return;
			}


			int GValue = CalculateGValue(vecControlList[y][x]);
			int HValue = CalculateHValue(vecControlList[y][x]);
			int FValue = GValue + HValue;
			// 1. 아직 계산 안했으면 바로 등록
			if (vecControlList[y][x]->getState() == (int)NODE_STATE::NONE)
			{
				vecControlList[y][x]->setState(NODE_STATE::NO_VISIT);
				vecControlList[y][x]->setGValue(GValue);
				vecControlList[y][x]->setHValue(HValue);
				vecControlList[y][x]->setFValue();
				ptrCurrent->AddNeighbor(vecControlList[y][x]);
				queueNode.push(vecControlList[y][x]);

				int n = vecControlList[y][x]->getFValue();
				printf("%d\n", n);
			}

			// 2. 계산 했으면 f값 비교해서 등록
			else if (FValue < vecControlList[y][x]->getFValue())
			{
				vecControlList[y][x]->setGValue(GValue);
				vecControlList[y][x]->setHValue(HValue);
				vecControlList[y][x]->setFValue();
				ptrCurrent->AddNeighbor(vecControlList[y][x]);
				queueNode.push(vecControlList[y][x]);

				int n = vecControlList[y][x]->getFValue();
				printf("%d\n", n);
			}
		}
	}

	CNode* temp = nullptr;
	int min = 999999;
	for (int i = 0; i < ptrCurrent->getNeighbor().size(); i++)
	{
		if (ptrCurrent->getNeighbor()[i]->getFValue() < min)
		{
			min = ptrCurrent->getNeighbor()[i]->getFValue();
			temp = ptrCurrent->getNeighbor()[i];
		}
	}
	if (temp != nullptr)
	{
		ptrCurrent = temp;
		ptrCurrent->setState(NODE_STATE::VISIT);
		return;
	}
}

void CControl::Update()
{
	if (iState < START)
		return;

	while (queueNode.top()->getFValue() > ptrCurrent->getFValue())
	{
		Sleep(1000);

		AStar();

		if (ptrCurrent == ptrDeparture)
		{
			iState = ARRIVAL;
			return;
		}
	}

	ptrCurrent = queueNode.top();
	queueNode.pop();
	printf("%d\n", ptrCurrent->getFValue());

}

void CControl::SetNodeActive(POINT cur_point, int state)
{
	if (iState > DEPARTURE)
		return;

	for (int x = 0; x < vecControlList[0].size(); x++)
	{
		for (int y = 0; y < vecControlList.size(); y++)
		{
			Vec2 NodePos = vecControlList[y][x]->GetPos();
			Vec2 NodeScale = vecControlList[y][x]->GetScale();
			if (NodePos.x < cur_point.x && cur_point.x < NodePos.x + NodeScale.x
			 && NodePos.y < cur_point.y && cur_point.y < NodePos.y + NodeScale.y)
			{
				vecControlList[y][x]->setState((NODE_STATE)state);
				if (state == (int)NODE_STATE::ARRIVAL)
				{
					ptrArrival = vecControlList[y][x];
				}
				else if (state == (int)NODE_STATE::DEPARTURE)
				{
					ptrDeparture = vecControlList[y][x];
				}
				return;
			}
		}
	}
}

CControl::CControl()
	: vecControlList(YSIZE, vector<CNode*>(0))
	, iState(0)
{
	
}

CControl::~CControl()
{
}

int CControl::CalculateGValue(CNode* neighbor)
{
	POINT neighborIndex = neighbor->getIndex();
	POINT currentIndex = ptrCurrent->getIndex();
	// 대각선
	if (abs(currentIndex.x - neighborIndex.x) == abs(currentIndex.y - neighborIndex.y))
		return (ptrCurrent->getGValue() + LINE2);
	// 직선
	else
		return (ptrCurrent->getGValue() + LINE1);
}

int CControl::CalculateHValue(CNode* neighbor)
{
	POINT neighborIndex = neighbor->getIndex();
	POINT departureIndex = ptrDeparture->getIndex();
	
	int subX = abs(neighborIndex.x - departureIndex.x);
	int subY = abs(neighborIndex.y - departureIndex.y);

	if (subX == subY)
		return subX * LINE2;

	int count = 0;
	while (1)
	{
		if (subX == 0)
			return ((subY * LINE1) + (count * LINE2));
		else if (subY == 0)
			return ((subX * LINE1) + (count * LINE2));
		subX--;
		subY--;
		count++;
	}
}

void CControl::Init()
{
	ptrCurrent = ptrArrival;

	AStar();

	//ptrCurrent = queueNode.top();
	//queueNode.pop();
}
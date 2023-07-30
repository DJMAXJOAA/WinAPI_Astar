#include "pch.h"
#include "CControl.h"
#include "CNode.h"

bool cmp::operator() (Node* a, Node* b)
{
	if (a->iFValue == b->iFValue)
	{
		return (a->iHValue > b->iHValue);
	}
	else
	{
		return (a->iFValue > b->iFValue);
	}
}

void CControl::AStar()
{
	ptrCurrent->setState(NODE_STATE::VISIT);
	if (ptrCurrent == ptrDeparture)
	{
		Node* temp = ptrNode;
		while (temp != nullptr)
		{
			vecControlList[temp->pIndex.y][temp->pIndex.x]->setState(NODE_STATE::RESULT);
			printf("%d\n", temp->iFValue);
			temp = temp->prev;
		}

		printf("Ž�� �Ϸ�!\n");
		iState = END;

		return;
	}

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
			// ���� Ž���ϴ� ����, Ȥ�� ��, Ȥ�� �����
			if (ptrIndex.x == x && ptrIndex.y == y
			 ||	vecControlList[y][x]->getState() == (int)NODE_STATE::BLOCK
			 || vecControlList[y][x]->getState() == (int)NODE_STATE::ARRIVAL)
			{
				continue;
			}

			int GValue = CalculateGValue(vecControlList[y][x]);
			int HValue = CalculateHValue(vecControlList[y][x]);
			int FValue = GValue + HValue;

			// ���� ����� �ȵưų�, F���� �� ������
			if (vecControlList[y][x]->getState() == (int)NODE_STATE::NONE
				|| vecControlList[y][x]->getState() == (int)NODE_STATE::DEPARTURE
				|| FValue < vecControlList[y][x]->getFValue())
			{
				if (vecControlList[y][x]->getState() == (int)NODE_STATE::NONE)
				{
					vecControlList[y][x]->setState(NODE_STATE::NO_VISIT);
				}
				vecControlList[y][x]->setGValue(GValue);
				vecControlList[y][x]->setHValue(HValue);
				vecControlList[y][x]->setFValue();

				Node* temp = new Node;
				temp->iGValue = GValue;
				temp->iHValue = HValue;
				temp->iFValue = FValue;
				temp->pIndex = vecControlList[y][x]->getIndex();
				temp->prev = ptrNode;

				queueNode.push(temp);
			}
		}
	}
}

void CControl::Update()
{
	static int abcd = 0;

	if (iState != START)
		return;
	abcd++;

	Sleep(1);

	AStar();

	if (queueNode.empty())
	{
		printf("��� Ž�� ����\n");
		iState = END;
		return;
	}
	ptrNode = queueNode.top();
	ptrCurrent = vecControlList[ptrNode->pIndex.y][ptrNode->pIndex.x];
	printf("%d ��° ����\n", abcd);
	printf("g��::%d / h��::%d / f��::%d\n", ptrNode->iGValue, ptrNode->iHValue, ptrNode->iFValue);
	printf("x��ǥ::%d / y��ǥ::%d\n\n", ptrNode->pIndex.x, ptrNode->pIndex.y);
	queueNode.pop();
}

void CControl::Reset()
{
	queueNode = priority_queue<Node*, vector<Node*>, cmp>();
	ptrArrival = nullptr;
	ptrDeparture = nullptr;
	ptrCurrent = nullptr;
	for (int i = 0; i < YSIZE; i++)
	{
		vecControlList[i].clear();
	}
	iState = ARRIVAL;
}

void CControl::SetNodeActive(POINT cur_point, int state)
{
	if (iState > DEPARTURE)
	{
		printf("�Ա���\n");
		return;
	}

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
				printf("x::%d, y::%d ���, ���°�::%d\n", x, y, iState);
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
	// �밢��
	if (abs(currentIndex.x - neighborIndex.x) == abs(currentIndex.y - neighborIndex.y))
		return (ptrNode->iGValue + LINE2);
	// ����
	else
		return (ptrNode->iGValue + LINE1);
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

	Node* temp = new Node;
	temp->iGValue = 0;
	temp->iHValue = CalculateHValue(ptrCurrent);
	temp->iFValue = temp->iHValue;
	temp->pIndex = ptrCurrent->getIndex();
	temp->prev = nullptr;

	ptrNode = temp;

	AStar();
}
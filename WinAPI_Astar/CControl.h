#pragma once

class CNode;
struct Node;

enum CONTROL_STATE
{
	ARRIVAL, DEPARTURE, START, END
};

struct cmp
{
	bool operator() (Node* a, Node* b);
};

class CControl
{
	SINGLE(CControl);
private:
	vector<vector<CNode*>> vecControlList;
	priority_queue<Node*, vector<Node*>, cmp> queueNode;
	CNode* ptrArrival; // 출발
	CNode* ptrDeparture; // 도착
	CNode* ptrCurrent; // 현재 가리키는 포인터
	Node* ptrNode;
	int iState;		// 현재 상태 

public:
	void AStar();
	int CalculateGValue(CNode* neighbor);
	int CalculateHValue(CNode* neighbor);

public:
	CNode* GetNodeList(int x, int y) { return vecControlList[y][x]; }
	int GetState() { return iState; }

public:
	void SetNodeActive(POINT cur_point, int state);
	void SetState(int state) { iState = state; }

public:
	void AddNodeList(CNode* node, int n) { vecControlList[n].push_back(node); }
	void Init();
	void Update();
	void Reset();

public:
	CControl();
	~CControl();
};

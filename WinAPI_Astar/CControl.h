#pragma once

class CNode;

struct cmp
{
	bool operator() (CNode* a, CNode* b);
};

class CControl
{
	SINGLE(CControl);
private:
	vector<vector<CNode*>> vecControlList;
	priority_queue<CNode*, vector<CNode*>, cmp> queueNode;
	CNode* ptrDeparture;
	CNode* ptrArrival; // Ãâ¹ßµµÂø

public:
	void AddNodeList(CNode* node, int n) { vecControlList[n].push_back(node); }
	CNode* GetNodeList(int x, int y) { return vecControlList[y][x]; }

public:
	void Init();
	void Update();

public:
	CControl();
	~CControl();
};

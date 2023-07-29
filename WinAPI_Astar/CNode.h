#pragma once
#include "CObject.h"

enum class NODE_STATE
{
    NONE, 
    DEPARTURE, 
    ARRIVAL,
    BLOCK,
    NO_VISIT,
    VISIT,

    LAST
};

class CNode :
    public CObject
{
private:
    int iState; // 현재 내 상태(계산이 됐는지?)
    POINT pIndex; // 벡터 컨테이너 좌표

private:
    int iFValue; // 밸류값들
    int iHValue;
    int iGValue;

private:
    vector<CNode*> vecNeighbor; // 내가 갈 수 있는 노드들 저장

public:
    void setState(NODE_STATE state) { iState = (int)state; }
    void setGValue(int n) { iGValue = n; }
    void setHValue(int n) { iHValue = n; }
    void setFValue() { iFValue = iGValue + iHValue; }
    void setIndex(int x, int y) { pIndex.x = x; pIndex.y = y; }
    void AddNeighbor(CNode* node) { vecNeighbor.push_back(node); }

public:
    int getState() { return iState; }
    int getGValue() { return iGValue; }
    int getHValue() { return iHValue; }
    int getFValue() { return iFValue; }
    POINT getIndex() { return pIndex; }
    vector<CNode*>& getNeighbor() { return vecNeighbor; }

public:
    virtual void Update();
    virtual void Render(HDC hdc);

public:
    CNode(Vec2 pos, Vec2 scale);
    ~CNode();
};


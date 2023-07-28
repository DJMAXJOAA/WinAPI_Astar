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

private:
    int iGValue;
    int iHValue;
    int iFValue; // 밸류값들

private:
    vector<CNode*> vecNeighbor; // 내가 갈 수 있는 노드들 저장

public:
    void setState(NODE_STATE state) { iState = (int)state; }

public:
    int getGValue() { return iGValue; }
    int getHValue() { return iHValue; }
    int getFValue() { return iFValue; }


public:
    virtual void Update();
    virtual void Render(HDC hdc);

public:
    CNode(Vec2 pos, Vec2 scale);
    ~CNode();
};


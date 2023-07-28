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
    int iState; // ���� �� ����(����� �ƴ���?)

private:
    int iGValue;
    int iHValue;
    int iFValue; // �������

private:
    vector<CNode*> vecNeighbor; // ���� �� �� �ִ� ���� ����

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


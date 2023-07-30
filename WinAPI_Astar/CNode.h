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
    RESULT,

    LAST
};

struct Node
{
    int iFValue; // �������
    int iHValue;
    int iGValue;
    POINT pIndex; // ���� �����̳� ��ǥ

    Node* prev;
};

class CNode :
    public CObject
{
private:
    int iState; // ���� �� ����(����� �ƴ���?)
    POINT pIndex; // ���� �����̳� ��ǥ

private:
    int iFValue; // �������
    int iHValue;
    int iGValue;

public:
    void setState(NODE_STATE state) { iState = (int)state; }
    void setGValue(int n) { iGValue = n; }
    void setHValue(int n) { iHValue = n; }
    void setFValue() { iFValue = iGValue + iHValue; }
    void setIndex(int x, int y) { pIndex.x = x; pIndex.y = y; }

public:
    int getState() { return iState; }
    int getGValue() { return iGValue; }
    int getHValue() { return iHValue; }
    int getFValue() { return iFValue; }
    POINT getIndex() { return pIndex; }

public:
    virtual void Update();
    virtual void Render(HDC hdc);

public:
    CNode(Vec2 pos, Vec2 scale);
    ~CNode();
};


#include "pch.h"
#include "CNode.h"

#include "CCore.h"

COLORREF NodeRGB[(int)NODE_STATE::LAST]
{
	RGB(255,255,255),//NONE,
	RGB(0,0,255),//DEPARTURE,
	RGB(0,255,255),//ARRIVAL,
	RGB(0,0,0),//BLOCK,
	RGB(0,255,0),//NO_VISIT,
	RGB(255,0,0),//VISIT,
};

CNode::CNode(Vec2 pos, Vec2 scale)
	: iGValue(0)
	, iHValue(1)
	, iState(0)
{
	this->SetPos(pos);
	this->SetScale(scale);
}

CNode::~CNode()
{

}

void CNode::Update()
{
	iFValue = iGValue + iHValue;
}

void CNode::Render(HDC hdc)
{
	int interval = 10;
	Vec2 vPos = this->GetPos();
	Vec2 vScale = this->GetScale();
	wstring temp;
	RECT rect;

	HBRUSH Brush = CreateSolidBrush(NodeRGB[iState]);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, Brush);

	Rectangle(hdc,	(int)vPos.x, (int)vPos.y,
					(int)(vPos.x + vScale.x), (int)(vPos.y + vScale.y));

	SelectObject(hdc, oldBrush);
	DeleteObject(Brush);

	if (!(iState == (int)NODE_STATE::BLOCK || iState == (int)NODE_STATE::DEPARTURE || iState == (int)NODE_STATE::ARRIVAL))
	{
		temp = std::to_wstring(iGValue);
		rect = { (int)vPos.x + interval, (int)vPos.y + interval, (int)(vPos.x + vScale.x - interval),(int)vPos.y + interval };
		DrawText(hdc, temp.c_str(), temp.length(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_LEFT);

		temp = std::to_wstring(iHValue);
		rect = { (int)vPos.x + interval, (int)vPos.y + interval, (int)(vPos.x + vScale.x - interval),(int)vPos.y + interval };
		DrawText(hdc, temp.c_str(), temp.length(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_RIGHT);

		temp = std::to_wstring(iFValue);
		rect = { (int)vPos.x, (int)(vPos.y + vScale.y / 2), (int)(vPos.x + vScale.x),(int)(vPos.y + vScale.y) };
		DrawText(hdc, temp.c_str(), temp.length(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
}


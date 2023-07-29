#include "pch.h"
#include "CCore.h"

#include "CObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CControl.h"

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	hWnd = _hWnd;
	ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0, 0, ptResolution.x, ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	hdc = GetDC(hWnd);

	// ������۸� ��Ʈ��, dc�� �Ҵ��ϱ�
	hBit = CreateCompatibleBitmap(hdc, ptResolution.x, ptResolution.y);
	memDC = CreateCompatibleDC(hdc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(memDC, hBit);
	DeleteObject(hOldBit);

	// Manager �ʱ�ȭ
	CTimeMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->Init();

	return S_OK;
}

void CCore::Progress()
{
	// �Ŵ��� ������Ʈ
	CTimeMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();
	CSceneMgr::GetInstance()->Update();
	CControl::GetInstance()->Update();

	// ȭ�� Ŭ����
	Rectangle(memDC, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	// ȭ�� �׸���
	CSceneMgr::GetInstance()->Render(memDC);

	// ������۸�(ȭ�� ����)
	BitBlt(hdc, 0, 0, ptResolution.x, ptResolution.y, memDC, 0, 0, SRCCOPY);
	/*TransparentBlt(hdc, 0, 0, ptResolution.x, ptResolution.y, memDC, 0, 0, ptResolution.x, ptResolution.y, RGB(255, 0, 255));*/
}

CCore::CCore()
	: hWnd(0)
	, ptResolution{}
	, hdc(0)
	, hBit(0)
	, memDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(hWnd, hdc);
	DeleteDC(memDC);
	DeleteObject(hBit);
}

#include "pch.h"
#include "CTimeMgr.h"

#include "CCore.h"

CTimeMgr::CTimeMgr()
	: liCurCount{}
	, liFrequency{}
	, liPrevCount{}
	, dDT(0.)
	, dAcc(0.)
	, iCallCount(0)
	, iFPS(0)
{
}

CTimeMgr::~CTimeMgr()
{
}


void CTimeMgr::Init()
{
	// ���� ī��Ʈ Ƚ��
	QueryPerformanceCounter(&liCurCount);

	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&liFrequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&liCurCount);

	// ���� �������� ī���ð�, ���� �������� ī���� ���� ���̸� ���Ѵ�
	dDT = (double)(liCurCount.QuadPart - liPrevCount.QuadPart) /
		(double)liFrequency.QuadPart;

	// ����ī��Ʈ ���� ���� ī��Ʈ������ ����(���� ��� ����)
	liPrevCount = liCurCount;

	++iCallCount;
	dAcc += dDT; // DT ����

	if (dAcc >= 1.) // 1�ʸ��� �ѹ� üũ
	{
		iFPS = iCallCount;
		dAcc = 0.;
		iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", iFPS, dDT);
		SetWindowText(CCore::GetInstance()->GetMainhWnd(), szBuffer); // Ÿ��Ʋ ����
	}
}


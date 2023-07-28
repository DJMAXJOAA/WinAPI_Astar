#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER liCurCount;
	LARGE_INTEGER liPrevCount;
	LARGE_INTEGER liFrequency;

	double dDT; // �������� �ð���
	double dAcc; // ���� �ð�
	UINT iCallCount;
	UINT iFPS;

public:
	void Init();
	void Update();

public:
	double GetDT() { return dDT; }
	float GetfDT() { return (float)dDT; }

private:
	CTimeMgr();
	~CTimeMgr();
};


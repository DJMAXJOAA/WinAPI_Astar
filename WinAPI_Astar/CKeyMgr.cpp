#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"


int arrVK[(int)KEY::LAST]
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	VK_MENU,
	VK_LSHIFT,
	VK_SPACE,
	VK_CONTROL,
	VK_RETURN,
	VK_ESCAPE,
};

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false, true });
	}
}

void CKeyMgr::Update()
{
	// ������ Ȱ���ÿ��� Ű�Է� ����
	HWND hMainWnd = CCore::GetInstance()->GetMainhWnd();
	HWND hWnd = GetFocus();

	/*if (hWnd == hMainWnd)*/
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			// Ű�� ��������
			if (GetAsyncKeyState(arrVK[i]) & 0x8000)
			{
				// �������� ������ �־���
				if (vecKey[i].bPrevPush)

				{
					vecKey[i].eState = KEY_STATE::HOLD;
				}
				// �̹��� ���� ����
				else
				{
					vecKey[i].eState = KEY_STATE::TAP;
				}
				vecKey[i].bPrevPush = true;
			}

			// Ű�� �ȴ���������
			else
			{
				// ������ ������ �־���(���� ����)
				if (vecKey[i].bPrevPush)
				{
					vecKey[i].eState = KEY_STATE::AWAY;
				}
				// �������� �����־���
				else
				{
					vecKey[i].eState = KEY_STATE::NONE;
				}
				vecKey[i].bPrevPush = false;
			}
		}
	}

	// ������ ��Ŀ�� ���� ����
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			vecKey[i].bPrevPush = false;
			// �����ų� ������ �ִ� ���¸� �ڵ����� ������ �ϱ�
			if (KEY_STATE::TAP == vecKey[i].eState
				|| KEY_STATE::HOLD == vecKey[i].eState)
			{
				vecKey[i].eState = KEY_STATE::AWAY;
			}
			// ������ �ִ� ���¶��, NONE���� ���� �ϱ�
			if (KEY_STATE::AWAY == vecKey[i].eState)
			{
				vecKey[i].bKeyAvailability = true;
				vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}
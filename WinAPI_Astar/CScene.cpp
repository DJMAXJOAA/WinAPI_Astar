#include "pch.h"
#include "CScene.h"

#include "CObject.h"

void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < arrObj[i].size(); j++)
		{
			arrObj[i][j]->Update();
		}
	}
}

void CScene::Render(HDC hdc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < arrObj[i].size(); j++)
		{
			arrObj[i][j]->Render(hdc);
		}
	}
}

CScene::CScene()
{
}

CScene::~CScene()
{
	// �� ��� ������Ʈ ����
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < arrObj[i].size(); j++)
		{
			// arrObj[i]�� �׷��� ���� j ��ü ����
			delete arrObj[i][j];
		}
	}
}

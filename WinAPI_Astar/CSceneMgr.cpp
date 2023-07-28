#include "pch.h"
#include "CSceneMgr.h"
#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"

void CSceneMgr::Init()
{
	arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	arrScene[(UINT)SCENE_TYPE::START]->SetName(L"���� �̸�");

	pCurScene = arrScene[(UINT)SCENE_TYPE::START];
	pCurScene->Enter(); // �� ����
}

void CSceneMgr::Update()
{
	// ���� ���� ������Ʈ �ؾߵ�
	pCurScene->Update();

}

void CSceneMgr::Render(HDC hdc)
{
	// ����
	pCurScene->Render(hdc);
}

CSceneMgr::CSceneMgr()
	: arrScene{}
	, pCurScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (nullptr != arrScene[i])
		{
			delete arrScene[i];
		}
	}
}

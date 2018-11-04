#pragma once
#include<DrawSprite.h>
#include "resource.h"
#include <GameEngine.h>
#include "DrawSpriteManage.h"
#include "Character.h"
#include "CustomObject.h"
#include <time.h>
#include <MMSystem.h>
#include <map>
#include <iostream>
using namespace std;
#pragma comment(lib, "WINMM.LIB")


//
GameEngine *g_pGE;
long g_lPreTime;
int g_nFrequency;
//�Ի��ṹ
typedef struct tagDIALOG
{
	LPTSTR szName;
	LPTSTR szTalk;
}DIALOG;
//�Ի�����
DIALOG g_dlg[5] = { {L"�ӳ�",L"ʲô��"},{L"��˹",L"��ְ�"},{ L"��˹",L"��ְ�" },{ L"��˹",L"��ְ�" },{ L"��˹",L"��ְ�" } };
int g_nDialigIndex;//�Ի�����

//���徫��ʵ��
DrawSprite *g_pSprBackGround;
DrawSprite *g_pTable;
DrawSprite *g_pChair[4];
DrawSprite *g_pMenu;
DrawSprite *g_pSprDlg;
DrawSprite *g_pSprDlgBG;
DrawSprite *g_pMenuButton1;
DrawSprite *g_pMenuButton2;
DrawSprite *g_pMenuButton3;
DrawSprite *g_pLoadScene;
DrawSprite *g_pStoryTeller;
DrawSprite *g_pPlayer[5];
DrawSprite *g_PlayerDialog[5];
DrawSprite *g_DrawObject[100];
DrawSpriteManage g_Sprm;
DrawSprite *g_pSetMenu;
DrawSprite *g_pSetCharacter[3];
DrawSprite *g_pSetValue[8];
Character *player[4];
Character *enemy[10];
DrawSprite *g_pSetMenuButton;
//���鶨��
DrawSprite *g_pSprCharStateL;
DrawSprite *g_pSprCharStateR;
DrawSprite *g_pStatus[8];
DrawSprite *g_pFightIcon[20];
DrawSprite *g_pSkill[20];
DrawSprite *g_pText[100];
DrawSprite *g_pStatusSign1[3];
DrawSprite *g_pStatusSign2[8];
DrawSprite *g_pStatusSign3[8];
DrawSprite *g_pShowHp[3];
DrawSprite *g_pShowMp[3];
//����λ���������
int g_nScene;//�������
BOOL g_bInitScene; 
BOOL InitScene_1(HWND hWnd);
BOOL PlayScene_1(HWND hWnd);

BOOL InitScene_2(HWND hWnd);
BOOL PlayScene_2(HWND hWnd);

BOOL InitScene_3(HWND hWnd);
BOOL PlayScene_3(HWND hWnd);

BOOL InitScene_4(HWND hWnd);
BOOL PlayScene_4(HWND hWnd);

BOOL InitScene_5(HWND hWnd);
BOOL PlayScene_5(HWND hWnd);

BOOL InitScene_6(HWND hWnd);
BOOL PlayScene_6(HWND hWnd);
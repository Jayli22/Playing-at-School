#pragma once
#include <windows.h>
#include <ximage.h>
#include "DrawSprite.h"
#define WM_OVEROBJECT WM_USER+10
#define WM_LEAVEOBJECT WM_USER+11
#define WM_FIGHT1 WM_USER+12
#define WM_MUSIC WM_USER+13

// ���ֵĶ��뷽ʽ,Ĭ�������
// �����
#define HLS_LEFT DT_LEFT
// ���ж���
#define HLS_CENTER DT_CENTER
// �Ҷ���
#define HLS_RIGHT DT_RIGHT
ATOM WINAPI RegisterCustomObject(HINSTANCE hIns,LPCTSTR ClassName);

HWND WINAPI CreateCustomObject(LPCTSTR ClassName, LPCTSTR pszTitle, // ��ʾ���ı�
	DWORD style, // ���ڷ��
	INT x, // x ����
	INT y, // y ����
	INT nWidth, // ���
	INT nHeight, //�߶�
	HWND hWndParent, // �����ھ��
	UINT CtrlID,
	DrawSprite *bmp); // �ؼ� ID

LONG WINAPI SubclassCustomObject(HWND hwnd);

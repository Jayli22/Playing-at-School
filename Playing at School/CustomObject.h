#pragma once
#include <windows.h>
#include <ximage.h>
#include "DrawSprite.h"
#define WM_OVEROBJECT WM_USER+10
#define WM_LEAVEOBJECT WM_USER+11
#define WM_FIGHT1 WM_USER+12
#define WM_MUSIC WM_USER+13

// 文字的对齐方式,默认左对齐
// 左对齐
#define HLS_LEFT DT_LEFT
// 居中对齐
#define HLS_CENTER DT_CENTER
// 右对齐
#define HLS_RIGHT DT_RIGHT
ATOM WINAPI RegisterCustomObject(HINSTANCE hIns,LPCTSTR ClassName);

HWND WINAPI CreateCustomObject(LPCTSTR ClassName, LPCTSTR pszTitle, // 显示的文本
	DWORD style, // 窗口风格
	INT x, // x 坐标
	INT y, // y 坐标
	INT nWidth, // 宽度
	INT nHeight, //高度
	HWND hWndParent, // 父窗口句柄
	UINT CtrlID,
	DrawSprite *bmp); // 控件 ID

LONG WINAPI SubclassCustomObject(HWND hwnd);

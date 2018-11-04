#include "CustomObject.h"
#include <assert.h>
#pragma comment(lib,"cximagecrtu.lib")
LRESULT CALLBACK CtrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LPCTSTR m_ClassName;
int m_ObjectID;
int m_x;
int m_y;
DrawSprite *m_bmp[100];

// 注册控件类
ATOM WINAPI RegisterCustomObject(HINSTANCE hIns, LPCTSTR ClassName)
{
	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_PARENTDC | CS_GLOBALCLASS;
	wndClass.lpszClassName = ClassName;
	//wndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	wndClass.hInstance = hIns;
	wndClass.lpfnWndProc = (WNDPROC)CtrlProc;
	wndClass.cbWndExtra = sizeof(INT*); // 为窗口分配额外内存,用来保存我们自己的指针.
	return RegisterClassEx(&wndClass);
}

// 创建一个超链接控件
HWND WINAPI CreateCustomObject(LPCTSTR ClassName,
	LPCTSTR pszTitle, // 显示的文本
	DWORD style, // 窗口风格
	INT x, // x 坐标
	INT y, // y 坐标
	INT nWidth, // 宽度
	INT nHeight, //高度
	HWND hWndParent, // 父窗口句柄
	UINT CtrlID,
	DrawSprite *bmp) // 控件 ID
{
	m_ClassName = ClassName;
	m_ObjectID = CtrlID;
	m_bmp[CtrlID] = bmp;
	return CreateWindow(
		ClassName,
		pszTitle,
		WS_CHILD | style,
		x,
		y,
		nWidth,
		nHeight,
		hWndParent,
		(HMENU)CtrlID,
		NULL,
		0);
}
// 子类化控件,在设计对话框程序时方便可视化调整
LONG WINAPI SubclassCustomObject(HWND hwnd)
{
		(hwnd);

	if (!SetWindowLong(hwnd, 0, 0))
		SetClassLong(hwnd, GCL_CBWNDEXTRA, sizeof(INT*));

	SetWindowLong(hwnd, 0, 0);

	return SetWindowLong(hwnd, GWL_WNDPROC, (LONG)CtrlProc);
}
// 设置控件的文本颜色
void WINAPI SetCtrlTextColor(HWND hWnd, HDC hDc, COLORREF rf, BOOL bUnderline = TRUE)
{
	HDC hdc = NULL;

	if (hDc == NULL)
		hdc = GetDC(hWnd);
	else
		hdc = hDc;

	HFONT hFont = (HFONT)SendMessage(GetParent(hWnd), WM_GETFONT, 0, 0);
	LOGFONT font;
	ZeroMemory(&font, sizeof(font));
	GetObject(hFont, sizeof(font), &font);
	font.lfUnderline = bUnderline;
	hFont = CreateFontIndirect(&font);
	SelectObject(hdc, hFont);

	int length = GetWindowTextLength(hWnd);
	TCHAR *title = new TCHAR[length + 1];
	ZeroMemory(title, (length + 1) * sizeof(TCHAR));
	GetWindowText(hWnd, title, length + 1);
	// 设置背景和文本颜色
	SetTextColor(hdc, rf);
	SetBkMode(hdc, TRANSPARENT);
	RECT rc;
	GetClientRect(hWnd, &rc);
	DWORD style = GetWindowLong(hWnd, GWL_STYLE);
	// 设置文本对齐方式
	if (style & HLS_CENTER)
		DrawText(hdc, title, length, &rc, DT_CENTER);
	else if (style & HLS_RIGHT)
		DrawText(hdc, title, length, &rc, DT_RIGHT);
	else
		DrawText(hdc, title, length, &rc, DT_LEFT);

	delete[]title;
	if (hdc)
		ReleaseDC(hWnd, hdc);
}




// 控件的消息处理过程
LRESULT CALLBACK CtrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TRACKMOUSEEVENT tms;

	switch (uMsg)
	{
	case WM_DRAWITEM:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}
	break;
	case WM_ERASEBKGND: // 画背景
	{
		HDC hDc = (HDC)wParam;
	}
	break;
	case WM_MOUSEMOVE:
	{
		tms.cbSize = sizeof(tms);
		tms.hwndTrack = hWnd;
		tms.dwFlags = TME_HOVER | TME_LEAVE;
		tms.dwHoverTime = 10;
		TrackMouseEvent(&tms);

		if (GetCapture() != hWnd) // 是否捕获过鼠标
			break;

		RECT rc;
		POINT pt;
		GetCursorPos(&pt);  // 获取当前鼠标位置
		GetWindowRect(hWnd, &rc); // 获取控件区域

		if (!PtInRect(&rc, pt)) // 如果鼠标离开控件则释放鼠标
			ReleaseCapture();
	}
	break;
	case WM_MOUSEHOVER:
		//SetCtrlTextColor(hWnd, NULL, RGB(255, 0, 0));
		m_bmp[GetDlgCtrlID(hWnd)]->FloatEvent(TRUE);
		break;
	case WM_MOUSELEAVE:
		if (m_bmp[GetDlgCtrlID(hWnd)] != NULL)
		m_bmp[GetDlgCtrlID(hWnd)]->FloatEvent(FALSE);
		break;
	case WM_LBUTTONDOWN:
		SetCapture(hWnd); // 捕获鼠标
		SendMessage(GetParent(hWnd), WM_COMMAND, wParam, GetDlgCtrlID(hWnd));
		break;
	case WM_LBUTTONUP:
	//{
	//	if (GetCapture() != hWnd) // 如果没有捕获过鼠标说明没有在控件上进行单击
	//		break;

	//	wParam = GetDlgCtrlID(hWnd);
	//	SendMessage(GetParent(hWnd), WM_FIGHT1, wParam, GetDlgCtrlID(hWnd));
	//}
	break;
	case WM_SETCURSOR:
		SetCursor(LoadCursor(NULL, IDC_HAND));
		break;
	

	case WM_COMMAND:
		SendMessage(GetParent(hWnd), WM_COMMAND, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

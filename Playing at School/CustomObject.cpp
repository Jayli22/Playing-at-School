#include "CustomObject.h"
#include <assert.h>
#pragma comment(lib,"cximagecrtu.lib")
LRESULT CALLBACK CtrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LPCTSTR m_ClassName;
int m_ObjectID;
int m_x;
int m_y;
DrawSprite *m_bmp[100];

// ע��ؼ���
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
	wndClass.cbWndExtra = sizeof(INT*); // Ϊ���ڷ�������ڴ�,�������������Լ���ָ��.
	return RegisterClassEx(&wndClass);
}

// ����һ�������ӿؼ�
HWND WINAPI CreateCustomObject(LPCTSTR ClassName,
	LPCTSTR pszTitle, // ��ʾ���ı�
	DWORD style, // ���ڷ��
	INT x, // x ����
	INT y, // y ����
	INT nWidth, // ���
	INT nHeight, //�߶�
	HWND hWndParent, // �����ھ��
	UINT CtrlID,
	DrawSprite *bmp) // �ؼ� ID
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
// ���໯�ؼ�,����ƶԻ������ʱ������ӻ�����
LONG WINAPI SubclassCustomObject(HWND hwnd)
{
		(hwnd);

	if (!SetWindowLong(hwnd, 0, 0))
		SetClassLong(hwnd, GCL_CBWNDEXTRA, sizeof(INT*));

	SetWindowLong(hwnd, 0, 0);

	return SetWindowLong(hwnd, GWL_WNDPROC, (LONG)CtrlProc);
}
// ���ÿؼ����ı���ɫ
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
	// ���ñ������ı���ɫ
	SetTextColor(hdc, rf);
	SetBkMode(hdc, TRANSPARENT);
	RECT rc;
	GetClientRect(hWnd, &rc);
	DWORD style = GetWindowLong(hWnd, GWL_STYLE);
	// �����ı����뷽ʽ
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




// �ؼ�����Ϣ�������
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
	case WM_ERASEBKGND: // ������
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

		if (GetCapture() != hWnd) // �Ƿ񲶻�����
			break;

		RECT rc;
		POINT pt;
		GetCursorPos(&pt);  // ��ȡ��ǰ���λ��
		GetWindowRect(hWnd, &rc); // ��ȡ�ؼ�����

		if (!PtInRect(&rc, pt)) // �������뿪�ؼ����ͷ����
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
		SetCapture(hWnd); // �������
		SendMessage(GetParent(hWnd), WM_COMMAND, wParam, GetDlgCtrlID(hWnd));
		break;
	case WM_LBUTTONUP:
	//{
	//	if (GetCapture() != hWnd) // ���û�в�������˵��û���ڿؼ��Ͻ��е���
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

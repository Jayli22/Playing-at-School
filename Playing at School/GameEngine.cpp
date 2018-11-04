#include "GameEngine.h"
#include "winuser.h"
#include "mmsystem.h"

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"user32.lib")
GameEngine *GameEngine::m_PGameEngine = NULL;


GameEngine::GameEngine(HINSTANCE hInstance, LPTSTR szWindowsClass, LPTSTR szTitle, WORD wIcon, WORD wSmallIcon, BOOL bFullScreen/* =FALSE */, int nColorbit/* =32 */, int nWidth/* =800 */, int nHeight/* =600 */)
{
	m_PGameEngine = this;
	m_hInstance = hInstance;

	lstrcpy(m_szWindowClass, szWindowsClass);
	lstrcpy(m_szTittle, szTitle);

	m_bFullScreen = bFullScreen;
	m_nColorbit = nColorbit;
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	m_wIcon = wIcon;
	m_wSmallIcon = wSmallIcon;

	m_lStartTime = timeGetTime();
	m_lNextGameTick = m_lStartTime;

}

LRESULT CALLBACK	WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);  //窗口过程函数
BOOL GameInitialize(HINSTANCE hInstance); //在此函数中进行资源的初始化
VOID GamePaint(HDC hDC); // 在此函数中进行绘图代码的重写
BOOL GameEnd(HWND hwnd);  //在此函数中进行资源的清理

BOOL GameEngine::CreateWnd() {
	//【1】窗口创建四步曲之一：开始设计一个完整的窗口类
	WNDCLASSEX wndClass = { 0 };							//用WINDCLASSEX定义了一个窗口类
	HWND hWnd = NULL;
	int nPosX, nPosY, nWndWidth, nWndHeight;
	DWORD dwWinStyle;
	wndClass.cbSize = sizeof(WNDCLASSEX);			//设置结构体的字节数大小
	wndClass.style = CS_HREDRAW | CS_VREDRAW ;	//设置窗口的样式
	wndClass.lpfnWndProc = WndProc;					//设置指向窗口过程函数的指针
	wndClass.cbClsExtra = 0;								//窗口类的附加内存，取0就可以了
	wndClass.cbWndExtra = 0;							//窗口的附加内存，依然取0就行了
	wndClass.hInstance = m_hInstance;						//指定包含窗口过程的程序的实例句柄。
	//wndClass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //本地加载自定义ico图标
	wndClass.hIconSm = LoadIcon(m_hInstance, MAKEINTRESOURCE(m_wIcon));
	wndClass.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(m_wSmallIcon));
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //指定窗口类的光标句柄。
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);  //为hbrBackground成员指定一个
	wndClass.lpszMenuName = NULL;						//用一个以空终止的字符串，指定菜单资源的名字。
	wndClass.lpszClassName = m_szWindowClass;		//用一个以空终止的字符串，指定窗口类的名字。
													//【2】窗口创建四步曲之二：注册窗口类
	if (!RegisterClassEx(&wndClass))				//设计完窗口后，需要对窗口类进行注册，这样才能创建该类型的窗口
		return -1;
	//使用devmode结构设置屏幕显示模式
	DEVMODE DevMode;
	ZeroMemory(&DevMode, sizeof(DevMode));
	DevMode.dmSize = sizeof(DevMode);//设置DevMode存储空间以存储屏幕属性数据
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &DevMode);
	BOOL bDisplayChange = FALSE;//表示屏幕显示模式是否改变
	if (DevMode.dmBitsPerPel!=(unsigned long)m_nColorbit)
	{
		DevMode.dmBitsPerPel = m_nColorbit;
		bDisplayChange = TRUE;
	}
	if (m_bFullScreen&&m_nWidth!=GetSystemMetrics(SM_CXSCREEN)||m_nWidth>GetSystemMetrics(SM_CXSCREEN))
	{
		DevMode.dmPelsWidth = m_nWidth;
		DevMode.dmPelsHeight = m_nHeight;
		bDisplayChange = TRUE;
	}
	if (bDisplayChange)
	{
		LONG result = ChangeDisplaySettings(&DevMode, 0);//动态修改屏幕显示模式
		//判断屏幕显示模式是否成功
		if (result==DISP_CHANGE_SUCCESSFUL)
		{
			ChangeDisplaySettings(&DevMode, CDS_FULLSCREEN);
		}
		else
		{
			ChangeDisplaySettings(NULL, 0);
			return FALSE;
		}
	}
	if (m_bFullScreen)
	{
		nPosX = 0;
		nPosY = 0;
		dwWinStyle = WS_POPUP;
		nWndHeight = m_nHeight;
		nWndWidth = m_nWidth;
	
	}
	else
	{
		nWndWidth = m_nWidth+GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
		nWndHeight = m_nHeight + GetSystemMetrics(SM_CXFIXEDFRAME) * 10;

		//
		nPosX = (GetSystemMetrics(SM_CXSCREEN) - nWndWidth) / 2;
		nPosY = (GetSystemMetrics(SM_CYSCREEN) - nWndHeight) / 2;

		dwWinStyle = WS_SYSMENU | WS_CAPTION;
	}

	hWnd = CreateWindow(m_szWindowClass,
		m_szTittle,
		dwWinStyle,
		nPosX,
		nPosY,
		nWndWidth,
		nWndHeight,
		NULL,
		NULL,
		m_hInstance,
		NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	return TRUE;
}



GameEngine::~GameEngine()
{
}

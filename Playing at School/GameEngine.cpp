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

LRESULT CALLBACK	WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);  //���ڹ��̺���
BOOL GameInitialize(HINSTANCE hInstance); //�ڴ˺����н�����Դ�ĳ�ʼ��
VOID GamePaint(HDC hDC); // �ڴ˺����н��л�ͼ�������д
BOOL GameEnd(HWND hwnd);  //�ڴ˺����н�����Դ������

BOOL GameEngine::CreateWnd() {
	//��1�����ڴ����Ĳ���֮һ����ʼ���һ�������Ĵ�����
	WNDCLASSEX wndClass = { 0 };							//��WINDCLASSEX������һ��������
	HWND hWnd = NULL;
	int nPosX, nPosY, nWndWidth, nWndHeight;
	DWORD dwWinStyle;
	wndClass.cbSize = sizeof(WNDCLASSEX);			//���ýṹ����ֽ�����С
	wndClass.style = CS_HREDRAW | CS_VREDRAW ;	//���ô��ڵ���ʽ
	wndClass.lpfnWndProc = WndProc;					//����ָ�򴰿ڹ��̺�����ָ��
	wndClass.cbClsExtra = 0;								//������ĸ����ڴ棬ȡ0�Ϳ�����
	wndClass.cbWndExtra = 0;							//���ڵĸ����ڴ棬��Ȼȡ0������
	wndClass.hInstance = m_hInstance;						//ָ���������ڹ��̵ĳ����ʵ�������
	//wndClass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //���ؼ����Զ���icoͼ��
	wndClass.hIconSm = LoadIcon(m_hInstance, MAKEINTRESOURCE(m_wIcon));
	wndClass.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(m_wSmallIcon));
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //ָ��������Ĺ������
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);  //ΪhbrBackground��Աָ��һ��
	wndClass.lpszMenuName = NULL;						//��һ���Կ���ֹ���ַ�����ָ���˵���Դ�����֡�
	wndClass.lpszClassName = m_szWindowClass;		//��һ���Կ���ֹ���ַ�����ָ������������֡�
													//��2�����ڴ����Ĳ���֮����ע�ᴰ����
	if (!RegisterClassEx(&wndClass))				//����괰�ں���Ҫ�Դ��������ע�ᣬ�������ܴ��������͵Ĵ���
		return -1;
	//ʹ��devmode�ṹ������Ļ��ʾģʽ
	DEVMODE DevMode;
	ZeroMemory(&DevMode, sizeof(DevMode));
	DevMode.dmSize = sizeof(DevMode);//����DevMode�洢�ռ��Դ洢��Ļ��������
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &DevMode);
	BOOL bDisplayChange = FALSE;//��ʾ��Ļ��ʾģʽ�Ƿ�ı�
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
		LONG result = ChangeDisplaySettings(&DevMode, 0);//��̬�޸���Ļ��ʾģʽ
		//�ж���Ļ��ʾģʽ�Ƿ�ɹ�
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

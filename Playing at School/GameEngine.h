#pragma once
#include<windows.h>
class GameEngine
{
protected:
	static GameEngine *m_PGameEngine; //静态成员，记录引擎自身指针
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	TCHAR m_szWindowClass[50];
	TCHAR m_szTittle[50];
	WORD m_wIcon;
	WORD m_wSmallIcon;
	int m_nWidth, m_nHeight;
	BOOL m_bFullScreen; 
	int m_nColorbit;
	int m_nFrameDelay;
	long m_lNextGameTick; //下一次游戏循环执行时间
	long m_lStartTime; //记录游戏开始时间
	BOOL m_bPause;

public:
	GameEngine(HINSTANCE hInstance,
		LPTSTR szWindowsClass,
		LPTSTR szTitle,
		WORD wIcon,
		WORD wSmallIcon,
		BOOL bFullScreen=FALSE,
		int nColorbit=32,
		int nWidth=800,
		int nHeight=600);
	virtual ~GameEngine();
	BOOL CreateWnd();
	static GameEngine *GetGameEngine()
	{
		return m_PGameEngine;
	}

	HINSTANCE GetInstance()
	{
		return m_hInstance;
	}
	HWND GetWindow()
	{
		return m_hWnd;
	}
	void SetWindow(HWND hWnd)
	{
		m_hWnd = hWnd;
	}
	BOOL GetPause()
	{
		return m_bPause;
	}
	void SetPause(BOOL bPause)
	{
		m_bPause = bPause;
		}
	
	int GetFrameDelay()
	{
		return m_nFrameDelay;
	}
	void SetFrameDelay(int nFrameDelay)
	{
		m_nFrameDelay = nFrameDelay;
	}

	int GetWidth() {
		return m_nWidth;
	}
	int GetHeight()
	{
		return m_nHeight;
	}

	long GetStartTime()
	{
		return m_lStartTime;
	}
	void SetNextGameTick(int nNextGameTick)
	{
		m_lNextGameTick = nNextGameTick;
	}
	int GetNextGameTick()
	{
		return m_lNextGameTick;
	}


};


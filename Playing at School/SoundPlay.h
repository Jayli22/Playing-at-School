#pragma once
#include <Windows.h>
#include <MMSystem.h>
#include <map>
#include <iostream>
using namespace std;
#pragma comment(lib, "WINMM.LIB")
class SoundPlay
{
public:
	SoundPlay()
	{

	}
	 void PlayBeep()
	{
		Beep(3000, 500);
	}

	 void PlaySysMusic()
	{
		MessageBeep(MB_OK);
		Sleep(800);
		MessageBeep(MB_ICONWARNING);
		Sleep(800);
		MessageBeep(MB_ICONSTOP);
		Sleep(800);
		MessageBeep(MB_ICONERROR);
		Sleep(800);
		MessageBeep(MB_ICONEXCLAMATION);
	}


	 void PlayWavMusic(LPCWSTR file)
	{
		PlaySound(file, NULL/*AfxGetInstanceHandle()*/, SND_FILENAME | SND_ASYNC);
	}


	 void PlayMp3Music_1(LPCWSTR file)
	{
		mciSendString(file, NULL, 0, 0);
		//mciSendString("play bg.mp3", NULL, 0, 0);
	}


	 void PlayMp3Music_2(LPCWSTR file)
	{
		MCI_OPEN_PARMS MciOpen;
		MCI_PLAY_PARMS MciPlay;
		MciOpen.lpstrElementName = file;
		MciOpen.lpstrDeviceType = NULL;


		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&MciOpen);
		UINT wDeviceID = MciOpen.wDeviceID;
		mciSendCommand(wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& MciPlay);
	}


#define TIMER_MUSIC_STATE 100
	MCI_OPEN_PARMS    gMciOpen;
	MCI_PLAY_PARMS    gMciPlay;
	MCI_STATUS_PARMS  gStatus;
	map<UINT_PTR, int> mapTimer;
	  void CheckMusicState()
	{
		
		 map<UINT_PTR, int> mapTimer;
		//播放文件长度
		gStatus.dwItem = MCI_STATUS_LENGTH;
		mciSendCommand(gMciOpen.wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&gStatus);
		DWORD dwLen = gStatus.dwReturn;


		//当前播放长度
		gStatus.dwItem = MCI_STATUS_POSITION;
		mciSendCommand(gMciOpen.wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&gStatus);
		DWORD dwCurLen = gStatus.dwReturn;


		cout << "文件长度: " << dwLen << ",当前播放位置: " << dwCurLen << endl;


		//循环播放
		if (dwLen == dwCurLen)
		{
			mciSendCommand(gMciOpen.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
			mciSendCommand(gMciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& gMciPlay);
		}
	}
	void CALLBACK TimerProc(HWND, UINT message, UINT_PTR idTimer, DWORD dwTime)
	{
		if (WM_TIMER == message)
		{
			switch (mapTimer[idTimer])
			{
			case TIMER_MUSIC_STATE:
				CheckMusicState();
				break;
			default:
				break;
			}
		}
	}
	 void PlayMp3Music_3(LPCWSTR file)
	{
		
		gMciOpen.lpstrElementName = file;
		gMciOpen.lpstrDeviceType = NULL;


		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&gMciOpen);
		mciSendCommand(gMciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& gMciPlay);


		//UINT_PTR timer = SetTimer(NULL, TIMER_MUSIC_STATE, 1000, TimerProc);
		mapTimer.insert(make_pair(timer, TIMER_MUSIC_STATE));
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (msg.message == WM_TIMER)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
};


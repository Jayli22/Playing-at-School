#include "main.h"
#include "atlimage.h"
#include <string>
using namespace std;
//全局变量声明
HDC g_hdc = NULL;


//全局函数声明，防止“未声明的标识”系列错误
//------------------------------------------------------------------------------------------------
LRESULT CALLBACK	WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);  //窗口过程函数
BOOL GameInitialize(HINSTANCE hInstance);
void GameAction(HWND hWnd);
CString IntToCString(int n);
HANDLE hThread;
DWORD threadId;
DWORD WINAPI ThreadFunc(LPVOID n);
void PressKey(DWORD Key, int x);
void CheckSysMsg(void);  //监听键盘输入
int g_bFightStatus=0;
void Scene4Dialog(HWND hWnd);
void GameTitle(HWND hWnd);
void Delay(long time);
int PerCal(int x, int y);
int fightstatussign = 3;
int skillchoosesign;
int playermessagesentsign =1;
int damagepoint;
CString  soundfile[20];
int g_nCharacternum = 0;
int leftenemy;
void ActionQueue();
int actionQueue[11] = { 0,1,2,3,4,5,6,7,8,9,10 };
int actionNow=0;
int ChooseTarget();
int WinTime=0;
BOOL isGIF = FALSE;

//-----------------------------------【WinMain( )函数】--------------------------------------
//	描述：Windows应用程序的入口函数，我们的程序从这里开始
//------------------------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{


	//MoveWindow(hwnd, 250, 80, WINDOW_WIDTH, WINDOW_HEIGHT, true);		//调整窗口显示时的位置，使窗口左上角位于（250,80）处

	// 初始化游戏资源，若初始化失败，弹出消息框，并返回FALSE
	if (!GameInitialize(hInstance))
	{
		return FALSE;
	}


	//【5】消息循环过程
	MSG msg = { 0 };		//定义并初始化msg
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (!GameEngine::GetGameEngine()->GetPause())
			{
				//游戏循环
				long nTick = timeGetTime();
				//获取下次循环时间
				long nNextTick = GameEngine::GetGameEngine()->GetNextGameTick();
				if (nTick > nNextTick)//尚未达到下次循环时间
				{
					long nNextGameTick = nTick + GameEngine::GetGameEngine()->GetFrameDelay();
					GameEngine::GetGameEngine()->SetNextGameTick(nNextGameTick);
					GameAction(GameEngine::GetGameEngine()->GetWindow());
				}
			}
		}

	}

	////【6】窗口类的注销
	//UnregisterClass(L"ForTheDreamOfGameDevelop", wndClass.hInstance);  //程序准备结束，注销窗口类
	return TRUE;
}
							  

BOOL GameInitialize(HINSTANCE hInstance) {
	//创建游戏引擎
	g_pGE = new GameEngine(hInstance, TEXT("Playing at School"), TEXT("Playing at School"), IDI_ICON1, IDI_ICON2, FALSE, 32,1280, 720);
	if (g_pGE == NULL)
	{
		return FALSE;
	}

	for (int i = 1;i<100;i++)
	{
		RegisterCustomObject(hInstance,IntToCString(i));
	}

	g_pGE->SetFrameDelay(15);
	g_pGE->SetPause(FALSE);

	if (!g_pGE->CreateWnd())
	{
		MessageBox(NULL, L"修改显示模式失败！\r\n程序退出", L"错误", MB_OK | MB_ICONERROR);
		return FALSE;
	}
	srand((unsigned)time(NULL));
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunc, NULL, 0, &threadId);
	soundfile[10] = L"..\\Resource\\attack2.wav";
	soundfile[11] = L"..\\Resource\\attack1.wav";
	soundfile[12] = L"..\\Resource\\stunattack.wav";
	soundfile[13] = L"..\\Resource\\heal.wav";
	soundfile[14] = L"..\\Resource\\healattack.wav";
	soundfile[15] = L"..\\Resource\\fireball.wav";
	soundfile[16] = L"..\\Resource\\thunder.wav";

	return TRUE;
}






//播放音乐部分


//


void PlayWavMusic(LPCWSTR file)
{
	PlaySound(file, NULL/*AfxGetInstanceHandle()*/, SND_FILENAME | SND_ASYNC);
}


void PlayMp3Music_1(LPCWSTR file)
{
	mciSendString(file, NULL, 0, 0);
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
MCI_GENERIC_PARMS close;
void PlayMp3Music_3(LPCWSTR file)
{

	gMciOpen.lpstrElementName = file;
	gMciOpen.lpstrDeviceType = NULL;

	gMciPlay.dwCallback = (DWORD)g_pGE->GetWindow();
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&gMciOpen);
	mciSendCommand(gMciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& gMciPlay);


}
void PauseMusic() {
	mciSendCommand(gMciOpen.wDeviceID, MCI_PAUSE, 0, NULL);
}
















DWORD WINAPI ThreadFunc(LPVOID n)
{
		

	while (true)
	if (g_nScene==4)
	while (true)
	{
		
		if (fightstatussign == 6)
		{
			g_pSkill[13]->SetVisible(TRUE);
			g_pSkill[13]->SetGifStatus(TRUE);
			/*actionNow++;
			
			if (actionNow == 11)
			{
				actionNow = 0;
			}*/
			fightstatussign = 0;
		//	while (true)
			//{
			//	if (!g_pSkill[13]->GetGifStatus())
				//{
			Delay(300);
					g_pSkill[13]->SetVisible(FALSE);
					isGIF = FALSE;

					if (actionQueue[actionNow] >= 3)
					{
						fightstatussign = 3;
					}
					//break;
				//}
		//	}
		}
		if (fightstatussign == 5)
		{

				if (actionQueue[actionNow] >= 3)
				{
					fightstatussign = 3;

				}
		}
		if (fightstatussign == 2)
		{
			if (g_pSkill[skillchoosesign] != NULL)
			if (!g_pSkill[skillchoosesign]->GetGifStatus())
			{

				Delay(100);
				g_pSkill[skillchoosesign]->SetVisible(FALSE);
				isGIF = FALSE;

				if (actionQueue[actionNow] >= 3)
				{
					fightstatussign = 3;

				}
			}

		}
		if (fightstatussign == 4)
		{
			if (g_pSkill[skillchoosesign]!=NULL)
			if (!g_pSkill[skillchoosesign]->GetGifStatus())
			{
				Delay(100);
				g_pSkill[skillchoosesign]->SetVisible(FALSE);
			}
			if (!g_pSkill[17]->GetGifStatus())
			{
				Delay(100);
				g_pSkill[17]->SetVisible(FALSE);
				Delay(1000);

				fightstatussign = 3;
				if (actionQueue[actionNow]<3)
				{
					fightstatussign = 2;

				}
			}
		}
		for (int i =3;i<=10;i++)
		{
			if (player[i] != NULL)
			{
				if (player[i]->GetHP() <= 0)
				{
					if (g_DrawObject[i-3]->GetVisible())
					{	
						leftenemy--;
						PlayWavMusic(L"..\\Resource\\death.wav");
					}
					g_DrawObject[i-3]->SetVisible(FALSE);
				}
			}
		}
		for (int i = 0;i<8;i++)
		{
			if (g_DrawObject[i]!=NULL)
			if (!g_DrawObject[i]->GetVisible())
			{
				g_pStatusSign2[i]->SetVisible(FALSE);
				g_pStatusSign3[i]->SetVisible(FALSE);
			}
		}
		if (player[0]!=NULL)
		if (player[0]->GetHP() <= 0)
		{
			g_pStatus[3]->SetVisible(TRUE);
		}
		if (player[1] != NULL)
			if (player[1]->GetHP() <= 0)
			{
				g_pStatus[4]->SetVisible(TRUE);
			}
		if (player[2] != NULL)

			if (player[2]->GetHP() <= 0)
			{
				g_pStatus[5]->SetVisible(TRUE);
			}
		if (leftenemy==0)
		{
			WinTime++;
			leftenemy = 8;
			if (WinTime==4)
			{
				g_bInitScene = FALSE;
				g_DrawObject[0]->SetVisible(FALSE);
				g_DrawObject[1]->SetVisible(FALSE);
				g_DrawObject[2]->SetVisible(FALSE);
				g_DrawObject[3]->SetVisible(FALSE);
				g_DrawObject[4]->SetVisible(FALSE);
				g_DrawObject[5]->SetVisible(FALSE);
				g_DrawObject[6]->SetVisible(FALSE);
				g_DrawObject[7]->SetVisible(FALSE);
				g_pFightIcon[0]->SetVisible(FALSE);
				g_pFightIcon[1]->SetVisible(FALSE);
				g_pFightIcon[2]->SetVisible(FALSE);
				g_pFightIcon[3]->SetVisible(FALSE);
				g_pFightIcon[4]->SetVisible(FALSE);
				g_pFightIcon[5]->SetVisible(FALSE);
				g_pFightIcon[6]->SetVisible(FALSE);

				g_Sprm.Release(FALSE);
				PauseMusic();
				SendMessage(g_pGE->GetWindow(), WM_MUSIC, 0, 0);
				g_nScene = 6;
				InitScene_6(g_pGE->GetWindow());
				break;
			}
			if (WinTime==1)
			{
				g_DrawObject[0]->LoadCxImage(L"..\\Resource\\enemy5.gif");
				g_DrawObject[1]->LoadCxImage(L"..\\Resource\\enemy5.gif");
				g_DrawObject[2]->LoadCxImage(L"..\\Resource\\enemy4.gif");
				g_DrawObject[3]->LoadCxImage(L"..\\Resource\\enemy4.gif");
				g_DrawObject[4]->LoadCxImage(L"..\\Resource\\enemy2.gif");
				g_DrawObject[5]->LoadCxImage(L"..\\Resource\\enemy2.gif");
				g_DrawObject[6]->LoadCxImage(L"..\\Resource\\enemy1.gif");
				g_DrawObject[7]->LoadCxImage(L"..\\Resource\\enemy1.gif");
				g_DrawObject[0]->SetVisible(TRUE);
				g_DrawObject[1]->SetVisible(TRUE);
				g_DrawObject[2]->SetVisible(TRUE);
				g_DrawObject[3]->SetVisible(TRUE);
				g_DrawObject[4]->SetVisible(TRUE);
				g_DrawObject[5]->SetVisible(TRUE);
				g_DrawObject[6]->SetVisible(TRUE);
				g_DrawObject[7]->SetVisible(TRUE);

				player[3] = new Character(L"clown", 1, 1, 1, 5, 5, 1, 3, 3, 3);
				player[4] = new Character(L"clown", 1, 1, 1, 5, 5, 1, 3, 3, 3, 3);
				player[5] = new Character(L"patrol", 1, 1, 1, 6, 10, 3, 3, 3, 3);
				player[6] = new Character(L"patrol", 1, 1, 1, 6, 10, 3, 3, 3, 3);
				player[7] = new Character(L"swordsman", 1, 1, 1, 20, 8, 6, 3, 3, 3);
				player[8] = new Character(L"swordsman", 1, 1, 1, 20, 8, 6, 3, 3, 3, 3);
				player[9] = new Character(L"samurai", 1, 1, 1, 12, 10, 6, 3, 3, 3);
				player[10] = new Character(L"samurai", 1, 1, 1, 12, 10, 6, 3, 3, 3);
			}
			if (WinTime == 2)
			{
				g_DrawObject[0]->LoadCxImage(L"..\\Resource\\enemy4.gif");
				g_DrawObject[1]->LoadCxImage(L"..\\Resource\\enemy4.gif");
				g_DrawObject[2]->LoadCxImage(L"..\\Resource\\enemy4.gif");
				g_DrawObject[3]->LoadCxImage(L"..\\Resource\\enemy4.gif");
				g_DrawObject[4]->LoadCxImage(L"..\\Resource\\enemy1.gif");
				g_DrawObject[5]->LoadCxImage(L"..\\Resource\\enemy1.gif");
				g_DrawObject[6]->LoadCxImage(L"..\\Resource\\enemy1.gif");
				g_DrawObject[7]->LoadCxImage(L"..\\Resource\\enemy3.gif");
				g_DrawObject[0]->SetVisible(TRUE);
				g_DrawObject[1]->SetVisible(TRUE);
				g_DrawObject[2]->SetVisible(TRUE);
				g_DrawObject[3]->SetVisible(TRUE);
				g_DrawObject[4]->SetVisible(TRUE);
				g_DrawObject[5]->SetVisible(TRUE);
				g_DrawObject[6]->SetVisible(TRUE);
				g_DrawObject[7]->SetVisible(TRUE);

				player[3] = new Character(L"enemy1", 1, 1, 1, 6, 10, 3, 3, 3, 3);
				player[4] = new Character(L"enemy2", 1, 1, 1, 6, 10, 3, 3, 3, 3, 3);
				player[5] = new Character(L"enemy3", 1, 1, 1, 6, 10, 3, 3, 3, 3);
				player[6] = new Character(L"enemy4", 1, 1, 1, 6, 10, 3, 3, 3, 3);
				player[7] = new Character(L"enemy1", 1, 1, 1, 12, 10, 6, 3, 3, 3);
				player[8] = new Character(L"enemy2", 1, 1, 1, 12, 10, 6, 3, 3, 3, 3);
				player[9] = new Character(L"enemy3", 1, 1, 1, 12, 10, 6, 3, 3, 3);
				player[10] = new Character(L"enemy4", 1, 1, 1, 15, 3, 8, 3, 3, 3);
			}if (WinTime == 3)
			{
				g_DrawObject[0]->LoadCxImage(L"..\\Resource\\enemy1.gif");
				g_DrawObject[1]->LoadCxImage(L"..\\Resource\\enemy1.gif");
				g_DrawObject[2]->LoadCxImage(L"..\\Resource\\enemy1.gif");
				g_DrawObject[3]->LoadCxImage(L"..\\Resource\\enemy2.gif");
				g_DrawObject[4]->LoadCxImage(L"..\\Resource\\enemy2.gif");
				g_DrawObject[5]->LoadCxImage(L"..\\Resource\\enemy3.gif");
				g_DrawObject[6]->LoadCxImage(L"..\\Resource\\enemy3.gif");
				g_DrawObject[7]->LoadCxImage(L"..\\Resource\\enemy3.gif");
				g_DrawObject[0]->SetVisible(TRUE);
				g_DrawObject[1]->SetVisible(TRUE);
				g_DrawObject[2]->SetVisible(TRUE);
				g_DrawObject[3]->SetVisible(TRUE);
				g_DrawObject[4]->SetVisible(TRUE);
				g_DrawObject[5]->SetVisible(TRUE);
				g_DrawObject[6]->SetVisible(TRUE);
				g_DrawObject[7]->SetVisible(TRUE);

				player[3] = new Character(L"enemy1", 1, 1, 1, 12, 10, 6, 3, 3, 3);
				player[4] = new Character(L"enemy2", 1, 1, 1, 12, 10, 6, 3, 3, 3, 3);
				player[5] = new Character(L"enemy3", 1, 1, 1, 12, 10, 6, 3, 3, 3);
				player[6] = new Character(L"enemy4", 1, 1, 1, 20, 15, 5, 3, 3, 3);
				player[7] = new Character(L"enemy1", 1, 1, 1, 20, 15, 5, 3, 3, 3);
				player[8] = new Character(L"enemy2", 1, 1, 1, 15, 3, 8, 3, 3, 3, 3);
				player[9] = new Character(L"enemy3", 1, 1, 1, 15, 3, 8, 3, 3, 3);
				player[10] = new Character(L"enemy4", 1, 1, 1, 15, 3, 8, 3, 3, 3);
			}
		}
		if (player[0]->GetHP()<=0&&player[1]->GetHP()<=0&& player[2]->GetHP()<=0)
		{
			g_nScene = 5;
			g_bInitScene = FALSE;
			g_DrawObject[0]->SetVisible(FALSE);
			g_DrawObject[1]->SetVisible(FALSE);
			g_DrawObject[2]->SetVisible(FALSE);
			g_DrawObject[3]->SetVisible(FALSE);
			g_DrawObject[4]->SetVisible(FALSE);
			g_DrawObject[5]->SetVisible(FALSE);
			g_DrawObject[6]->SetVisible(FALSE);
			g_DrawObject[7]->SetVisible(FALSE);
			g_pFightIcon[0]->SetVisible(FALSE);
			g_pFightIcon[1]->SetVisible(FALSE);
			g_pFightIcon[2]->SetVisible(FALSE);
			g_pFightIcon[3]->SetVisible(FALSE);
			g_pFightIcon[4]->SetVisible(FALSE);
			g_pFightIcon[5]->SetVisible(FALSE);
			g_pFightIcon[6]->SetVisible(FALSE);

			g_Sprm.Release(FALSE);
			g_nScene = 5;
			PauseMusic();
			SendMessage(g_pGE->GetWindow(), WM_MUSIC, 0, 0);

			InitScene_5(g_pGE->GetWindow());
			break;
		}
	}
	return 0;
}

void GameStart(HWND hWnd)
{
	//long lCur=(long)LoadCursor(g_pG

	g_pLoadScene = new DrawSprite(NULL,L"..\\Resource\\loading.png");
	g_nScene = 1;
	g_bInitScene = FALSE;
	InitScene_1(hWnd);

}

void GameAction(HWND hWnd)
{
	if (g_bInitScene)//判断场景初始化情况
	{
		switch (g_nScene)
		{
		case 1:
			if (PlayScene_1(hWnd))
			{
				g_bInitScene = FALSE;
					InitScene_1(hWnd);
			}
			break;
		case 2:		
			if (PlayScene_2(hWnd))
			{
				g_bInitScene = FALSE;
				InitScene_2(hWnd);
			}
			break;
		case 3:
			if (PlayScene_3(hWnd))
			{
				g_bInitScene = FALSE;
				InitScene_3(hWnd);
			}
			break;
		case 4:
			if (PlayScene_4(hWnd))
			{
				g_bInitScene = FALSE;
				InitScene_4(hWnd);
			}
			break;
		case 5:
			if (PlayScene_5(hWnd))
			{
				g_bInitScene = FALSE;
				InitScene_5(hWnd);
			}
			break;
		case 6:
			if (PlayScene_6(hWnd))
			{
				g_bInitScene = FALSE;
				InitScene_6(hWnd);
			}
			break;
		}

	}

	InvalidateRect(hWnd, NULL, FALSE);
	UpdateWindow(hWnd);
}

BOOL InitScene_1(HWND hWnd)
{


		srand((unsigned)time(NULL));
		int x = Character::RandomDx_y(1, 3);
		switch (x)
		{
		case 1:
			PlayMp3Music_3(L"..\\Resource\\begin1.mp3");
			break;
		case 2:
			PlayMp3Music_3(L"..\\Resource\\begin2.mp3");
			break;
		case 3:
			PlayMp3Music_3(L"..\\Resource\\begin3.mp3");
			break;
		}
	//载入游戏图像
	g_pSprBackGround = new DrawSprite(L"..\\Resource\\startbackground.png");
	g_pMenu = new DrawSprite(L"..\\Resource\\menubackground.png");
	g_pTable = new DrawSprite(L"..\\Resource\\table.png");
	g_pMenuButton1 = new DrawSprite(L"..\\Resource\\menubutton.png");
	g_pMenuButton2 = new DrawSprite(L"..\\Resource\\menubutton.png");
	g_pMenuButton3 = new DrawSprite( L"..\\Resource\\menubutton.png");

	//将精灵添加到精灵管理对象，并设置相应Z顺序
	g_Sprm.AddSprite(g_pSprBackGround, 0);
	g_Sprm.AddSprite(g_pMenu,2);
	g_Sprm.AddSprite(g_pMenuButton1, 3);
	g_Sprm.AddSprite(g_pMenuButton2, 3);
	g_Sprm.AddSprite(g_pMenuButton3, 3);
	g_Sprm.AddSprite(g_pTable, 1);
	//场景状态变量初始化

	g_bInitScene = TRUE;
	return TRUE;
}

BOOL PlayScene_1(HWND hWnd)
{
	//设置精灵对象绘图信息
	g_pTable->SetDrawCxImageInfo(410,400,460,160);
	g_pMenu->SetDrawCxImageInfo(430, 180, 400,  340);
	g_pMenuButton1->SetDrawCxImageDialogInfo(L"Start Game",30,50,0,472, 220,320,80,420,140);
	g_pMenuButton2->SetDrawCxImageDialogInfo(L"Load Game", 30, 50,8,472, 310, 320,80, 420, 140);
	g_pMenuButton3->SetDrawCxImageDialogInfo(L"Exit", 30,50,8,472,400, 320, 80, 420, 140);
	g_pSprBackGround->SetDrawCxImageInfo(0, 0, g_pGE->GetWidth(), g_pGE->GetHeight());


	return FALSE;
}


BOOL InitScene_2(HWND hWnd)
{
	g_pSprBackGround = new DrawSprite(L"..\\Resource\\startbackground.png");
	g_pSetMenu = new DrawSprite(L"..\\Resource\\setmenubg.png");
	g_pSetCharacter[0] = new DrawSprite(L"..\\Resource\\solidman.png");
	g_pSetCharacter[1] = new DrawSprite(L"..\\Resource\\healwoman.png");
	g_pSetCharacter[2] = new DrawSprite(L"..\\Resource\\wizardman.png");
	g_pSetValue[0] = new DrawSprite(L"..\\Resource\\plusandminus.png");
	g_pSetValue[1] = new DrawSprite(L"..\\Resource\\plusandminus.png");
	g_pSetValue[2] = new DrawSprite(L"..\\Resource\\plusandminus.png");
	g_pSetValue[3] = new DrawSprite(L"..\\Resource\\plusandminus.png");
	g_pSetValue[4] = new DrawSprite(L"..\\Resource\\plusandminus.png");
	g_pSetValue[5] = new DrawSprite(L"..\\Resource\\plusandminus.png");
	g_pSetMenuButton = new DrawSprite(L"..\\Resource\\menubutton.png");

	player[0] = new Character(L"StudentPresident", 1, 1, 1, 15,10,20,15, 10, 10, 3,10,0);
	player[1] = new Character(L"Cheerleader", 1, 1, 1, 10, 15, 10,15,10, 20, 2, 10, 0);
	player[2] = new Character(L"ChemistryTeacher", 1, 1, 1, 8, 12, 15,22, 10, 10, 5, 10, 0);
		g_Sprm.AddSprite(g_pSprBackGround,0);
		g_Sprm.AddSprite(g_pSetMenu, 1);
		g_Sprm.AddSprite(g_pSetCharacter[0],2);
		g_Sprm.AddSprite(g_pSetCharacter[1],2);
		g_Sprm.AddSprite(g_pSetCharacter[2],2);
		g_Sprm.AddSprite(g_pSetValue[0], 2);
		g_Sprm.AddSprite(g_pSetValue[1], 2);
		g_Sprm.AddSprite(g_pSetValue[2], 2);
		g_Sprm.AddSprite(g_pSetValue[3], 2);
		g_Sprm.AddSprite(g_pSetValue[4], 2);
		g_Sprm.AddSprite(g_pSetValue[5], 2);
		g_Sprm.AddSprite(g_pSetMenuButton, 2);

		g_bInitScene = TRUE; 
		return TRUE;

}

CString IntToCString(int n)
{
	CString str;
	str.Format(L"%d", n);
	return str;
}



BOOL PlayScene_2(HWND hWnd)
{

	g_pSprBackGround->SetDrawCxImageInfo(0, 0, g_pGE->GetWidth(), g_pGE->GetHeight());
	g_pSetMenu->SetDrawCxImageInfo(400, 80, 460, 560);
	g_pSetCharacter[0]->SetDrawCxImageInfo(465, 150,60,160);
	g_pSetCharacter[1]->SetDrawCxImageInfo(465, 150, 60, 160);
	g_pSetCharacter[2]->SetDrawCxImageInfo(465, 150, 60, 160);
	g_pSetValue[0]->SetDrawCxImageDialogInfo(IntToCString(player[g_nCharacternum]->GetStrength()),10,10,100,720,160,0, 0, 48,20);
	g_pSetValue[1]->SetDrawCxImageDialogInfo(IntToCString(player[g_nCharacternum]->GetDexterity()), 10, 10, 1, 720, 200, 0, 0, 48, 20);
	g_pSetValue[2]->SetDrawCxImageDialogInfo(IntToCString(player[g_nCharacternum]->GetConstitution()), 10, 10, 1, 720, 240, 0, 0, 48, 20);
	g_pSetValue[3]->SetDrawCxImageDialogInfo(IntToCString(player[g_nCharacternum]->GetIntelligence()), 10, 10, 1, 720, 280, 0, 0, 48, 20);
	g_pSetValue[4]->SetDrawCxImageDialogInfo(IntToCString(player[g_nCharacternum]->GetWisdom()), 10, 10, 1, 720, 320, 0, 0, 48, 20);
	g_pSetValue[5]->SetDrawCxImageDialogInfo(IntToCString(player[g_nCharacternum]->GetCharisma()), 10, 10, 1, 720, 360, 0, 0, 48, 20);
	g_pSetMenuButton->SetDrawCxImageDialogInfo(L"Finish", 30, 60, 300, 500,500, 260, 80, 420, 140);
	g_pSetMenuButton->BindChildObject(hWnd, 1,g_pSetMenuButton);
	switch (g_nCharacternum)
	{
	case 0:
		g_pSetCharacter[0]->SetVisible(TRUE);
		g_pSetCharacter[1]->SetVisible(FALSE);
		g_pSetCharacter[2]->SetVisible(FALSE);	
		break;
	case 1:
		g_pSetCharacter[0]->SetVisible(FALSE);
		g_pSetCharacter[1]->SetVisible(TRUE);
		g_pSetCharacter[2]->SetVisible(FALSE);
		break;
	case 2:
		g_pSetCharacter[0]->SetVisible(FALSE);
		g_pSetCharacter[1]->SetVisible(FALSE);
		g_pSetCharacter[2]->SetVisible(TRUE);
		break;
	default:
		break;
	}


	return FALSE;
}

BOOL InitScene_3(HWND hWnd)
{
	srand((unsigned)time(NULL));
	int x = Character::RandomDx_y(1, 2);
	switch (x)
	{
	case 1:
		PlayMp3Music_3(L"..\\Resource\\Scene1.mp3");
		break;
	case 2:
		PlayMp3Music_3(L"..\\Resource\\Scene2.mp3");
		break;

	}
	g_pSprBackGround = new DrawSprite(L"..\\Resource\\scene3bg.png");
	g_bInitScene = TRUE;
	return TRUE;
}

void CheckSysMsg(void)  //监听键盘输入
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if (!GetMessage(&msg, NULL, 0, 0)) return;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


}


void Delay(long time)
{
	static long old_clock, new_clock; //延时变量
	new_clock = old_clock = GetTickCount();
	while (new_clock < old_clock + time)
	{
		new_clock = GetTickCount();
		CheckSysMsg();
	}
}




//
void PrintText(HDC hDC, int x1, int y1, int x2, int y2, LPTSTR text, COLORREF color)  //逐个字符打印函数
{
	SetBkMode(hDC, TRANSPARENT);//设置输出文字背景色为透明
	SetTextColor(hDC, color);
	RECT stRect = { x1,y1,x2,y2 };
	HFONT hfont = CreateFont(20,0,0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"Microsoft YaHei UI"); //创建一种字体
	SelectObject(hDC, hfont); //将字体选入设备环境中
	int i = 0;
	int n = lstrlen(text);
	CString k = text[i];
	do
	{
		CString k = text[i];
		LPTSTR m = (LPTSTR)(LPCTSTR)k;
		DrawText(hDC,m, -1, &stRect, DT_CENTER | DT_VCENTER);
		i++;
		x2 = x2 + 20;
		stRect = { x1,y1,x2,y2 };
		Delay(120);

	} while (i < n);
}
//按下键后松开
void PressKey(DWORD Key, int x)
{
	if (x == 0)
		while (!GetAsyncKeyState(Key))
		{
			CheckSysMsg();
		}
	while (GetAsyncKeyState(Key))
	{
		CheckSysMsg();
	}
}

void GameTitle(HWND hWnd)   //场景三打印字
{
	LPTSTR text1 = L"There was a peaceful school... Until one day..";
	LPTSTR text2 = L"Some Strangers come to this school...";
	LPTSTR text3 = L"These creatures are clawed, Trying to attack students...";
	LPTSTR text4 = L"The chemistry teacher picks up his whip and uses magic to fend off strange creatures...";
	LPTSTR text5 = L"The student President and the Cheerleader also stepped up to ward off those monsters' attack";
	LPTSTR text6 = L"Press Space to Continue...";



	int x1 = 100, y1 = 100, x2 = 115, y2 = 135;
	RECT rect_3;
	rect_3 = { x1,y1,x2,y2 };
	int i = 0;
	int n = lstrlen(text1);
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text1, RGB(255, 255, 255));
	y1 += 25;
	y2 += 25;
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text2, RGB(255, 255, 255));
	y1 += 25;
	y2 += 25;
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text3, RGB(255, 255, 255));
	y1 += 25;
	y2 += 25;
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text4, RGB(255, 255, 255));
	y1 += 25;
	y2 += 25;
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text5, RGB(255, 255, 255));
	y1 += 65;
	y2 += 65;
	Delay(3000);

	PrintText(GetDC(hWnd), x1, y1, x2, y2, text6, RGB(255, 255, 255));
	PressKey(VK_SPACE, 0);
	


	
}
int scene3 = 0;
BOOL PlayScene_3(HWND hWnd)
{

	if (scene3==1)
	{
		GameTitle(hWnd);
		Delay(80);
		PauseMusic();
		g_nScene = 4;
		InitScene_4(hWnd);
	}
	scene3++;
	/*x2 = x2 + 30;
		rect_3 = { x1,y1,x2,y2 };
			g_pSprBackGround->DrawCustomText(GetDC(hWnd),x1,y1,x2,y2,text[i],RGB(255,255,255));
			lasttime = timeGetTime();
			i++;*/


	
	return FALSE;

}


void ActionQueue()
{
	int tmp;
	for(int i =0;i<11;i++)
	{
		for (int j=i+1;j<11;j++)
		{
			if (player[actionQueue[i]]->GetActionNum() < player[actionQueue[j]]->GetActionNum())
			{
				tmp = actionQueue[i];
				actionQueue[i] = actionQueue[j];
				actionQueue[j] = tmp;
			}
		}
	}
}

int ChooseTarget()
{
	int n;
	if (player[0]->GetHP()<=0&&player[1]->GetHP()<=0&&player[2]->GetHP()>0)
	{
		n = 2;
	}
	if (player[0]->GetHP() <= 0 && player[1]->GetHP() > 0 && player[2]->GetHP() <= 0)
	{
		n = 1;
	}if (player[0]->GetHP() > 0 && player[1]->GetHP() <= 0 && player[2]->GetHP() <=0)
	{
		n = 0;
	}if (player[0]->GetHP() <= 0 && player[1]->GetHP() > 0 && player[2]->GetHP() > 0)
	{
		n = Character::RandomDx_y(1,2);
	}
	if (player[0]->GetHP() > 0 && player[1]->GetHP() > 0 && player[2]->GetHP() <= 0)
	{
		n = Character::RandomDx_y(0, 1);
	}
	if (player[0]->GetHP() > 0 && player[1]->GetHP() <= 0 && player[2]->GetHP() > 0)
	{
		if (Character::RandomDx_y(0,1)==1)
		{
			n = 2;
		}
		else
		{
			n = 0;
		}
	}
	if (player[0]->GetHP()> 0 && player[1]->GetHP() > 0 && player[2]->GetHP() > 0)
	{
		n = Character::RandomDx_y(0, 2);
	}
	return n;
}

BOOL InitScene_4(HWND hWnd) {

	leftenemy = 8;

	srand((unsigned)time(NULL));
	int x = Character::RandomDx_y(1, 2);
	switch (x)
	{
	case 1:
		PlayMp3Music_3(L"..\\Resource\\battle1.mp3");
		break;
	case 2:
		PlayMp3Music_3(L"..\\Resource\\battle2.mp3");
		break;

	}

	//载入游戏图像
	g_pSprBackGround = new DrawSprite(L"..\\Resource\\startbackground.png");
	g_pTable = new DrawSprite(L"..\\Resource\\table.png");
	g_pPlayer[0] = new DrawSprite(L"..\\Resource\\bookromback1.png");
	g_pPlayer[1] = new DrawSprite(L"..\\Resource\\lalaback.png");
	g_pPlayer[2] = new DrawSprite(L"..\\Resource\\teacherback1.png");
	g_pChair[0] = new DrawSprite(L"..\\Resource\\chair2.png");
	g_pChair[1] = new DrawSprite(L"..\\Resource\\chair2.png");
	g_pChair[2] = new DrawSprite(L"..\\Resource\\chair2.png");
	g_DrawObject[0] = new DrawSprite(L"..\\Resource\\enemy4.gif");
	g_DrawObject[1] = new DrawSprite(L"..\\Resource\\enemy4.gif");
	g_DrawObject[2] = new DrawSprite(L"..\\Resource\\enemy4.gif");
	g_DrawObject[3] = new DrawSprite(L"..\\Resource\\enemy4.gif");
	g_DrawObject[4] = new DrawSprite(L"..\\Resource\\enemy5.gif");
	g_DrawObject[5] = new DrawSprite(L"..\\Resource\\enemy5.gif");
	g_DrawObject[6] = new DrawSprite(L"..\\Resource\\enemy5.gif");
	g_DrawObject[7] = new DrawSprite(L"..\\Resource\\enemy5.gif");

	g_pStatus[0] = new DrawSprite(L"..\\Resource\\statusbg.png");
	g_pStatus[1] = new DrawSprite(L"..\\Resource\\statusbg.png");
	g_pStatus[2] = new DrawSprite(L"..\\Resource\\statusbg.png");
	g_pStatus[3] = new DrawSprite(L"..\\Resource\\dead.png");
	g_pStatus[4] = new DrawSprite(L"..\\Resource\\dead.png");
	g_pStatus[5] = new DrawSprite(L"..\\Resource\\dead.png");
	g_pFightIcon[0] = new DrawSprite(L"..\\Resource\\attack.png");
	g_pFightIcon[1] = new DrawSprite(L"..\\Resource\\defend2.png");
	g_pFightIcon[2] = new DrawSprite(L"..\\Resource\\stunattack2.png");
	g_pFightIcon[3] = new DrawSprite(L"..\\Resource\\heal2.png");
	g_pFightIcon[4] = new DrawSprite(L"..\\Resource\\healattack2.png");
	g_pFightIcon[5] = new DrawSprite(L"..\\Resource\\fire2.png");
	g_pFightIcon[6] = new DrawSprite(L"..\\Resource\\thunder2.png");
	g_PlayerDialog[0] = new DrawSprite(L"..\\Resource\\dialogframe.png");
	g_PlayerDialog[1] = new DrawSprite(L"..\\Resource\\dialogframe.png");
	g_PlayerDialog[2] = new DrawSprite(L"..\\Resource\\dialogframe.png");
	g_pSkill[10] = new DrawSprite(L"..\\Resource\\attackeffect2.gif");
	g_pSkill[12] = new DrawSprite(L"..\\Resource\\stunattack.gif");
	g_pSkill[13] = new DrawSprite(L"..\\Resource\\heal.gif");
	g_pSkill[14] = new DrawSprite(L"..\\Resource\\healattack.gif");
	g_pSkill[15] = new DrawSprite(L"..\\Resource\\fireball.gif");
	g_pSkill[16] = new DrawSprite(L"..\\Resource\\thunder.gif");
	g_pSkill[17] = new DrawSprite(L"..\\Resource\\attackeffect1.gif");
	g_pSkill[18] = new DrawSprite(L"..\\Resource\\heal.gif");
	g_pSkill[19] = new DrawSprite(L"..\\Resource\\heal.gif");


	g_pStatusSign1[0] = new DrawSprite(L"..\\Resource\\getdefend.png");
	g_pStatusSign1[1] = new DrawSprite(L"..\\Resource\\getdefend.png");
	g_pStatusSign1[2] = new DrawSprite(L"..\\Resource\\getdefend.png");
	g_pStatusSign2[0] = new DrawSprite(L"..\\Resource\\getstun.png");
	g_pStatusSign2[1] = new DrawSprite(L"..\\Resource\\getstun.png");
	g_pStatusSign2[2] = new DrawSprite(L"..\\Resource\\getstun.png");
	g_pStatusSign2[3] = new DrawSprite(L"..\\Resource\\getstun.png");
	g_pStatusSign2[4] = new DrawSprite(L"..\\Resource\\getstun.png");
	g_pStatusSign2[5] = new DrawSprite(L"..\\Resource\\getstun.png");
	g_pStatusSign2[6] = new DrawSprite(L"..\\Resource\\getstun.png");
	g_pStatusSign2[7] = new DrawSprite(L"..\\Resource\\getstun.png");
	g_pStatusSign3[0] = new DrawSprite(L"..\\Resource\\getfire.png");
	g_pStatusSign3[1] = new DrawSprite(L"..\\Resource\\getfire.png");
	g_pStatusSign3[2] = new DrawSprite(L"..\\Resource\\getfire.png");
	g_pStatusSign3[3] = new DrawSprite(L"..\\Resource\\getfire.png");
	g_pStatusSign3[4] = new DrawSprite(L"..\\Resource\\getfire.png");
	g_pStatusSign3[5] = new DrawSprite(L"..\\Resource\\getfire.png");
	g_pStatusSign3[6] = new DrawSprite(L"..\\Resource\\getfire.png");
	g_pStatusSign3[7] = new DrawSprite(L"..\\Resource\\getfire.png");

	g_pShowHp[0] = new DrawSprite(L"..\\Resource\\hp.png");
	g_pShowHp[1] = new DrawSprite(L"..\\Resource\\hp.png");
	g_pShowHp[2] = new DrawSprite(L"..\\Resource\\hp.png");
	g_pShowMp[0] = new DrawSprite(L"..\\Resource\\mp.png");
	g_pShowMp[1] = new DrawSprite(L"..\\Resource\\mp.png");
	g_pShowMp[2] = new DrawSprite(L"..\\Resource\\mp.png");
	srand((unsigned)time(NULL));



	player[3] = new Character(L"enemy1", 1, 1, 1, 6, 10,2 , 3, 3, 3);
	player[4] = new Character(L"enemy2", 1, 1, 1, 6,10 ,2, 3, 3, 3, 3);
	player[5] = new Character(L"enemy3", 1, 1, 1, 6, 10, 2, 3, 3, 3);
	player[6] = new Character(L"enemy4", 1, 1, 1, 6, 10, 2, 3, 3, 3);
	player[7] = new Character(L"enemy1", 1, 1, 1, 5, 5, 1, 3, 3, 3);
	player[8] = new Character(L"enemy2", 1, 1, 1, 5, 5, 1, 3, 3, 3, 3);
	player[9] = new Character(L"enemy3", 1, 1, 1, 5, 5, 1, 3, 3, 3);
	player[10] = new Character(L"enemy4", 1, 1, 1, 5, 5, 1, 3, 3, 3);
	
	ActionQueue();
	//MessageBox(g_pGE->GetWindow(), IntToCString(actionQueue[0])+ IntToCString(actionQueue[1]) 
	//	+ IntToCString(actionQueue[2]) + IntToCString(actionQueue[3]) 
	//	+ IntToCString(actionQueue[4]) + IntToCString(actionQueue[5])
	//	+ IntToCString(actionQueue[7]) + IntToCString(actionQueue[8])
	//	+ IntToCString(actionQueue[9]) + IntToCString(actionQueue[10])  , L"提醒", MB_OK | MB_DEFBUTTON2 | MB_ICONASTERISK);


	//将精灵添加到精灵管理对象，并设置相应Z顺序
	g_Sprm.AddSprite(g_pSprBackGround, 0);
	g_Sprm.AddSprite(g_pTable, 1);
	g_Sprm.AddSprite(g_pChair[0], 3);
	g_Sprm.AddSprite(g_pChair[1], 3);
	g_Sprm.AddSprite(g_pChair[2], 3);
	g_Sprm.AddSprite(g_pPlayer[0], 2);
	g_Sprm.AddSprite(g_pPlayer[1], 2);
	g_Sprm.AddSprite(g_pPlayer[2], 2);
	g_Sprm.AddSprite(g_DrawObject[0], 2);
	g_Sprm.AddSprite(g_DrawObject[1], 2);
	g_Sprm.AddSprite(g_DrawObject[2], 2);
	g_Sprm.AddSprite(g_DrawObject[3], 2);
	g_Sprm.AddSprite(g_DrawObject[4], 2);
	g_Sprm.AddSprite(g_DrawObject[5], 2);
	g_Sprm.AddSprite(g_DrawObject[6], 2);
	g_Sprm.AddSprite(g_DrawObject[7], 2);
	g_Sprm.AddSprite(g_pStatus[0], 4);
	g_Sprm.AddSprite(g_pStatus[1], 4);
	g_Sprm.AddSprite(g_pStatus[2], 4);
	g_Sprm.AddSprite(g_pStatus[3], 6);
	g_Sprm.AddSprite(g_pStatus[4], 6);
	g_Sprm.AddSprite(g_pStatus[5], 6);
	g_Sprm.AddSprite(g_pFightIcon[0], 3);
	g_Sprm.AddSprite(g_pFightIcon[1], 3);
	g_Sprm.AddSprite(g_pFightIcon[2], 3);
	g_Sprm.AddSprite(g_pFightIcon[3], 3);
	g_Sprm.AddSprite(g_pFightIcon[4], 3);
	g_Sprm.AddSprite(g_pFightIcon[5], 3);
	g_Sprm.AddSprite(g_pFightIcon[6], 3);
	g_Sprm.AddSprite(g_PlayerDialog[0], 5);
	g_Sprm.AddSprite(g_PlayerDialog[1], 5);
	g_Sprm.AddSprite(g_PlayerDialog[2], 5);
	g_Sprm.AddSprite(g_pSkill[10], 6);
	g_Sprm.AddSprite(g_pSkill[12], 6);
	g_Sprm.AddSprite(g_pSkill[13], 6);
	g_Sprm.AddSprite(g_pSkill[14], 6);
	g_Sprm.AddSprite(g_pSkill[15], 6);
	g_Sprm.AddSprite(g_pSkill[16], 6);
	g_Sprm.AddSprite(g_pSkill[17], 6);
	g_Sprm.AddSprite(g_pSkill[18], 6);
	g_Sprm.AddSprite(g_pSkill[19], 6);

	g_Sprm.AddSprite(g_pStatusSign1[0], 7);
	g_Sprm.AddSprite(g_pStatusSign1[1], 7);
	g_Sprm.AddSprite(g_pStatusSign1[2], 7);
	g_Sprm.AddSprite(g_pStatusSign2[0], 7);
	g_Sprm.AddSprite(g_pStatusSign2[1], 7);
	g_Sprm.AddSprite(g_pStatusSign2[2], 7);
	g_Sprm.AddSprite(g_pStatusSign2[3], 7);
	g_Sprm.AddSprite(g_pStatusSign2[4], 7);
	g_Sprm.AddSprite(g_pStatusSign2[5], 7);
	g_Sprm.AddSprite(g_pStatusSign2[6], 7);
	g_Sprm.AddSprite(g_pStatusSign2[7], 7);
	g_Sprm.AddSprite(g_pStatusSign3[0], 7);
	g_Sprm.AddSprite(g_pStatusSign3[1], 7);
	g_Sprm.AddSprite(g_pStatusSign3[2], 7);
	g_Sprm.AddSprite(g_pStatusSign3[3], 7);
	g_Sprm.AddSprite(g_pStatusSign3[4], 7);
	g_Sprm.AddSprite(g_pStatusSign3[5], 7);
	g_Sprm.AddSprite(g_pStatusSign3[6], 7);
	g_Sprm.AddSprite(g_pStatusSign3[7], 7);

	g_Sprm.AddSprite(g_pShowHp[0], 5);
	g_Sprm.AddSprite(g_pShowHp[1], 5);
	g_Sprm.AddSprite(g_pShowHp[2], 5);

	g_Sprm.AddSprite(g_pShowMp[0], 5);
	g_Sprm.AddSprite(g_pShowMp[1], 5);
	g_Sprm.AddSprite(g_pShowMp[2], 5);

	g_pSkill[10]->SetVisible(FALSE);
	g_pSkill[12]->SetVisible(FALSE);
	g_pSkill[13]->SetVisible(FALSE);
	g_pSkill[14]->SetVisible(FALSE);
	g_pSkill[15]->SetVisible(FALSE);
	g_pSkill[16]->SetVisible(FALSE);
	g_pSkill[17]->SetVisible(FALSE);
	g_pStatus[3]->SetVisible(FALSE);
	g_pStatus[4]->SetVisible(FALSE);
	g_pStatus[5]->SetVisible(FALSE);
	g_pStatusSign1[0]->SetVisible(FALSE);
	g_pStatusSign1[1]->SetVisible(FALSE);
	g_pStatusSign1[2]->SetVisible(FALSE);
	g_pStatusSign2[0]->SetVisible(FALSE);
	g_pStatusSign2[1]->SetVisible(FALSE);
	g_pStatusSign2[2]->SetVisible(FALSE);
	g_pStatusSign2[3]->SetVisible(FALSE);
	g_pStatusSign2[4]->SetVisible(FALSE);
	g_pStatusSign2[5]->SetVisible(FALSE);
	g_pStatusSign2[6]->SetVisible(FALSE);
	g_pStatusSign2[7]->SetVisible(FALSE);
	g_pStatusSign3[0]->SetVisible(FALSE);
	g_pStatusSign3[1]->SetVisible(FALSE);
	g_pStatusSign3[2]->SetVisible(FALSE);
	g_pStatusSign3[3]->SetVisible(FALSE);
	g_pStatusSign3[4]->SetVisible(FALSE);
	g_pStatusSign3[5]->SetVisible(FALSE);
	g_pStatusSign3[6]->SetVisible(FALSE);
	g_pStatusSign3[7]->SetVisible(FALSE);

	g_bInitScene = TRUE;
	return TRUE;
}

int PerCal(int x,int y)
{
	int n;
	double m = (double)x /(double) y;
	if (m==0)
	{
		n = 0;
	}
	if (0<m && m<0.04)
	{
		n = 2;
	}
	if (0.04<=m && m<0.08)
	{
		n = 4;
	}
	if (0.08 <= m  && m< 0.12)
	{
		n = 6;
	}if (0.12 <= m  && m< 0.16)
	{
		n = 8;
	}if (0.16 <= m  && m< 0.20)
	{
		n = 10;
	}if (0.20 <= m  && m< 0.24)
	{
		n = 12;
	}if (0.24 <= m  && m< 0.28)
	{
		n = 14;
	}if (0.28 <= m  && m< 0.32)
	{
		n = 16;
	}if (0.32 <= m  && m< 0.36)
	{
		n = 18;
	}if (0.36 <= m  && m< 0.40)
	{
		n = 20;
	}if (0.40 <= m  && m< 0.44)
	{
		n = 22;
	}if (0.44 <= m  && m< 0.48)
	{
		n = 24;
	}if (0.48 <= m  && m< 0.52)
	{
		n = 26;
	}if (0.52 <= m  && m< 0.56)
	{
		n = 28;
	}if (0.56 <= m  && m< 0.60)
	{
		n = 30;
	}if (0.60 <= m  && m< 0.64)
	{
		n = 32;
	}if (0.64 <= m  && m< 0.68)
	{
		n = 34;
	}if (0.68 <= m  && m< 0.72)
	{
		n = 36;
	}if (0.72 <= m  && m< 0.76)
	{
		n = 38;
	}if (0.76 <= m  && m< 0.80)
	{
		n = 40;
	}if (0.80 <= m  && m< 0.84)
	{
		n = 42;
	}if (0.84 <= m  && m< 0.88)
	{
		n = 44;
	}if (0.88 <= m  && m< 0.92)
	{
		n = 46;
	}if (0.92 <= m  && m< 0.96)
	{
		n = 48;
	}if (0.96 <= m  && m<= 1)
	{
		n = 50;
	}
	if (m<0)
	{
		n = 0;
	}
	return n;
}

void Scene4Dialog(HWND hWnd)
{
	LPTSTR text1 = L"这些东西到底是什么来头？";
	LPTSTR text2 = L"不知道，可不知道总觉得他们的样子有些似曾相识..";
	LPTSTR text3 = L"不要让他们伤害同学们，先击败他们！";




	int x1 = 100, y1 = 100, x2 = 115, y2 = 135;
	RECT rect_3;
	rect_3 = { x1,y1,x2,y2 };
	int i = 0;
	int n = lstrlen(text1);
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text1, RGB(255, 255, 255));
	y1 += 25;
	y2 += 25;

	PressKey(VK_LBUTTON, 0);
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text2, RGB(255, 255, 255));
	y1 += 25;
	y2 += 25;

	PressKey(VK_LBUTTON, 0);
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text3, RGB(255, 255, 255));
	y1 += 25;
	y2 += 25;

	PressKey(VK_LBUTTON, 0);



}

BOOL PlayScene_4(HWND hWnd)
{//设置精灵对象绘图信息
	g_pTable->SetDrawCxImageInfo(410, 400, 460, 160);
	g_pSprBackGround->SetDrawCxImageInfo(0, 0, g_pGE->GetWidth(), g_pGE->GetHeight());
	g_pChair[0]->SetDrawCxImageInfo(460, 500,66,76);
	g_pChair[1]->SetDrawCxImageInfo(600, 500, 66, 76);
	g_pChair[2]->SetDrawCxImageInfo(740, 500, 66, 76);
	g_pPlayer[0]->SetDrawCxImageInfo(458, 415,70,90);
	g_pPlayer[1]->SetDrawCxImageInfo(597, 420,70,90);
	g_pPlayer[2]->SetDrawCxImageInfo(737,416,70,90);
	g_DrawObject[0]->SetDrawCxImageInfo(420, 130,85,100,500);
	g_DrawObject[1]->SetDrawCxImageInfo(540, 130, 85, 100,500);
	g_DrawObject[2]->SetDrawCxImageInfo(660, 130, 85, 100,500);
	g_DrawObject[3]->SetDrawCxImageInfo(780, 130, 85, 100,500);
	g_DrawObject[4]->SetDrawCxImageInfo(380, 240,85,100,500);	
	g_DrawObject[5]->SetDrawCxImageInfo(500, 240,85,100,500);
	g_DrawObject[6]->SetDrawCxImageInfo(620, 240,90,100,500);
	g_DrawObject[7]->SetDrawCxImageInfo(740, 240,85,100,500);
	g_pStatus[0]->SetDrawCxImageInfo(462, 525, 60, 75);
	//g_pStatus[0]->MergerImage(PerCal(player[0]->GetHP(),player[0]->GetMaxHP()), PerCal(player[0]->GetMP(), player[0]->GetMaxMP()),player[0]->GetLevel());
	g_pStatus[1]->SetDrawCxImageInfo(602, 525, 60, 75);
	//g_pStatus[1]->MergerImage(PerCal(player[1]->GetHP(), player[1]->GetMaxHP()), PerCal(player[1]->GetMP(), player[1]->GetMaxMP()), player[1]->GetLevel());
	g_pStatus[2]->SetDrawCxImageInfo(742, 525, 60, 75);
//	g_pStatus[2]->MergerImage(PerCal(player[2]->GetHP(), player[2]->GetMaxHP()), PerCal(player[2]->GetMP(), player[2]->GetMaxMP()), player[2]->GetLevel());
	g_pShowHp[0]->SetDrawCxImageInfo(467, 560, PerCal(player[0]->GetHP(), player[0]->GetMaxHP()), 14);
	g_pShowHp[1]->SetDrawCxImageInfo(607, 560, PerCal(player[1]->GetHP(), player[1]->GetMaxHP()), 14);
	g_pShowHp[2]->SetDrawCxImageInfo(747, 560, PerCal(player[2]->GetHP(), player[2]->GetMaxHP()), 14);
	g_pShowMp[0]->SetDrawCxImageInfo(467, 578, PerCal(player[0]->GetMP(), player[0]->GetMaxMP()), 14);
	g_pShowMp[1]->SetDrawCxImageInfo(607, 578, PerCal(player[1]->GetMP(), player[1]->GetMaxMP()), 14);
	g_pShowMp[2]->SetDrawCxImageInfo(747, 578, PerCal(player[2]->GetMP(), player[2]->GetMaxMP()), 14);

	g_pStatus[3]->SetDrawCxImageInfo(462, 525, 60, 75);
	g_pStatus[4]->SetDrawCxImageInfo(602, 525, 60, 75);
	g_pStatus[5]->SetDrawCxImageInfo(742, 525, 60, 75);	
	g_DrawObject[0]->BindChildObject(hWnd, 2,g_DrawObject[0]);
	g_DrawObject[1]->BindChildObject(hWnd, 3,g_DrawObject[1]);
	g_DrawObject[2]->BindChildObject(hWnd, 4,g_DrawObject[2]);
	g_DrawObject[3]->BindChildObject(hWnd, 5,g_DrawObject[3]);
	g_DrawObject[4]->BindChildObject(hWnd, 6,g_DrawObject[4]);
	g_DrawObject[5]->BindChildObject(hWnd, 7, g_DrawObject[5]);
	g_DrawObject[6]->BindChildObject(hWnd, 8, g_DrawObject[6]);
	g_DrawObject[7]->BindChildObject(hWnd, 9, g_DrawObject[7]);

	g_pFightIcon[0]->SetDrawCxImageInfo(470, 620, 36, 31);
	g_pFightIcon[1]->SetDrawCxImageInfo(570, 620, 36, 31);
	g_pFightIcon[2]->SetDrawCxImageInfo(670, 620, 36, 31);
	g_pFightIcon[3]->SetDrawCxImageInfo(670, 620, 36, 31);
	g_pFightIcon[4]->SetDrawCxImageInfo(770, 620, 36, 31);
	g_pFightIcon[5]->SetDrawCxImageInfo(670, 620, 36, 31);
	g_pFightIcon[6]->SetDrawCxImageInfo(770, 620, 36, 31);
	g_pFightIcon[0]->BindChildObject(hWnd, 10, g_pFightIcon[0]);
	g_pFightIcon[1]->BindChildObject(hWnd, 11, g_pFightIcon[1]);
	g_pFightIcon[2]->BindChildObject(hWnd, 12, g_pFightIcon[2]);
	g_pFightIcon[3]->BindChildObject(hWnd, 13, g_pFightIcon[3]);
	g_pFightIcon[4]->BindChildObject(hWnd, 14, g_pFightIcon[4]);
	g_pFightIcon[5]->BindChildObject(hWnd, 15, g_pFightIcon[5]);
	g_pFightIcon[6]->BindChildObject(hWnd, 16, g_pFightIcon[6]);

	g_pStatusSign1[0]->SetDrawCxImageInfo(458, 415, 30, 30);
	g_pStatusSign1[1]->SetDrawCxImageInfo(597, 415, 30, 30);
	g_pStatusSign1[2]->SetDrawCxImageInfo(737, 415, 30, 30);
	g_pStatusSign2[0]->SetDrawCxImageInfo(420, 120, 30, 30);
	g_pStatusSign2[1]->SetDrawCxImageInfo(540, 120, 30, 30);
	g_pStatusSign2[2]->SetDrawCxImageInfo(660, 120, 30, 30);
	g_pStatusSign2[3]->SetDrawCxImageInfo(780, 120, 30, 30);
	g_pStatusSign2[4]->SetDrawCxImageInfo(380, 230, 30, 30);
	g_pStatusSign2[5]->SetDrawCxImageInfo(500, 230, 30, 30);
	g_pStatusSign2[6]->SetDrawCxImageInfo(620, 230, 30, 30);
	g_pStatusSign2[7]->SetDrawCxImageInfo(740, 230, 30, 30);
	g_pStatusSign3[0]->SetDrawCxImageInfo(455, 120, 30, 30);
	g_pStatusSign3[1]->SetDrawCxImageInfo(575, 120, 30, 30);
	g_pStatusSign3[2]->SetDrawCxImageInfo(695, 120, 30, 30);
	g_pStatusSign3[3]->SetDrawCxImageInfo(815, 120, 30, 30);
	g_pStatusSign3[4]->SetDrawCxImageInfo(415, 230, 30, 30);
	g_pStatusSign3[5]->SetDrawCxImageInfo(535, 230, 30, 30);
	g_pStatusSign3[6]->SetDrawCxImageInfo(655, 230, 30, 30);
	g_pStatusSign3[7]->SetDrawCxImageInfo(775, 230, 30, 30);
	
	for (int i =10;i<16;i++)
	{
		if (g_pSkill[skillchoosesign]!=NULL)
			if (g_pSkill[skillchoosesign]->GetGifStatus())
		{
				isGIF = TRUE;
		}
	}
	if (isGIF)
	{
		g_pFightIcon[0]->SetVisible(FALSE);
		g_pFightIcon[1]->SetVisible(FALSE);
		g_pFightIcon[2]->SetVisible(FALSE);
		g_pFightIcon[3]->SetVisible(FALSE);
		g_pFightIcon[4]->SetVisible(FALSE);
		g_pFightIcon[5]->SetVisible(FALSE);
		g_pFightIcon[6]->SetVisible(FALSE);
		if (skillchoosesign!=13)
		fightstatussign = 2;
		else
		{
			fightstatussign = 6;
		}
	}
	else
	switch (actionQueue[actionNow])
	{
	case 0:
		if (player[0]->GetHP() > 0)
		{

			g_pFightIcon[0]->SetVisible(TRUE);
			g_pFightIcon[1]->SetVisible(TRUE);
			g_pFightIcon[2]->SetVisible(TRUE);
			g_pFightIcon[3]->SetVisible(FALSE);
			g_pFightIcon[4]->SetVisible(FALSE);
			g_pFightIcon[5]->SetVisible(FALSE);
			g_pFightIcon[6]->SetVisible(FALSE);
			if (playermessagesentsign == 1)
			{
			
			playermessagesentsign = 0;
			SendMessage(hWnd, WM_FIGHT1, 0, 0);

		}
			break;
		}
		else
		{
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}			break;
		}
	case 1:
		if (player[1]->GetHP() > 0)
		{

			g_pFightIcon[1]->SetVisible(TRUE);
			g_pFightIcon[0]->SetVisible(TRUE);
			g_pFightIcon[2]->SetVisible(FALSE);
			g_pFightIcon[3]->SetVisible(TRUE);
			g_pFightIcon[4]->SetVisible(TRUE);
			g_pFightIcon[5]->SetVisible(FALSE);
			g_pFightIcon[6]->SetVisible(FALSE);
			if (playermessagesentsign == 1)
			{
				playermessagesentsign = 0;
				SendMessage(hWnd, WM_FIGHT1, 1, 0);

			}
			break;
		}
		else
		{
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}			break;
		}
	case 2:
		if (player[2]->GetHP() > 0) {
			g_pFightIcon[1]->SetVisible(TRUE);
			g_pFightIcon[0]->SetVisible(TRUE);
			g_pFightIcon[2]->SetVisible(FALSE);
			g_pFightIcon[3]->SetVisible(FALSE);
			g_pFightIcon[4]->SetVisible(FALSE);
			g_pFightIcon[5]->SetVisible(TRUE);
			g_pFightIcon[6]->SetVisible(TRUE);
			if (playermessagesentsign == 1)
			{
				playermessagesentsign = 0;
				SendMessage(hWnd, WM_FIGHT1, 2, 0);

			}
			break;
		}
		else
		{
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}			break;
		}
	case 3:
		if (player[3]->GetHP() > 0)
		{
			g_pFightIcon[0]->SetVisible(FALSE);
			g_pFightIcon[1]->SetVisible(FALSE);
			g_pFightIcon[2]->SetVisible(FALSE);
			g_pFightIcon[3]->SetVisible(FALSE);
			g_pFightIcon[4]->SetVisible(FALSE);
			g_pFightIcon[5]->SetVisible(FALSE);
			g_pFightIcon[6]->SetVisible(FALSE);
			//fightstatussign = 3;
			SendMessage(hWnd, WM_FIGHT1, 3, Character::RandomDx_y(1, 3));
			break;
		}
		else
		{
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}			break;
		}
	case 4:
		if (player[4]->GetHP() > 0)
		{
			g_pFightIcon[0]->SetVisible(FALSE);
			g_pFightIcon[1]->SetVisible(FALSE);
			g_pFightIcon[2]->SetVisible(FALSE);
			g_pFightIcon[3]->SetVisible(FALSE);
			g_pFightIcon[4]->SetVisible(FALSE);
			g_pFightIcon[5]->SetVisible(FALSE);
			g_pFightIcon[6]->SetVisible(FALSE);

			//	skillchoosesign = 17;
			SendMessage(hWnd, WM_FIGHT1, 4, Character::RandomDx_y(1, 3));
			break;
		}
		else
		{
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}			break;
		}
	case 5:
		if (player[5]->GetHP() > 0)
		{
			g_pFightIcon[0]->SetVisible(FALSE);
			g_pFightIcon[1]->SetVisible(FALSE);
			g_pFightIcon[2]->SetVisible(FALSE);
			g_pFightIcon[3]->SetVisible(FALSE);
			g_pFightIcon[4]->SetVisible(FALSE);
			g_pFightIcon[5]->SetVisible(FALSE);
			g_pFightIcon[6]->SetVisible(FALSE);
			//	skillchoosesign = 17;
			SendMessage(hWnd, WM_FIGHT1, 5, Character::RandomDx_y(1, 3));
			break;
		}
		else
		{
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}			break;
		}
	case 6:
		if (player[6]->GetHP() > 0)
		{

			g_pFightIcon[0]->SetVisible(FALSE);
			g_pFightIcon[1]->SetVisible(FALSE);
			g_pFightIcon[2]->SetVisible(FALSE);
			g_pFightIcon[3]->SetVisible(FALSE);
			g_pFightIcon[4]->SetVisible(FALSE);
			g_pFightIcon[5]->SetVisible(FALSE);
			g_pFightIcon[6]->SetVisible(FALSE);

			//		skillchoosesign = 17;
			SendMessage(hWnd, WM_FIGHT1, 6, Character::RandomDx_y(1, 3));
			break;
		}
		else
		{
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}			break;
		}
	case 7:
		if (player[7]->GetHP() > 0)
		{
			g_pFightIcon[0]->SetVisible(FALSE);
			g_pFightIcon[1]->SetVisible(FALSE);
			g_pFightIcon[2]->SetVisible(FALSE);
			g_pFightIcon[3]->SetVisible(FALSE);
			g_pFightIcon[4]->SetVisible(FALSE);
			g_pFightIcon[5]->SetVisible(FALSE);
			g_pFightIcon[6]->SetVisible(FALSE);
			//skillchoosesign = 17;
			SendMessage(hWnd, WM_FIGHT1, 7, Character::RandomDx_y(1, 3));
			break;
		}
		else
		{
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}			break;
		}
	case 8:
		if (player[8]->GetHP() > 0)
		{
			g_pFightIcon[0]->SetVisible(FALSE);
			g_pFightIcon[1]->SetVisible(FALSE);
			g_pFightIcon[2]->SetVisible(FALSE);
			g_pFightIcon[3]->SetVisible(FALSE);
			g_pFightIcon[4]->SetVisible(FALSE);
			g_pFightIcon[5]->SetVisible(FALSE);
			g_pFightIcon[6]->SetVisible(FALSE);
			//		skillchoosesign = 17;
			SendMessage(hWnd, WM_FIGHT1, 8, Character::RandomDx_y(1, 3));
			break;
		}
		else
		{
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}			break;
		}
	case 9:
		if (player[9]->GetHP() > 0)
		{

			g_pFightIcon[0]->SetVisible(FALSE);
			g_pFightIcon[1]->SetVisible(FALSE);
			g_pFightIcon[2]->SetVisible(FALSE);
			g_pFightIcon[3]->SetVisible(FALSE);
			g_pFightIcon[4]->SetVisible(FALSE);
			g_pFightIcon[5]->SetVisible(FALSE);
			g_pFightIcon[6]->SetVisible(FALSE);
			//		skillchoosesign = 17;
			SendMessage(hWnd, WM_FIGHT1, 9, Character::RandomDx_y(1, 3));
			break;
		}
		else
		{
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}			break;
		}
	case 10:
		if (player[10]->GetHP() > 0)
		{
			g_pFightIcon[0]->SetVisible(FALSE);
			g_pFightIcon[1]->SetVisible(FALSE);
			g_pFightIcon[2]->SetVisible(FALSE);
			g_pFightIcon[3]->SetVisible(FALSE);
			g_pFightIcon[4]->SetVisible(FALSE);
			g_pFightIcon[5]->SetVisible(FALSE);
			g_pFightIcon[6]->SetVisible(FALSE);
			//	skillchoosesign = 17;
			SendMessage(hWnd, WM_FIGHT1, 10, Character::RandomDx_y(1, 3));
			break;
		}
		else
		{
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}			break;
		}
	}




	return FALSE;
}

BOOL InitScene_5(HWND hWnd)
{
	srand((unsigned)time(NULL));
	int x = Character::RandomDx_y(1, 2);
	switch (x)
	{
	case 1:
		PlayMp3Music_3(L"..\\Resource\\lose1.mp3");
		break;
	case 2:
		PlayMp3Music_3(L"..\\Resource\\lose2.mp3");
		break;

	}
	g_pSprBackGround = new DrawSprite(L"..\\Resource\\scene3bg.png");

	g_bInitScene = TRUE;
	return TRUE;
}

void Game5Lose(HWND hWnd)   //场景五打印字
{
	LPTSTR text1 = L"You are defeated by monsters";
	LPTSTR text2 = L"The whole school fall into a panic..";
	LPTSTR text3 = L"Try again ! Beat those monsters!";
	LPTSTR text4 = L"Press Space to Exit";



	int x1 = 100, y1 = 100, x2 = 115, y2 = 135;
	RECT rect_3;
	rect_3 = { x1,y1,x2,y2 };
	int i = 0;
	int n = lstrlen(text1);
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text1, RGB(255, 255, 255));
	y1 += 25;
	y2 += 25;
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text2, RGB(255, 255, 255));
	y1 += 25;
	y2 += 25;
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text3, RGB(255, 255, 255));
	y1 += 65;
	y2 += 65;
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text4, RGB(255, 255, 255));
	PressKey(VK_SPACE, 0);




}


int scene5 = 0;

BOOL PlayScene_5(HWND hWnd)
{


		if (scene5 == 1)
		{
			Game5Lose(hWnd);
			Delay(80);
			SendMessage(hWnd, WM_DESTROY, 0, 0);
		}
		scene5++;





	return FALSE;
}

BOOL InitScene_6(HWND hWnd)
{

	srand((unsigned)time(NULL));
	int x = Character::RandomDx_y(1, 2);
	switch (x)
	{
	case 1:
		PlayMp3Music_3(L"..\\Resource\\win1.mp3");
		break;
	case 2:
		PlayMp3Music_3(L"..\\Resource\\win2.mp3");
		break;

	}
	g_pSprBackGround = new DrawSprite(L"..\\Resource\\scene3bg.png");

	g_bInitScene = TRUE;
	return TRUE;
}

void Game6Win(HWND hWnd)   //场景五打印字
{
	LPTSTR text1 = L"You beat those monsters!";
	LPTSTR text2 = L"You are the hero of the school";
	LPTSTR text3 = L"Press Space to Exit";

	int x1 = 100, y1 = 100, x2 = 115, y2 = 135;
	RECT rect_3;
	rect_3 = { x1,y1,x2,y2 };
	int i = 0;
	int n = lstrlen(text1);
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text1, RGB(255, 255, 255));
	y1 += 25;
	y2 += 25;
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text2, RGB(255, 255, 255));

	y1 += 65;
	y2 += 65;
	PrintText(GetDC(hWnd), x1, y1, x2, y2, text3, RGB(255, 255, 255));
	PressKey(VK_SPACE, 0);




}


int scene6 = 0;

BOOL PlayScene_6(HWND hWnd)
{


	if (scene6 == 1)
	{
		Game6Win(hWnd);
		Delay(80);
		SendMessage(hWnd, WM_DESTROY, 0, 0);
	}
	scene6++;





	return FALSE;
}


VOID GamePaint(HDC hDC, LPARAM lParam)
{
	if (!g_bInitScene)
	{
		g_pLoadScene->Draw(hDC,0,0);
	}
	else
	{
		g_Sprm.Draw(hDC);

	}

		SetBkMode(hDC, TRANSPARENT);//设置输出文字背景色为透明
		SetTextColor(hDC, RGB(0,0,0));
		HFONT hfont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"Microsoft YaHei UI"); //创建一种字体
		SelectObject(hDC, hfont); //将字体选入设备环境中

	if (g_nScene == 2)
	{
		TextOut(hDC, 450, 320,player[g_nCharacternum]->GetName(),wcslen(player[g_nCharacternum]->GetName()));
		TextOut(hDC, 600, 165, L"Strength",wcslen(L"Strength"));
		TextOut(hDC, 600, 205,  L"Dexterity",wcslen(L"Dexterity"));
		TextOut(hDC, 600, 245, L"Constitution",wcslen(L"Constitution"));
		TextOut(hDC, 600, 285, L"Intelligence",wcslen(L"Intelligence"));
		TextOut(hDC, 600, 325, L"Wisdom",wcslen(L"Wisdom"));
		TextOut(hDC, 600, 365, L"Charisma",wcslen(L"Charisma"));
		TextOut(hDC, 600, 405,  L"Attributes",wcslen(L"Attributes"));
		TextOut(hDC, 760, 408,  IntToCString(player[g_nCharacternum]->GetAttributes()),wcslen(IntToCString(player[g_nCharacternum]->GetAttributes())));
	}
	if (g_nScene == 4)
	{
		if (player[0]->GetHP() > 0)
		{

			TextOut(hDC, 470, 555, IntToCString(player[0]->GetHP()) + "/" + IntToCString(player[0]->GetMaxHP()), wcslen(IntToCString(player[0]->GetHP()) + "/" + IntToCString(player[0]->GetMaxHP())));
			TextOut(hDC, 470, 575, IntToCString(player[0]->GetMP()) + "/" + IntToCString(player[0]->GetMaxMP()), wcslen(IntToCString(player[0]->GetMP()) + "/" + IntToCString(player[0]->GetMaxMP())));
		}
		if (player[1]->GetHP() > 0)
		{
			TextOut(hDC, 610, 555, IntToCString(player[1]->GetHP()) + "/" + IntToCString(player[1]->GetMaxHP()), wcslen(IntToCString(player[1]->GetHP()) + "/" + IntToCString(player[0]->GetMaxHP())));
			TextOut(hDC, 610, 575, IntToCString(player[1]->GetMP()) + "/" + IntToCString(player[1]->GetMaxMP()), wcslen(IntToCString(player[1]->GetMP()) + "/" + IntToCString(player[0]->GetMaxMP())));
		}
		if (player[2]->GetHP() > 0)
		{
			TextOut(hDC, 750, 555, IntToCString(player[2]->GetHP()) + "/" + IntToCString(player[2]->GetMaxHP()), wcslen(IntToCString(player[2]->GetHP()) + "/" + IntToCString(player[0]->GetMaxHP())));
			TextOut(hDC, 750, 575, IntToCString(player[2]->GetMP()) + "/" + IntToCString(player[2]->GetMaxMP()), wcslen(IntToCString(player[2]->GetMP()) + "/" + IntToCString(player[0]->GetMaxMP())));
		}
		if (fightstatussign == 2)
		{
			if (actionNow!=0)
			TextOut(hDC, 100, 555, (CString)(player[actionQueue[actionNow-1]]->GetName()) + 
				"对敌人造成了" + IntToCString(damagepoint) + "点伤害.",wcslen((CString)(player[actionQueue[actionNow-1]]->GetName()) + "对敌人造成了" + IntToCString(damagepoint) + "点伤害."));
			else
			{
				TextOut(hDC, 100, 555, (CString)(player[actionQueue[actionNow]]->GetName()) +
					"对敌人造成了" + IntToCString(damagepoint) + "点伤害.", wcslen((CString)(player[actionQueue[actionNow]]->GetName()) + "对敌人造成了" + IntToCString(damagepoint) + "点伤害."));
			}
			}
	}
}




BOOL GameEnd(HWND hwnd) {
	PauseMusic();
	g_Sprm.Release(TRUE);
	delete g_pGE;
	CloseHandle(hThread);
	return TRUE;
}
void GameActive(HWND hWnd)
{
	g_pGE->SetPause(FALSE);
}
void GamePause(HWND hWnd)
{
	g_pGE->SetPause(TRUE);
}

BOOL GameWindowClose(HWND hWnd)
{
	if (MessageBox(g_pGE->GetWindow(), L"你确定要退出吗", L"退出游戏", MB_YESNO | MB_DEFBUTTON2 | MB_ICONASTERISK) == IDYES)
		return TRUE;
	else
	{
		return FALSE;
	}
}


//窗口过程函数WndProc,对窗口消息进行处理
//------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


	switch (message)						//switch语句开始
	{
	case MM_MCINOTIFY:
	{

		mciSendCommand(gMciOpen.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&gMciOpen);
		mciSendCommand(gMciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& gMciPlay);
	}
	break;
	case WM_CREATE:
	{
		GameEngine::GetGameEngine()->SetWindow(hWnd);
		GameStart(hWnd);

	}
	break;
	case WM_PAINT:
	{// 若是客户区重绘消息
		HDC hDC; //绘图用DC
		HDC hMemDC;//双缓冲DC
		HBITMAP hbmMem, hbmOld;
		PAINTSTRUCT paintStruct; //定义一个PAINTSTRUCT结构体来记录一些绘制信息
		hDC = BeginPaint(hWnd, &paintStruct); //制定窗口进行绘图工作的准备，并用将和绘图有关的信息填充到paintStruct结构体中
		hMemDC = CreateCompatibleDC(hDC); //创建内存兼容设备环境
		//创建内存兼容位图
		hbmMem = CreateCompatibleBitmap(hDC, GameEngine::GetGameEngine()->GetWidth(), GameEngine::GetGameEngine()->GetHeight());
		hbmOld = (HBITMAP)SelectObject(hMemDC, hbmMem);
		GamePaint(hMemDC, lParam);  //调用gamepaint绘制到内存设备环境

		//将内存设备环境中的内容绘制到物理设备环境
		BitBlt(hDC, 0, 0, GameEngine::GetGameEngine()->GetWidth(), GameEngine::GetGameEngine()->GetHeight(), hMemDC, 0, 0, SRCCOPY);


		SelectObject(hMemDC, hbmOld);
		DeleteObject(hbmMem);
		DeleteDC(hMemDC);
		DeleteDC(hDC);
		//ValidateRect(hWnd, NULL);		// 更新客户区的显示
		EndPaint(hWnd, &paintStruct);
	}
	break;									//跳出该switch语句
	case WM_LBUTTONDOWN: //鼠标左键按下
	{

		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		if (g_nScene == 1)
		{

			if (x >= 472 && x <= 792 && y >= 220 && y <= 300)
			{
				g_Sprm.Release(TRUE);
				g_nScene = 2;
				player[0] = new Character(L"Student Monitor", 1, 1, 1, 7, 5, 7, 5, 5, 5, 1, 5);
				player[1] = new Character(L"CheerLeader", 1, 3, 2, 7, 7, 5, 5, 5, 7, 1, 5);
				player[2] = new Character(L"ChemistryTeacher", 1, 2, 1, 5, 5, 5, 7, 7, 5, 1, 5);
				g_bInitScene = FALSE;

				InitScene_2(hWnd);
			}
			if (x >= 472 && x <= 792 && y >= 400 && y <= 480)
			{
				if (GameWindowClose(hWnd))
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
				}
			}
		}
		if (g_nScene == 2)
		{
			//判定切换角色点击
			if (x >= 400 && x <= 430 && y >= 80 && y <= 130)
			{
				if (g_nCharacternum == 0)
				{
					g_nCharacternum = 2;
				}
				else
					g_nCharacternum--;
			}
			if (x >= 830 && y <= 860 && y >= 80 && y <= 130)
			{
				if (g_nCharacternum == 2)
				{
					g_nCharacternum = 0;
				}
				else
				{
					g_nCharacternum++;
				}
			}
			//增减数值点击事件
			if (x >= 720 && x <= 750 && y >= 160 && y <= 190)
			{
				if (player[g_nCharacternum]->GetStrength() == 5)
				{
				}
				else
				{
					player[g_nCharacternum]->Strength(player[g_nCharacternum]->GetStrength() - 1);
					player[g_nCharacternum]->SetAttributes(player[g_nCharacternum]->GetAttributes() + 1);
				}
			}
			if (x >= 780 && x <= 810 && y >= 160 && y <= 190)
			{
				if (player[g_nCharacternum]->GetAttributes() == 0)
				{
				}
				else
				{
					player[g_nCharacternum]->Strength(player[g_nCharacternum]->GetStrength() + 1);
					player[g_nCharacternum]->SetAttributes(player[g_nCharacternum]->GetAttributes() - 1);
				}
			}
			if (x >= 720 && x <= 750 && y >= 200 && y <= 230)
			{
				if (player[g_nCharacternum]->GetDexterity() == 5)
				{
				}
				else
				{
					player[g_nCharacternum]->Dexterity(player[g_nCharacternum]->GetDexterity() - 1);
					player[g_nCharacternum]->SetAttributes(player[g_nCharacternum]->GetAttributes() + 1);
				}
			}
			if (x >= 780 && x <= 810 && y >= 200 && y <= 230)
			{
				if (player[g_nCharacternum]->GetAttributes() == 0)
				{
				}
				else
				{
					player[g_nCharacternum]->Dexterity(player[g_nCharacternum]->GetDexterity() + 1);
					player[g_nCharacternum]->SetAttributes(player[g_nCharacternum]->GetAttributes() - 1);
				}
			}
			if (x >= 720 && x <= 750 && y >= 240 && y <= 270)
			{
				if (player[g_nCharacternum]->GetConstitution() == 5)
				{
				}
				else
				{
					player[g_nCharacternum]->Constitution(player[g_nCharacternum]->GetConstitution() - 1);
					player[g_nCharacternum]->SetAttributes(player[g_nCharacternum]->GetAttributes() + 1);
				}
			}
			if (x >= 780 && x <= 810 && y >= 240 && y <= 270)
			{
				if (player[g_nCharacternum]->GetAttributes() == 0)
				{
				}
				else
				{
					player[g_nCharacternum]->Constitution(player[g_nCharacternum]->GetConstitution() + 1);
					player[g_nCharacternum]->SetAttributes(player[g_nCharacternum]->GetAttributes() - 1);
				}
			}
			if (x >= 720 && x <= 750 && y >= 280 && y <= 310)
			{
				if (player[g_nCharacternum]->GetIntelligence() == 5)
				{
				}
				else
				{
					player[g_nCharacternum]->Intelligence(player[g_nCharacternum]->GetIntelligence() - 1);
					player[g_nCharacternum]->SetAttributes(player[g_nCharacternum]->GetAttributes() + 1);
				}
			}
			if (x >= 780 && x <= 810 && y >= 280 && y <= 310)
			{
				if (player[g_nCharacternum]->GetAttributes() == 0)
				{
				}
				else
				{
					player[g_nCharacternum]->Intelligence(player[g_nCharacternum]->GetIntelligence() + 1);
					player[g_nCharacternum]->SetAttributes(player[g_nCharacternum]->GetAttributes() - 1);
				}
			}
			if (x >= 720 && x <= 750 && y >= 320 && y <= 350)
			{
				if (player[g_nCharacternum]->GetWisdom() == 5)
				{
				}
				else
				{
					player[g_nCharacternum]->Wisdom(player[g_nCharacternum]->GetWisdom() - 1);
					player[g_nCharacternum]->SetAttributes(player[g_nCharacternum]->GetAttributes() + 1);
				}
			}
			if (x >= 780 && x <= 810 && y >= 320 && y <= 350)
			{
				if (player[g_nCharacternum]->GetAttributes() == 0)
				{
				}
				else
				{
					player[g_nCharacternum]->Wisdom(player[g_nCharacternum]->GetWisdom() + 1);
					player[g_nCharacternum]->SetAttributes(player[g_nCharacternum]->GetAttributes() - 1);
				}
			}
			if (x >= 720 && x <= 750 && y >= 360 && y <= 390)
			{
				if (player[g_nCharacternum]->GetCharisma() == 5)
				{
				}
				else
				{
					player[g_nCharacternum]->Charisma(player[g_nCharacternum]->GetCharisma() - 1);
					player[g_nCharacternum]->SetAttributes(player[g_nCharacternum]->GetAttributes() + 1);
				}
			}
			if (x >= 780 && x <= 810 && y >= 360 && y <= 390)
			{
				if (player[g_nCharacternum]->GetAttributes() == 0)
				{
				}
				else
				{
					player[g_nCharacternum]->Charisma(player[g_nCharacternum]->GetCharisma() + 1);
					player[g_nCharacternum]->SetAttributes(player[g_nCharacternum]->GetAttributes() - 1);
				}
			}
		}
	}
	break;
	case WM_SETFOCUS:
		GameActive(hWnd);
		GameEngine::GetGameEngine()->SetPause(FALSE);
		break;
	case WM_KILLFOCUS:
		GamePause(hWnd);
		GameEngine::GetGameEngine()->SetPause(TRUE);
		break;
	case WM_KEYDOWN:                // 若是键盘按下消息
		if (wParam == VK_ESCAPE)    // 如果被按下的键是ESC
			DestroyWindow(hWnd);		// 销毁窗口, 并发送一条WM_DESTROY消息
		break;									//跳出该switch语句
	case WM_CLOSE:
		if (GameWindowClose(hWnd))
		{
			GameEnd(hWnd);
			PostQuitMessage(0);
			PostQuitMessage(0);
		}
		break;
	case WM_DESTROY:			//若是窗口销毁消息
		GameEnd(hWnd);
		PostQuitMessage(0);
		PostQuitMessage(0);		//向系统表明有个线程有终止请求。用来响应WM_DESTROY消息
		break;								//跳出该switch语句
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		if (g_nScene == 1) {

			if (x >= 472 && x <= 792 && y >= 220 && y <= 300)
			{
				g_pMenuButton1->FloatEvent(TRUE);
			}
			else
			{
				g_pMenuButton1->FloatEvent(FALSE);
			}
			if (x >= 472 && x <= 792 && y >= 310 && y <= 390)
			{
				g_pMenuButton2->FloatEvent(TRUE);
			}
			else
			{
				g_pMenuButton2->FloatEvent(FALSE);
			}
			if (x >= 472 && x <= 792 && y >= 400 && y <= 480)
			{
				g_pMenuButton3->FloatEvent(TRUE);
			}
			else
			{
				g_pMenuButton3->FloatEvent(FALSE);
			}
		}
	}
	break;
	case WM_COMMAND:
	{
		switch (lParam)
		{


		case 1:
		{
			if (player[0]->GetAttributes() != 0 || player[1]->GetAttributes() != 0 || player[2]->GetAttributes() != 0)
			{
				MessageBox(g_pGE->GetWindow(), L"Character's attributes still remain.", L"Alert", MB_OK | MB_DEFBUTTON2 | MB_ICONASTERISK);
			}
			else
			{
				player[0]->MaxHP((player[0]->GetConstitution() - 1) * 3 + Character::RandomDx_y(5, 20));
				player[0]->HP(player[0]->GetMaxHP());
				player[0]->MaxMP((player[0]->GetIntelligence() - 10) / 2 + 10);
				player[0]->MP(player[0]->GetMaxMP());
				player[0]->SetAttack((player[0]->GetStrength() - 10) / 2);
				player[0]->SetDefend((player[0]->GetDexterity() - 10) / 2);
				player[0]->SetActionNum((player[0]->GetDexterity() - 10) / 2 + Character::RandomDx_y(1, 20));

				player[1]->MaxHP((player[1]->GetConstitution() - 1) * 3 + Character::RandomDx_y(5, 20));
				player[1]->HP(player[1]->GetMaxHP());
				player[1]->MaxMP((player[1]->GetIntelligence() - 10) / 2 + 10);
				player[1]->MP(player[1]->GetMaxMP());
				player[1]->SetAttack((player[1]->GetCharisma() - 8) / 2);
				player[1]->SetDefend((player[1]->GetDexterity() - 10) / 2);
				player[1]->SetActionNum((player[1]->GetDexterity() - 10) / 2 + Character::RandomDx_y(1, 20));

				player[2]->MaxHP((player[2]->GetConstitution() - 1) * 3 + Character::RandomDx_y(5, 20));
				player[2]->HP(player[2]->GetMaxHP());
				player[2]->MaxMP((player[2]->GetIntelligence() - 10) / 2 + 10);
				player[2]->MP(player[2]->GetMaxMP());
				player[2]->SetAttack((player[2]->GetIntelligence() - 5) / 2);
				player[2]->SetDefend((player[2]->GetDexterity() - 10) / 2);
				player[2]->SetActionNum((player[2]->GetDexterity() - 10) / 2 + Character::RandomDx_y(1, 20));

				g_pSetMenuButton->SetVisible(FALSE);
				g_Sprm.Release(FALSE);
				PauseMusic();
				g_nScene = 3;
				InitScene_3(hWnd);

			}
		}
		case 2:
			//g_DrawObject[0]->SetGifStatus(TRUE);
			if (fightstatussign == 1)
			{

				if (skillchoosesign != 10 && skillchoosesign != 11)
				{
					if (player[actionQueue[actionNow]]->GetMP() < 3)
					{
						MessageBox(hWnd, L"MP is not enough", L"Alert", MB_OK | MB_DEFBUTTON2 | MB_ICONASTERISK);
						break;
					}
					player[actionQueue[actionNow]]->MP(player[actionQueue[actionNow]]->GetMP() - 3);
				}
				playermessagesentsign = 1;

				if (skillchoosesign==12)
				{
					player[3]->SetStatus(1);
					g_pStatusSign2[0]->SetVisible(TRUE);
				}
				if (skillchoosesign==15)
				{
					player[3]->SetStatus(2);
					g_pStatusSign3[0]->SetVisible(TRUE);
				}
				
			
				g_pSkill[skillchoosesign]->SetDrawCxImageInfo(420, 130, 100, 100, 200);
				g_pSkill[skillchoosesign]->SetVisible(TRUE);
				g_pSkill[skillchoosesign]->SetGifStatus(TRUE);
				PlayWavMusic(soundfile[skillchoosesign]);
				player[3]->HP(player[3]->GetHP() - damagepoint);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}				
				fightstatussign = 2;

			}
			break;
		case 3:
			//g_DrawObject[0]->SetGifStatus(TRUE);
			if (fightstatussign == 1)
			{
				if (skillchoosesign != 10 && skillchoosesign != 11)
				{
					if (player[actionQueue[actionNow]]->GetMP() < 3)
					{
						MessageBox(hWnd, L"MP is not enough", L"Alert", MB_OK | MB_DEFBUTTON2 | MB_ICONASTERISK);
						break;
					}
					player[actionQueue[actionNow]]->MP(player[actionQueue[actionNow]]->GetMP() - 3);
				}
				playermessagesentsign = 1;

				if (skillchoosesign == 12)
				{
					player[4]->SetStatus(1);
					g_pStatusSign2[1]->SetVisible(TRUE);
				}
				if (skillchoosesign == 15)
				{
					player[4]->SetStatus(2);
					g_pStatusSign3[1]->SetVisible(TRUE);
				}
				PlayWavMusic(soundfile[skillchoosesign]);
				g_pSkill[skillchoosesign]->SetDrawCxImageInfo(540, 130, 100, 100, 200);
				g_pSkill[skillchoosesign]->SetVisible(TRUE);
				g_pSkill[skillchoosesign]->SetGifStatus(TRUE);
				player[4]->HP(player[4]->GetHP() - damagepoint);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}				fightstatussign = 2;
			}
			break;
		case 4:
			//g_DrawObject[0]->SetGifStatus(TRUE);
			if (fightstatussign == 1)
			{
				if (skillchoosesign != 10 && skillchoosesign != 11)
				{
					if (player[actionQueue[actionNow]]->GetMP() < 3)
					{
						MessageBox(hWnd, L"MP is not enough", L"Alert", MB_OK | MB_DEFBUTTON2 | MB_ICONASTERISK);
						break;
					}
					player[actionQueue[actionNow]]->MP(player[actionQueue[actionNow]]->GetMP() - 3);
				}
				playermessagesentsign = 1;

				if (skillchoosesign == 12)
				{
					player[5]->SetStatus(1);
					g_pStatusSign2[2]->SetVisible(TRUE);
				}
				if (skillchoosesign == 15)
				{
					player[5]->SetStatus(2);
					g_pStatusSign3[2]->SetVisible(TRUE);
				}
				PlayWavMusic(soundfile[skillchoosesign]);

				g_pSkill[skillchoosesign]->SetDrawCxImageInfo(660, 130, 100, 100, 200);
				g_pSkill[skillchoosesign]->SetVisible(TRUE);
				g_pSkill[skillchoosesign]->SetGifStatus(TRUE);
				player[5]->HP(player[5]->GetHP() - damagepoint);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}				fightstatussign = 2;
			}
			break;
		case 5:
			//g_DrawObject[0]->SetGifStatus(TRUE);
			if (fightstatussign == 1)
			{
				if (skillchoosesign != 10 && skillchoosesign != 11)
				{
					if (player[actionQueue[actionNow]]->GetMP() < 3)
					{
						MessageBox(hWnd, L"MP is not enough", L"Alert", MB_OK | MB_DEFBUTTON2 | MB_ICONASTERISK);
						break;
					}
					player[actionQueue[actionNow]]->MP(player[actionQueue[actionNow]]->GetMP() - 3);
				}
				playermessagesentsign = 1;

				if (skillchoosesign == 12)
				{
					player[6]->SetStatus(1);
					g_pStatusSign2[3]->SetVisible(TRUE);
				}
				if (skillchoosesign == 15)
				{
					player[6]->SetStatus(2);
					g_pStatusSign3[3]->SetVisible(TRUE);
				}
				PlayWavMusic(soundfile[skillchoosesign]);

				g_pSkill[skillchoosesign]->SetDrawCxImageInfo(780, 130, 100, 100, 200);
				g_pSkill[skillchoosesign]->SetVisible(TRUE);
				g_pSkill[skillchoosesign]->SetGifStatus(TRUE);
				player[6]->HP(player[6]->GetHP() - damagepoint);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				fightstatussign = 2;
			}
			break;
		case 6:
			//g_DrawObject[0]->SetGifStatus(TRUE);
			if (fightstatussign == 1)
			{
				if (skillchoosesign != 10 && skillchoosesign != 11)
				{
					if (player[actionQueue[actionNow]]->GetMP() < 3)
					{
						MessageBox(hWnd, L"MP is not enough", L"Alert", MB_OK | MB_DEFBUTTON2 | MB_ICONASTERISK);
						break;
					}
					player[actionQueue[actionNow]]->MP(player[actionQueue[actionNow]]->GetMP() - 3);
				}
				playermessagesentsign = 1;

				if (skillchoosesign == 12)
				{
					player[7]->SetStatus(1);
					g_pStatusSign2[4]->SetVisible(TRUE);
				}
				if (skillchoosesign == 15)
				{
					player[7]->SetStatus(2);
					g_pStatusSign3[4]->SetVisible(TRUE);
				}
				PlayWavMusic(soundfile[skillchoosesign]);

				g_pSkill[skillchoosesign]->SetDrawCxImageInfo(380, 240, 100, 100, 200);
				g_pSkill[skillchoosesign]->SetVisible(TRUE);
				g_pSkill[skillchoosesign]->SetGifStatus(TRUE);
				player[7]->HP(player[7]->GetHP() - damagepoint);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				fightstatussign = 2;
			}
			break;
		case 7:
			//g_DrawObject[0]->SetGifStatus(TRUE);
			if (fightstatussign == 1)
			{
				if (skillchoosesign != 10 && skillchoosesign != 11)
				{
					if (player[actionQueue[actionNow]]->GetMP() < 3)
					{
						MessageBox(hWnd, L"MP is not enough", L"Alert", MB_OK | MB_DEFBUTTON2 | MB_ICONASTERISK);
						break;
					}
					player[actionQueue[actionNow]]->MP(player[actionQueue[actionNow]]->GetMP() - 3);
				}
				playermessagesentsign = 1;

				if (skillchoosesign == 12)
				{
					player[8]->SetStatus(1);
					g_pStatusSign2[5]->SetVisible(TRUE);
				}
				if (skillchoosesign == 15)
				{
					player[8]->SetStatus(2);
					g_pStatusSign3[5]->SetVisible(TRUE);
				}
				PlayWavMusic(soundfile[skillchoosesign]);

				g_pSkill[skillchoosesign]->SetDrawCxImageInfo(500, 240, 100, 100, 200);
				g_pSkill[skillchoosesign]->SetVisible(TRUE);
				g_pSkill[skillchoosesign]->SetGifStatus(TRUE);
				player[8]->HP(player[8]->GetHP() - damagepoint);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				fightstatussign = 2;
			}
			break;
		case 8:
			//g_DrawObject[0]->SetGifStatus(TRUE);
			if (fightstatussign == 1)
			{
				if (skillchoosesign != 10 && skillchoosesign != 11)
				{
					if (player[actionQueue[actionNow]]->GetMP() < 3)
					{
						MessageBox(hWnd, L"MP is not enough", L"Alert", MB_OK | MB_DEFBUTTON2 | MB_ICONASTERISK);
						break;
					}
					player[actionQueue[actionNow]]->MP(player[actionQueue[actionNow]]->GetMP() - 3);
				}
				playermessagesentsign = 1;

				if (skillchoosesign == 12)
				{
					player[9]->SetStatus(1);
					g_pStatusSign2[6]->SetVisible(TRUE);
				}
				if (skillchoosesign == 15)
				{
					player[9]->SetStatus(2);
					g_pStatusSign3[6]->SetVisible(TRUE);
				}
				PlayWavMusic(soundfile[skillchoosesign]);

				g_pSkill[skillchoosesign]->SetDrawCxImageInfo(620, 240, 100, 100, 200);
				g_pSkill[skillchoosesign]->SetVisible(TRUE);
				g_pSkill[skillchoosesign]->SetGifStatus(TRUE);
				player[9]->HP(player[9]->GetHP() - damagepoint);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				fightstatussign = 2;
			}
			break;
		case 9:
			//g_DrawObject[0]->SetGifStatus(TRUE);
			if (fightstatussign == 1)
			{
				if (skillchoosesign != 10 && skillchoosesign != 11)
				{
					if (player[actionQueue[actionNow]]->GetMP() < 3)
					{
						MessageBox(hWnd, L"MP is not enough", L"Alert", MB_OK | MB_DEFBUTTON2 | MB_ICONASTERISK);
						break;
					}
					player[actionQueue[actionNow]]->MP(player[actionQueue[actionNow]]->GetMP() - 3);
				}
				playermessagesentsign = 1;

				if (skillchoosesign == 12)
				{
					player[10]->SetStatus(1);
					g_pStatusSign2[7]->SetVisible(TRUE);
				}
				if (skillchoosesign == 15)
				{
					player[10]->SetStatus(2);
					g_pStatusSign3[7]->SetVisible(TRUE);
				}
				PlayWavMusic(soundfile[skillchoosesign]);

				g_pSkill[skillchoosesign]->SetDrawCxImageInfo(740, 240, 100, 100, 200);
				g_pSkill[skillchoosesign]->SetVisible(TRUE);
				g_pSkill[skillchoosesign]->SetGifStatus(TRUE);	
				player[10]->HP(player[10]->GetHP() - damagepoint);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				fightstatussign = 2;
			}
			break;

		case 10: {
			fightstatussign = 1;
			skillchoosesign = 10;
			damagepoint = Character::RandomDx_y(1, 10) + player[actionQueue[actionNow]]->GetAttack();
			g_pStatusSign1[actionQueue[actionNow]]->SetVisible(FALSE);

		}
				 break;
		case 11: {
				g_pStatusSign1[actionQueue[actionNow]]->SetVisible(TRUE);
				player[actionQueue[actionNow]]->SetStatus(0);
				fightstatussign = 5;
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				playermessagesentsign = 1;

			break;
		}
		case 12: {
			skillchoosesign = 12;
			fightstatussign = 1;
			damagepoint = Character::RandomDx_y(1, 12) + player[actionQueue[actionNow]]->GetAttack();
			break;
		}
		case 13: {
			skillchoosesign = 13;
			PlayWavMusic(soundfile[skillchoosesign]);
			if (player[actionQueue[actionNow]]->GetMP() < 3)
			{
				MessageBox(hWnd, L"MP is not enough", L"Alert", MB_OK | MB_DEFBUTTON2 | MB_ICONASTERISK);
				break;
			}
			player[actionQueue[actionNow]]->MP(player[actionQueue[actionNow]]->GetMP() - 3);
						playermessagesentsign = 1;

			g_pSkill[skillchoosesign]->SetDrawCxImageInfo(458, 450, 300, 200, 50);
			g_pSkill[skillchoosesign]->SetGifStatus(TRUE);
			g_pSkill[skillchoosesign]->SetVisible(TRUE);

			damagepoint = Character::RandomDx_y(5, 15) + (player[actionQueue[actionNow]]->GetCharisma())/2 ;

			if (player[0]->GetHP()>0)
			player[0]->HP(player[0]->GetHP()  + damagepoint);
			if (player[0]->GetHP() > player[0]->GetMaxHP())
				player[0]->HP(player[0]->GetMaxHP());

			player[1]->HP(player[1]->GetHP() + damagepoint);
			if (player[1]->GetHP() > player[1]->GetMaxHP())
				player[1]->HP(player[1]->GetMaxHP());

			if (player[2]->GetHP() > 0)
			player[2]->HP(player[2]->GetHP() + damagepoint);
			if (player[2]->GetHP() > player[2]->GetMaxHP())
				player[2]->HP(player[2]->GetMaxHP());
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}
			fightstatussign = 6;

			break;
		}
		case 14: {
			fightstatussign = 1;
			
			skillchoosesign = 14;
		damagepoint = Character::RandomDx_y(5, 20) + (player[actionQueue[actionNow]]->GetCharisma()-2)/2;
			break;
		}
		case 15: {
			fightstatussign = 1;
			skillchoosesign = 15;
			damagepoint = Character::RandomDx_y(3, 18) + (player[actionQueue[actionNow]]->GetIntelligence() - 2) / 2;

			break;
		}
		case 16: {
			fightstatussign = 1;
			skillchoosesign = 16;
			damagepoint = Character::RandomDx_y(5, 25) + (player[actionQueue[actionNow]]->GetIntelligence() - 2) / 2;

			break;
		}
		default:
			break;
		}
	}
	break;
	case WM_OVEROBJECT:
		MessageBox(g_pGE->GetWindow(), IntToCString(wParam), L"提醒", MB_OK | MB_DEFBUTTON2 | MB_ICONASTERISK);
		break;
	case WM_FIGHT1:
	{
		if (wParam == 0)
		{
			g_pStatusSign1[0]->SetVisible(FALSE);
			player[0]->SetStatus(4);
			player[0]->MP(player[0]->GetMP() + 1);
			if (player[0]->GetMP() > player[0]->GetMaxMP())
			{
				player[0]->MP(player[0]->GetMaxMP());
			}

			break;
		}
		if (wParam == 1)
		{
			g_pStatusSign1[1]->SetVisible(FALSE);
			player[1]->SetStatus(4);

			player[1]->MP(player[1]->GetMP() + 1);
			if (player[1]->GetMP() > player[1]->GetMaxMP())
			{
				player[1]->MP(player[1]->GetMaxMP());
			}


			break;
		}
		if (wParam == 2)
		{
			g_pStatusSign1[2]->SetVisible(FALSE);
			player[2]->SetStatus(4);

			player[2]->MP(player[2]->GetMP() + 1);
			if (player[2]->GetMP() > player[2]->GetMaxMP())
			{
				player[2]->MP(player[2]->GetMaxMP());
			}


			break;
		}

		if (wParam == 3)
		{
			if (fightstatussign == 3)
			{
				damagepoint = player[3]->GetAttack() + Character::RandomDx_y(1, 10);
			
			
				PlayWavMusic(soundfile[11]);
				switch (ChooseTarget())
				{
				case 0:
					g_pSkill[17]->SetDrawCxImageInfo(458, 415, 100, 100, 200);
					if (player[0]->GetStatus() == 0)
						damagepoint = damagepoint - player[0]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[0]->HP(player[0]->GetHP() - damagepoint);
					break;
				case 1:
					g_pSkill[17]->SetDrawCxImageInfo(597, 415, 100, 100, 200);
					if (player[1]->GetStatus() == 0)
						damagepoint = damagepoint - player[1]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[1]->HP(player[1]->GetHP() - damagepoint);

					break;
				case 2:
					g_pSkill[17]->SetDrawCxImageInfo(737, 415, 100, 100, 200);
					if (player[2]->GetStatus() == 0)
						damagepoint = damagepoint - player[2]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[2]->HP(player[2]->GetHP() - damagepoint);

					break;
				}

				if (player[3]->GetStatus()==1)
				{
					player[3]->SetStatus(0);
					g_pStatusSign2[0]->SetVisible(FALSE);
					actionNow++;
					if (actionNow == 11)
					{
						actionNow = 0;
					}
					break;
				}
				if (player[3]->GetStatus()==2)
				{
					player[3]->HP(player[3]->GetHP() - Character::RandomDx_y(1, 5));
					if (player[3]->GetHP()<=0)
					{
						actionNow++;
						if (actionNow == 11)
						{
							actionNow = 0;
						}
						break;
					}
				}

				g_DrawObject[0]->SetGifStatus(TRUE);
				g_pSkill[17]->SetVisible(TRUE);
				g_pSkill[17]->SetGifStatus(TRUE);
				fightstatussign = 4;

				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				break;
			}
		}

		if (wParam == 4)
			if (fightstatussign == 3)
			{
				PlayWavMusic(soundfile[11]);
				damagepoint = player[4]->GetAttack() + Character::RandomDx_y(1, 10);
				if (damagepoint < 0)
				{
					damagepoint = 0;
				}
				switch (ChooseTarget())
				{
				case 0:
					g_pSkill[17]->SetDrawCxImageInfo(458, 415, 100, 100, 200);
					if (player[0]->GetStatus() == 0)
						damagepoint = damagepoint - player[0]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[0]->HP(player[0]->GetHP() - damagepoint);
					break;
				case 1:
					g_pSkill[17]->SetDrawCxImageInfo(597, 415, 100, 100, 200);
					if (player[1]->GetStatus() == 0)
						damagepoint = damagepoint - player[1]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[1]->HP(player[1]->GetHP() - damagepoint);

					break;
				case 2:
					g_pSkill[17]->SetDrawCxImageInfo(737, 415, 100, 100, 200);
					if (player[2]->GetStatus() == 0)
						damagepoint = damagepoint - player[2]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[2]->HP(player[2]->GetHP() - damagepoint);

					break;
				}
				if (player[4]->GetStatus() == 1)
				{
					player[4]->SetStatus(0);
					g_pStatusSign2[1]->SetVisible(FALSE);
					actionNow++;
					if (actionNow == 11)
					{
						actionNow = 0;
					}
					break;
				}
				if (player[4]->GetStatus() == 2)
				{
					player[4]->HP(player[4]->GetHP() - Character::RandomDx_y(1, 5));
					if (player[4]->GetHP() <= 0)
					{
						break;
					}
				}
				g_DrawObject[1]->SetGifStatus(TRUE);
				g_pSkill[17]->SetVisible(TRUE);
				g_pSkill[17]->SetGifStatus(TRUE);
				fightstatussign = 4;

				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				break;
			}

		if (wParam == 5)
			if (fightstatussign == 3)
			{
				PlayWavMusic(soundfile[11]);
				damagepoint = player[5]->GetAttack() + Character::RandomDx_y(1, 10);
				if (damagepoint < 0)
				{
					damagepoint = 0;
				}
				switch (ChooseTarget())
				{
				case 0:
					g_pSkill[17]->SetDrawCxImageInfo(458, 415, 100, 100, 200);
					if (player[0]->GetStatus() == 0)
						damagepoint = damagepoint - player[0]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[0]->HP(player[0]->GetHP() - damagepoint);
					break;
				case 1:
					g_pSkill[17]->SetDrawCxImageInfo(597, 415, 100, 100, 200);
					if (player[1]->GetStatus() == 0)
						damagepoint = damagepoint - player[1]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[1]->HP(player[1]->GetHP() - damagepoint);

					break;
				case 2:
					g_pSkill[17]->SetDrawCxImageInfo(737, 415, 100, 100, 200);
					if (player[2]->GetStatus() == 0)
						damagepoint = damagepoint - player[2]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[2]->HP(player[2]->GetHP() - damagepoint);

					break;
				}

				if (player[5]->GetStatus() == 1)
				{
					player[5]->SetStatus(0);
					g_pStatusSign2[2]->SetVisible(FALSE);
					actionNow++;
					if (actionNow == 11)
					{
						actionNow = 0;
					}
					break;
				}
				if (player[5]->GetStatus() == 2)
				{
					player[5]->HP(player[5]->GetHP() - Character::RandomDx_y(1, 5));
					if (player[5]->GetHP() <= 0)
					{
						actionNow++;
						if (actionNow == 11)
						{
							actionNow = 0;
						}
						break;
					}
				}
				g_pSkill[17]->SetVisible(TRUE);
				g_DrawObject[2]->SetGifStatus(TRUE);
				g_pSkill[17]->SetVisible(TRUE);
				g_pSkill[17]->SetGifStatus(TRUE);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				fightstatussign = 4;
				break;
			}

		if (wParam == 6)
			if (fightstatussign == 3)
			{

				PlayWavMusic(soundfile[11]);
				damagepoint = player[6]->GetAttack() + Character::RandomDx_y(1, 10);
				if (damagepoint < 0)
				{
					damagepoint = 0;
				}
				switch (ChooseTarget())
				{
				case 0:
					g_pSkill[17]->SetDrawCxImageInfo(458, 415, 100, 100, 200);
					if (player[0]->GetStatus() == 0)
						damagepoint = damagepoint - player[0]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[0]->HP(player[0]->GetHP() - damagepoint);
					break;
				case 1:
					g_pSkill[17]->SetDrawCxImageInfo(597, 415, 100, 100, 200);
					if (player[1]->GetStatus() == 0)
						damagepoint = damagepoint - player[1]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[1]->HP(player[1]->GetHP() - damagepoint);

					break;
				case 2:
					g_pSkill[17]->SetDrawCxImageInfo(737, 415, 100, 100, 200);
					if (player[2]->GetStatus() == 0)
						damagepoint = damagepoint - player[2]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[2]->HP(player[2]->GetHP() - damagepoint);

					break;
				}
				if (player[6]->GetStatus() == 1)
				{
					player[6]->SetStatus(0);
					g_pStatusSign2[3]->SetVisible(FALSE);
					actionNow++;
					if (actionNow == 11)
					{
						actionNow = 0;
					}
					break;
				}
				if (player[6]->GetStatus() == 2)
				{
					player[6]->HP(player[6]->GetHP() - Character::RandomDx_y(1, 5));
					if (player[6]->GetHP() <= 0)
					{
						actionNow++;
						if (actionNow == 11)
						{
							actionNow = 0;
						}
						break;
					}
				}
				g_pSkill[17]->SetVisible(TRUE);
				g_DrawObject[3]->SetGifStatus(TRUE);

				g_pSkill[17]->SetVisible(TRUE);
				g_pSkill[17]->SetGifStatus(TRUE);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				fightstatussign = 4;
				break;
			}

		if (wParam == 7)
			if (fightstatussign == 3)
			{
				PlayWavMusic(soundfile[11]);
				damagepoint = player[7]->GetAttack() + Character::RandomDx_y(1, 10);
				if (damagepoint < 0)
				{
					damagepoint = 0;
				}
				switch (ChooseTarget())
				{
				case 0:
					g_pSkill[17]->SetDrawCxImageInfo(458, 415, 100, 100, 200);
					if (player[0]->GetStatus() == 0)
						damagepoint = damagepoint - player[0]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[0]->HP(player[0]->GetHP() - damagepoint);
					break;
				case 1:
					g_pSkill[17]->SetDrawCxImageInfo(597, 415, 100, 100, 200);
					if (player[1]->GetStatus() == 0)
						damagepoint = damagepoint - player[1]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[1]->HP(player[1]->GetHP() - damagepoint);

					break;
				case 2:
					g_pSkill[17]->SetDrawCxImageInfo(737, 415, 100, 100, 200);
					if (player[2]->GetStatus() == 0)
						damagepoint = damagepoint - player[2]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[2]->HP(player[2]->GetHP() - damagepoint);

					break;
				}
				if (player[7]->GetStatus() == 1)
				{
					player[7]->SetStatus(0);
					g_pStatusSign2[4]->SetVisible(FALSE);
					actionNow++;
					if (actionNow == 11)
					{
						actionNow = 0;
					}
					break;
				}
				if (player[7]->GetStatus() == 2)
				{
					player[7]->HP(player[7]->GetHP() - Character::RandomDx_y(1, 5));
					if (player[7]->GetHP() <= 0)
					{
						actionNow++;
						if (actionNow == 11)
						{
							actionNow = 0;
						}
						break;
					}
				}
				g_pSkill[17]->SetVisible(TRUE);
				g_DrawObject[4]->SetGifStatus(TRUE);

				g_pSkill[17]->SetVisible(TRUE);
				g_pSkill[17]->SetGifStatus(TRUE);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}

				fightstatussign = 4;
				break;
			}

		if (wParam == 8)
			if (fightstatussign == 3)
			{
			PlayWavMusic(soundfile[11]);
			damagepoint = player[8]->GetAttack() + Character::RandomDx_y(1, 10);
			if (damagepoint < 0)
			{
				damagepoint = 0;
			}
			switch (ChooseTarget())
			{
			case 0:
				g_pSkill[17]->SetDrawCxImageInfo(458, 415, 100, 100, 200);
				if (player[0]->GetStatus() == 0)
					damagepoint = damagepoint - player[0]->GetDefend();
				if (damagepoint < 0)
				{
					damagepoint = 0;
				}
				player[0]->HP(player[0]->GetHP() - damagepoint);
				break;
			case 1:
				g_pSkill[17]->SetDrawCxImageInfo(597, 415, 100, 100, 200);
				if (player[1]->GetStatus() == 0)
					damagepoint = damagepoint - player[1]->GetDefend();
				if (damagepoint < 0)
				{
					damagepoint = 0;
				}
				player[1]->HP(player[1]->GetHP() - damagepoint);

				break;
			case 2:
				g_pSkill[17]->SetDrawCxImageInfo(737, 415, 100, 100, 200);
				if (player[2]->GetStatus() == 0)
					damagepoint = damagepoint - player[2]->GetDefend();
				if (damagepoint < 0)
				{
					damagepoint = 0;
				}
				player[2]->HP(player[2]->GetHP() - damagepoint);

				break;
			}
			if (player[8]->GetStatus() == 1)
			{
				player[8]->SetStatus(0);
				g_pStatusSign2[5]->SetVisible(FALSE);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				break;
			}
			if (player[8]->GetStatus() == 2)
			{
				player[8]->HP(player[8]->GetHP() - Character::RandomDx_y(1, 5));
				if (player[8]->GetHP() <= 0)
				{
					actionNow++;
					if (actionNow == 11)
					{
						actionNow = 0;
					}
					break;
				}
			}
			g_pSkill[17]->SetVisible(TRUE);
			g_DrawObject[5]->SetGifStatus(TRUE);

			g_pSkill[17]->SetVisible(TRUE);
			g_pSkill[17]->SetGifStatus(TRUE);

			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}
			fightstatussign = 4;
			break;

		}

		if (wParam == 9)
			if (fightstatussign == 3)
			{
			PlayWavMusic(soundfile[11]);
			damagepoint = player[9]->GetAttack() + Character::RandomDx_y(1, 10);
			if (damagepoint < 0)
			{
				damagepoint = 0;
			}
			switch (ChooseTarget())
			{
			case 0:
				g_pSkill[17]->SetDrawCxImageInfo(458, 415, 100, 100, 200);
				if (player[0]->GetStatus() == 0)
					damagepoint = damagepoint - player[0]->GetDefend();
				if (damagepoint < 0)
				{
					damagepoint = 0;
				}
				player[0]->HP(player[0]->GetHP() - damagepoint);
				break;
			case 1:
				g_pSkill[17]->SetDrawCxImageInfo(597, 415, 100, 100, 200);
				if (player[1]->GetStatus() == 0)
					damagepoint = damagepoint - player[1]->GetDefend();
				if (damagepoint < 0)
				{
					damagepoint = 0;
				}
				player[1]->HP(player[1]->GetHP() - damagepoint);

				break;
			case 2:
				g_pSkill[17]->SetDrawCxImageInfo(737, 415, 100, 100, 200);
				if (player[2]->GetStatus() == 0)
					damagepoint = damagepoint - player[2]->GetDefend();
				if (damagepoint < 0)
				{
					damagepoint = 0;
				}
				player[2]->HP(player[2]->GetHP() - damagepoint);

				break;
			}
			if (player[9]->GetStatus() == 1)
			{
				player[9]->SetStatus(0);
				g_pStatusSign2[6]->SetVisible(FALSE);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				break;
			}
			if (player[9]->GetStatus() == 2)
			{
				player[9]->HP(player[9]->GetHP() - Character::RandomDx_y(1, 5));
				if (player[9]->GetHP() <= 0)
				{
					actionNow++;
					if (actionNow == 11)
					{
						actionNow = 0;
					}
					break;
				}
			}
			
			g_pSkill[17]->SetVisible(TRUE);
			g_DrawObject[6]->SetGifStatus(TRUE);

			g_pSkill[17]->SetVisible(TRUE);
			g_pSkill[17]->SetGifStatus(TRUE);
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}
			fightstatussign = 4;
			break;
		}

		if (wParam == 10)
			if (fightstatussign == 3)
			{
			PlayWavMusic(soundfile[11]);
			damagepoint = player[10]->GetAttack() + Character::RandomDx_y(1, 10);
			if (damagepoint<0)
			{	
				damagepoint = 0;
			}
			switch (ChooseTarget())
				{
				case 0:
					g_pSkill[17]->SetDrawCxImageInfo(458, 415, 100, 100, 200);
					if (player[0]->GetStatus() == 0)
						damagepoint = damagepoint - player[0]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[0]->HP(player[0]->GetHP() - damagepoint);
					break;
				case 1:
					g_pSkill[17]->SetDrawCxImageInfo(597, 415, 100, 100, 200);
					if (player[1]->GetStatus() == 0)
						damagepoint = damagepoint - player[1]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[1]->HP(player[1]->GetHP() - damagepoint);

					break;
				case 2:
					g_pSkill[17]->SetDrawCxImageInfo(737, 415, 100, 100, 200);
					if (player[2]->GetStatus() == 0)
						damagepoint = damagepoint - player[2]->GetDefend();
					if (damagepoint < 0)
					{
						damagepoint = 0;
					}
					player[2]->HP(player[2]->GetHP() - damagepoint);

					break;
				}		
			if (player[10]->GetStatus() == 1)
			{
				player[10]->SetStatus(0);
				g_pStatusSign2[7]->SetVisible(FALSE);
				actionNow++;
				if (actionNow == 11)
				{
					actionNow = 0;
				}
				break;
			}
			if (player[10]->GetStatus() == 2)
			{
				player[10]->HP(player[10]->GetHP() - Character::RandomDx_y(1, 5));
				if (player[10]->GetHP() <= 0)
				{
					actionNow++;
					if (actionNow == 11)
					{
						actionNow = 0;
					}
					break;
				}
			}
			
			g_pSkill[17]->SetVisible(TRUE);
			g_DrawObject[7]->SetGifStatus(TRUE);

			g_pSkill[17]->SetVisible(TRUE);
			g_pSkill[17]->SetGifStatus(TRUE);
			actionNow++;
			if (actionNow == 11)
			{
				actionNow = 0;
			}
			fightstatussign = 4;
			break;
		}
		break;

	}
	break;
	case WM_MUSIC:
		PauseMusic();
		break;

		default:									//若上述case条件都不符合，则执行该default语句
			return DefWindowProc(hWnd, message, wParam, lParam);		//调用缺省的窗口过程
		break;

	return 0;			//正常退出
	}

}
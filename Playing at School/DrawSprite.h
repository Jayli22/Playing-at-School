#pragma once
#include <windows.h>
#include <ximage.h>
#include "atlimage.h"
using namespace std;
typedef int DRAWTYPE;
const DRAWTYPE DT_NULL = 0,
DT_DRAW = 1,
DT_ALPHA = 2,
DT_GRAY = 3,
DT_TRANSALPHA = 4,
DT_ANIMA = 5,
DT_RECT = 6,
DT_CXIMAGE = 7,
DT_CXIMAGEDIALOG = 8;
class DrawSprite
{
protected:static int m_nNewID;
		  int m_ID;
		  HBITMAP m_hbm;
		  int m_nWidth, m_nHeight;
		  int m_nZOrder;
		  //动画成员属性
		  int m_nFrameWidth, m_nFrameHeight; //位图中构成动画的单帧图像高度和宽度
		  int m_nRowCount, m_nColCount; //为途中构成动画的系列帧的行、列总数
		  int m_nRow, m_nCol;
		  int m_nFrameDelay;
		  unsigned long m_lNextFrameTime;
		  BOOL m_bInitAnima;//是否已经初始化
		  //精灵管理类精灵数据
		  DRAWTYPE m_dt;
		  int m_nX, m_nY;
		  BOOL m_bTrans;
		  COLORREF m_crTrans;//透明色
		  int m_nAlpha;
		  //用于DrawTransAlpha方法背景图左上角图表、宽度和高度
		  int m_nXBack, m_nYBack, m_nWidthBack, m_nHeightBack;
		  //用于drawrect方法
		  int m_nRectX, m_nRectY, m_nRectWidth, m_nRectHeight;
		  BOOL m_bVisible;
		  CString m_dialogword;
		  CxImage *m_cxImage;//cxImage对象指针'
		  CxImage *m_OriImg;
		  int m_nXFont, m_nYFont, m_nFontHeight, m_nFontWeight,m_nFontWidth;
		  COLORREF m_FontColor;
		  int m_hWndID;
		  HWND m_ObjecthWnd;
		  BOOL m_PlayGif = FALSE;

public:
	DrawSprite();  

	DrawSprite(HINSTANCE hInstance, LPTSTR szFileNmae); //根据位图文件名创造绘制精灵
	DrawSprite(HINSTANCE hInstance, UINT uRcID); //根据位图资源ID创建绘制精灵
	//创建精灵，并可载入图像文件szFileName并可设置是否将其转换为Hbitmap，以便与原油的方法相兼容
	DrawSprite(LPTSTR szFileName, BOOL bConvertBmp = FALSE);


	//获取CxImage属性
	CxImage *GetCxImage()const
	{
		return m_cxImage;
	}

	void SetCxImage(CxImage *image)
	{
		m_cxImage = image;
	}
	//载入图像文件szFileName并可设置是否将其转换为Hbitmap，以便与原油的方法相兼容
	BOOL LoadCxImage(LPTSTR szFileName, BOOL bConvertBmp = FALSE);
	//在以x和y为左上角，宽nWidth，高nHeight的范围内绘制图像，并可设置动画帧延迟时为nFrameDelay
	void DrawCxImage(HDC hDC, int x, int y, int nWidth = 0, int nHeight = 0, int nFrameDelay = 100);
	void SetDrawCxImageInfo(int x, int y, int nWidth = 0, int nHeight = 0, int nFrameDelay = 100);
	void SetDrawCxImageDialogInfo(CString word, int fontwidth, int fontheight,int fontweight,int x, int y, int nWidth = 0, int nHeight = 0, int xFont=0,int yFont=0, COLORREF fontColor = RGB(0, 0, 0));
	//根据制定的大小、颜色，创建绘制精灵
	DrawSprite(HDC hDC, int nWidth, int nHeight, COLORREF crColor = RGB(255, 255, 255));
	virtual ~DrawSprite();

	//声明成员访问方法
	int GetID() //获取绘制精灵图像编号
	{
		return m_ID;
	}
	HBITMAP GetBitmap()//获取位图句柄
	{
		return m_hbm;
	}
	void SetBitmap(HBITMAP hbm) //设置位图句柄
	{
		if (m_hbm != NULL)
			Release();        //释放资源
		m_hbm = hbm;
		BITMAP bm;
		GetObject(m_hbm, sizeof(BITMAP), &bm);
		m_nWidth = bm.bmWidth;
		m_nHeight = bm.bmHeight;
	}
	int GetHeight()
	{
		return m_nHeight;
	}

	int GetWidth()
	{
		return m_nWidth; 
	}

	void SetZOrder(int nZOrder) //设置Z顺序 
	{
		m_nZOrder = nZOrder;
	}

	int GetZOrder() {
		return m_nZOrder;
	}

	//释放资源
	void Release();

	//根据制定的大小、颜色创建位图
	BOOL Create(HDC hDC, int nWidth, int nHeight, COLORREF crColor = RGB(0, 0, 0));
	//加载文件中的位图
	BOOL Load(HINSTANCE hInstance, LPTSTR szFileName);
	//加载资源中的位图
	BOOL Load(HINSTANCE hInstance, UINT uRcid);
	//绘制位图，若设置bTrans为True，则按指定颜色crTransparent镂空位图
	void Draw(HDC hDC, int x, int y, BOOL bTrans = FALSE, COLORREF crTrans = RGB(0, 0, 0));
	//绘制为途中的一个矩形区域内的图像
	void DrawRect(HDC hDC, int x,int y, int nRectX, int nRectY, int nRectWidth, int nRectHeight, BOOL bTrans = FALSE, COLORREF crTrans = RGB(0, 0, 0));
	//绘制半透明位图，
	void DrawAlpha(HDC hDC, int x, int y, int nAlpha);
	//绘制灰度图片，可设置为镂空
	void DrawGray(HDC hDC, int x, int y, BOOL bTrans = FALSE, COLORREF crTransparent = RGB(0, 0, 0));
	//绘制半透明镂空位图
	void DrawTransAlpha(HDC hdcBack ,//背景DC
		int nXBack, //背景图左上角X坐标
		int nYBack,//
		int nWidthBack,
		int nHeightBack,
		int nXFore,//前景图左上角X坐标
		int nYFore,
		int nAlpha = 100, 
		COLORREF crTrans = RGB(0, 0, 0)  //镂空色

	);
		void DrawCxImageDialog(HDC hDC, CString word, int fontWidth, int fontHeight,int fontWeight,int x, int y, int nWidth = 0,int nHeight = 0,
			int xFont=0,int yFont=0, int nFrameDelay = 100,COLORREF fontColor=RGB(0,0,0));
	

	//下面是动画成员方法
	//初始化动画参数
	void InitAnima(int nRowCount, int nColCount, int nFrameDelay);
	//在hDC上的制定位置绘制第n行nCol列的图像，可设置为镂空
	void DrawRowCol(HDC hDC, int x, int y, int nRow, int nCol, BOOL bTrans = FALSE, COLORREF crTrans = RGB(0, 0, 0));
	//绘制动画帧
	void DrawAnima(HDC hDC, int x, int y, BOOL bTrans = FALSE, COLORREF crTrans = RGB(0, 0, 0));

	//精灵管理类绘图时所需方法
	//DrawTransAlpha
	void SetDrawAlphaInfo(int x, int y, int nAlpha = 255);

	void SetDrawInfo(int x, int y, BOOL bTrans = FALSE, COLORREF crTrans = RGB(0, 0, 0));

	void SetDrawAnimaInfo(int x, int y, int nRow, BOOL bTrans, COLORREF crTrans = RGB(0, 0, 0));

	void SetDrawGrayInfo(int x, int y, COLORREF crTrans = RGB(0, 0, 0));

	void SetDrawRectInfo(int x, int y, int nRectX, int nRectY, int nRectWidth, int nRectHeight,
		BOOL bTrans, COLORREF crTrans = RGB(0, 0, 0));

	void SetDrawTransAlphaInfo(int nXBack, int nYBack, int nWidthBack, int nHeightBack, int nXFore, int nYFore, int nAlpha = 255, COLORREF crTrans = RGB(0, 0, 0));

	//统一的绘图接口
	void CDrawSprite(HDC hDC);


	void SetVisible(BOOL bVisible)
	{
		m_bVisible = bVisible;
		if (m_hWndID!=NULL&&!bVisible)
		{
			ShowWindow(m_ObjecthWnd, SW_HIDE);
		}
		if (m_hWndID!=NULL&&bVisible)
		{
			ShowWindow(m_ObjecthWnd, SW_SHOW);
		}
	}

	BOOL GetVisible()
	{
		return m_bVisible;
	}
	BOOL floatsign=FALSE;
	void FloatEvent(BOOL isor)//位图悬停事件
	{
		if (m_cxImage!=NULL)
		{

		if (isor&&!floatsign)
		{
			m_cxImage->Gamma(1.5);
			floatsign = TRUE;
		}
		if (!isor&&floatsign)
		{
			m_cxImage->Gamma(1/1.5);
			floatsign = FALSE;
		}   
		}
	}
	HWND GethWnd(HWND parentHWND,int hID)
	{
		HWND hLink = GetDlgItem(parentHWND, 0);
		return m_ObjecthWnd;
	}
	void SethWnd(HWND hWnd)
	{
		m_ObjecthWnd = hWnd;
	}
	int GetObjectID()
	{
		if (m_hWndID != NULL)
		{

			return m_hWndID;
		}
	}
	void BindChildObject(HWND parenthWnd, int hWndID, DrawSprite *bmp);//位图与控件对象绑定
	void MergerImage(int x1,int x2,int lv);
	BOOL GetGifStatus()
	{
		return m_PlayGif;
	}
	void SetGifStatus(BOOL isor)
	{
		m_PlayGif = isor;
	}
private:
	//自定义的绘制镂空图的方法
	void TransBitmap(HDC hdcDest,//目标DC
		int nXDest, //目标左上角X坐标
		int nYDest,//
		int nWidthDest,
		int nHeightDest,
		HDC hdcSrc,
		int nXSrc,//源左上角X坐标
		int nYSrc,
		int nWidthSrc,
		int nHeightSrc,
		COLORREF crTrans = RGB(255,255,255)  //透明色

	);
};


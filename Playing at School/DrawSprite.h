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
		  //������Ա����
		  int m_nFrameWidth, m_nFrameHeight; //λͼ�й��ɶ����ĵ�֡ͼ��߶ȺͿ��
		  int m_nRowCount, m_nColCount; //Ϊ;�й��ɶ�����ϵ��֡���С�������
		  int m_nRow, m_nCol;
		  int m_nFrameDelay;
		  unsigned long m_lNextFrameTime;
		  BOOL m_bInitAnima;//�Ƿ��Ѿ���ʼ��
		  //��������ྫ������
		  DRAWTYPE m_dt;
		  int m_nX, m_nY;
		  BOOL m_bTrans;
		  COLORREF m_crTrans;//͸��ɫ
		  int m_nAlpha;
		  //����DrawTransAlpha��������ͼ���Ͻ�ͼ����Ⱥ͸߶�
		  int m_nXBack, m_nYBack, m_nWidthBack, m_nHeightBack;
		  //����drawrect����
		  int m_nRectX, m_nRectY, m_nRectWidth, m_nRectHeight;
		  BOOL m_bVisible;
		  CString m_dialogword;
		  CxImage *m_cxImage;//cxImage����ָ��'
		  CxImage *m_OriImg;
		  int m_nXFont, m_nYFont, m_nFontHeight, m_nFontWeight,m_nFontWidth;
		  COLORREF m_FontColor;
		  int m_hWndID;
		  HWND m_ObjecthWnd;
		  BOOL m_PlayGif = FALSE;

public:
	DrawSprite();  

	DrawSprite(HINSTANCE hInstance, LPTSTR szFileNmae); //����λͼ�ļ���������ƾ���
	DrawSprite(HINSTANCE hInstance, UINT uRcID); //����λͼ��ԴID�������ƾ���
	//�������飬��������ͼ���ļ�szFileName���������Ƿ���ת��ΪHbitmap���Ա���ԭ�͵ķ��������
	DrawSprite(LPTSTR szFileName, BOOL bConvertBmp = FALSE);


	//��ȡCxImage����
	CxImage *GetCxImage()const
	{
		return m_cxImage;
	}

	void SetCxImage(CxImage *image)
	{
		m_cxImage = image;
	}
	//����ͼ���ļ�szFileName���������Ƿ���ת��ΪHbitmap���Ա���ԭ�͵ķ��������
	BOOL LoadCxImage(LPTSTR szFileName, BOOL bConvertBmp = FALSE);
	//����x��yΪ���Ͻǣ���nWidth����nHeight�ķ�Χ�ڻ���ͼ�񣬲������ö���֡�ӳ�ʱΪnFrameDelay
	void DrawCxImage(HDC hDC, int x, int y, int nWidth = 0, int nHeight = 0, int nFrameDelay = 100);
	void SetDrawCxImageInfo(int x, int y, int nWidth = 0, int nHeight = 0, int nFrameDelay = 100);
	void SetDrawCxImageDialogInfo(CString word, int fontwidth, int fontheight,int fontweight,int x, int y, int nWidth = 0, int nHeight = 0, int xFont=0,int yFont=0, COLORREF fontColor = RGB(0, 0, 0));
	//�����ƶ��Ĵ�С����ɫ���������ƾ���
	DrawSprite(HDC hDC, int nWidth, int nHeight, COLORREF crColor = RGB(255, 255, 255));
	virtual ~DrawSprite();

	//������Ա���ʷ���
	int GetID() //��ȡ���ƾ���ͼ����
	{
		return m_ID;
	}
	HBITMAP GetBitmap()//��ȡλͼ���
	{
		return m_hbm;
	}
	void SetBitmap(HBITMAP hbm) //����λͼ���
	{
		if (m_hbm != NULL)
			Release();        //�ͷ���Դ
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

	void SetZOrder(int nZOrder) //����Z˳�� 
	{
		m_nZOrder = nZOrder;
	}

	int GetZOrder() {
		return m_nZOrder;
	}

	//�ͷ���Դ
	void Release();

	//�����ƶ��Ĵ�С����ɫ����λͼ
	BOOL Create(HDC hDC, int nWidth, int nHeight, COLORREF crColor = RGB(0, 0, 0));
	//�����ļ��е�λͼ
	BOOL Load(HINSTANCE hInstance, LPTSTR szFileName);
	//������Դ�е�λͼ
	BOOL Load(HINSTANCE hInstance, UINT uRcid);
	//����λͼ��������bTransΪTrue����ָ����ɫcrTransparent�ο�λͼ
	void Draw(HDC hDC, int x, int y, BOOL bTrans = FALSE, COLORREF crTrans = RGB(0, 0, 0));
	//����Ϊ;�е�һ�����������ڵ�ͼ��
	void DrawRect(HDC hDC, int x,int y, int nRectX, int nRectY, int nRectWidth, int nRectHeight, BOOL bTrans = FALSE, COLORREF crTrans = RGB(0, 0, 0));
	//���ư�͸��λͼ��
	void DrawAlpha(HDC hDC, int x, int y, int nAlpha);
	//���ƻҶ�ͼƬ��������Ϊ�ο�
	void DrawGray(HDC hDC, int x, int y, BOOL bTrans = FALSE, COLORREF crTransparent = RGB(0, 0, 0));
	//���ư�͸���ο�λͼ
	void DrawTransAlpha(HDC hdcBack ,//����DC
		int nXBack, //����ͼ���Ͻ�X����
		int nYBack,//
		int nWidthBack,
		int nHeightBack,
		int nXFore,//ǰ��ͼ���Ͻ�X����
		int nYFore,
		int nAlpha = 100, 
		COLORREF crTrans = RGB(0, 0, 0)  //�ο�ɫ

	);
		void DrawCxImageDialog(HDC hDC, CString word, int fontWidth, int fontHeight,int fontWeight,int x, int y, int nWidth = 0,int nHeight = 0,
			int xFont=0,int yFont=0, int nFrameDelay = 100,COLORREF fontColor=RGB(0,0,0));
	

	//�����Ƕ�����Ա����
	//��ʼ����������
	void InitAnima(int nRowCount, int nColCount, int nFrameDelay);
	//��hDC�ϵ��ƶ�λ�û��Ƶ�n��nCol�е�ͼ�񣬿�����Ϊ�ο�
	void DrawRowCol(HDC hDC, int x, int y, int nRow, int nCol, BOOL bTrans = FALSE, COLORREF crTrans = RGB(0, 0, 0));
	//���ƶ���֡
	void DrawAnima(HDC hDC, int x, int y, BOOL bTrans = FALSE, COLORREF crTrans = RGB(0, 0, 0));

	//����������ͼʱ���跽��
	//DrawTransAlpha
	void SetDrawAlphaInfo(int x, int y, int nAlpha = 255);

	void SetDrawInfo(int x, int y, BOOL bTrans = FALSE, COLORREF crTrans = RGB(0, 0, 0));

	void SetDrawAnimaInfo(int x, int y, int nRow, BOOL bTrans, COLORREF crTrans = RGB(0, 0, 0));

	void SetDrawGrayInfo(int x, int y, COLORREF crTrans = RGB(0, 0, 0));

	void SetDrawRectInfo(int x, int y, int nRectX, int nRectY, int nRectWidth, int nRectHeight,
		BOOL bTrans, COLORREF crTrans = RGB(0, 0, 0));

	void SetDrawTransAlphaInfo(int nXBack, int nYBack, int nWidthBack, int nHeightBack, int nXFore, int nYFore, int nAlpha = 255, COLORREF crTrans = RGB(0, 0, 0));

	//ͳһ�Ļ�ͼ�ӿ�
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
	void FloatEvent(BOOL isor)//λͼ��ͣ�¼�
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
	void BindChildObject(HWND parenthWnd, int hWndID, DrawSprite *bmp);//λͼ��ؼ������
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
	//�Զ���Ļ����ο�ͼ�ķ���
	void TransBitmap(HDC hdcDest,//Ŀ��DC
		int nXDest, //Ŀ�����Ͻ�X����
		int nYDest,//
		int nWidthDest,
		int nHeightDest,
		HDC hdcSrc,
		int nXSrc,//Դ���Ͻ�X����
		int nYSrc,
		int nWidthSrc,
		int nHeightSrc,
		COLORREF crTrans = RGB(255,255,255)  //͸��ɫ

	);
};


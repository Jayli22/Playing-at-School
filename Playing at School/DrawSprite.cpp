
#include "DrawSprite.h"
#include "CustomObject.h"

#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"cximagecrtu.lib")
int DrawSprite::m_nNewID = 1; //��ʼ�����ƾ�����

DrawSprite::DrawSprite(LPTSTR szFilename, BOOL bConvertBmp /* = FALSE */)
{
	LoadCxImage(szFilename,bConvertBmp);
	m_ID = m_nNewID;
	m_nNewID++;
	m_nZOrder = 0;

}

BOOL DrawSprite::LoadCxImage(LPTSTR szFileName, BOOL bConvertBmp /* = FALSE */)
{
	Release();
	m_cxImage = new CxImage();
	m_cxImage->Load(szFileName);
	m_OriImg = m_cxImage;

	if (!m_cxImage->IsValid())
	{
		return FALSE;
	}
	if (m_cxImage->GetType()==CXIMAGE_FORMAT_GIF)
	{
		m_cxImage->SetRetreiveAllFrames(true);
		m_cxImage->SetFrame(m_cxImage->GetNumFrames() - 1);
		m_cxImage->Load(szFileName,CXIMAGE_FORMAT_GIF);
		m_lNextFrameTime = 0;
	}
	if (!m_PlayGif&&m_cxImage->GetType() == CXIMAGE_FORMAT_GIF)
	{
		m_cxImage->Copy(*m_cxImage->GetFrame(0));
	}
	if (bConvertBmp)
	{
		m_hbm = m_cxImage->MakeBitmap();
	}
	m_nWidth = m_cxImage->GetWidth();
	m_nHeight = m_cxImage->GetHeight();
	m_bVisible = TRUE;
}
long n = 0;
//��x,yΪ���Ͻ�
void DrawSprite::DrawCxImage(HDC hDC, int x, int y, int nWidth /* = 0 */, int nHeight /* = 0 */, int nFrameDelay /* = 100 */)
{
	if (m_cxImage == NULL)
	{
		return;
	}
	if (!m_bVisible)
		return;
	int ImaType = m_cxImage->GetType();
	//����GIF�������貽��
    if (ImaType == CXIMAGE_FORMAT_GIF&&m_PlayGif)
	{	
		if (timeGetTime() >= m_lNextFrameTime)
		{
			m_lNextFrameTime = timeGetTime() + nFrameDelay;
			long m = m_cxImage->GetNumFrames();//��ȡ��֡��
			if (n >= m)
			{
				n = 0; //�����һ֡��������������Χ������һ֡Ϊ��0֡
				m_PlayGif = FALSE;
				m_cxImage->Copy(*m_cxImage->GetFrame(0));
			}
			if (m_cxImage->GetFrame(n)&&m_PlayGif)
			{
				m_cxImage->Copy(*m_cxImage->GetFrame(n));//����ͼ��Ϊ��һ֡
				n++;
			}

		}
	}
	m_cxImage->Draw(hDC, x, y, nWidth, nHeight);
}


void DrawSprite::DrawCxImageDialog(HDC hDC, CString word,int fontWidth,int fontHeight,int fontWeight,int x, int y,
	int nWidth /* = 0 */,int nHeight /* = 0 */, 
	int xFont/* =0 */,int yFont/* =0 */, int nFrameDelay /* = 100 */,COLORREF fontColor/* =RGB(0,0,0) */)
{
	if (!m_bVisible)
		return;
	//m_cxImage->Save(L"..\\Resource\\mdialog.png", CXIMAGE_FORMAT_PNG);
	CxImage tmpimg;
	tmpimg = *m_cxImage;
	CxImage::CXTEXTINFO textword;
	m_cxImage->InitTextInfo(&textword);
	_stprintf(textword.lfont.lfFaceName, _T("Microsoft YaHei UI"));
	textword.lfont.lfCharSet = GB2312_CHARSET;
	textword.lfont.lfHeight = fontHeight;
	textword.lfont.lfWidth = fontWidth;
	textword.lfont.lfQuality = CLEARTYPE_QUALITY;
	textword.lfont.lfWeight = fontWeight;    //������������ϸ
	textword.lfont.lfItalic = 0;   
	textword.lfont.lfUnderline = 0;  //�Ƿ���»���
	textword.fcolor = fontColor;   //������ɫ
	textword.bcolor = RGB(0, 80, 160);  
	textword.opaque = 0; //����͸����͸��
	textword.b_opacity = (float)(0) / (float)100.; //͸����
	textword.b_round = (BYTE)10; //��������Ϊ�������ΰ뾶
	textword.smooth = (BYTE)1; //ƽ��ѡ����ı�
	LPTSTR tmpword = (LPTSTR)(LPCTSTR)word;
	_stprintf(textword.text, tmpword);
	tmpimg.DrawStringEx(hDC, xFont, yFont, &textword);
	tmpimg.Draw(hDC, x, y, nWidth, nHeight);
}


//��������drawcximagedialog�����Ĳ���
void DrawSprite::SetDrawCxImageDialogInfo(CString word,int fontwidth,int fontheight,int fontweight,int x, int y, 
	int nWidth /* = 0 */, int nHeight /* = 0 */, 
	int xFont/* =0 */,int yFont/* =0 */, COLORREF fontColor /* = RGB(0, 0, 0) */)
{
	m_dt = DT_CXIMAGEDIALOG;
	m_nX = x;
	m_nY = y;
	m_dialogword = word;
	m_nFontHeight = fontheight;
	m_nFontWeight = fontweight;
	m_nFontWidth = fontwidth;
	if (fontColor!=RGB(0,0,0))
	{
		m_FontColor = fontColor;

	}
	if (nWidth != 0)
	{
		m_nWidth = nWidth;
	}
	if (nHeight != 0)
	{
		m_nHeight = nHeight;
	}
	if (xFont!=0)
	{
		m_nXFont = xFont;
	}
	if (yFont!=0)
	{
		m_nYFont = yFont;
	}
}


//��������drawcximage�����Ĳ���
void DrawSprite::SetDrawCxImageInfo(int x, int y, int nWidth /* = 0 */, int nHeight /* = 0 */, int nFrameDelay /* = 100 */)
{
	m_dt = DT_CXIMAGE;
	m_nX = x;
	m_nY = y;
	if (nWidth!=0)
	{
		m_nWidth = nWidth;
	}
	if (nHeight!=0)
	{
		m_nHeight = nHeight;
	}
	m_nFrameDelay = nFrameDelay;
}


DrawSprite::DrawSprite()
{
	m_hbm = NULL;
	m_ID = m_nNewID;
	m_nNewID++;
	m_nZOrder = 0;
}

//��ָ��λͼ�ļ�����DrawSpriteʵ��
DrawSprite::DrawSprite(HINSTANCE hInstance, LPTSTR szFileNmae)
{
	//����ָ����λͼ�ļ�
	Load(hInstance, szFileNmae);
	m_ID = m_nNewID;
	m_nNewID++;
	m_nZOrder = 0;
}
//��ָ��λͼ��Դ����DrawSpriteʵ��
DrawSprite::DrawSprite(HINSTANCE hInstance, UINT uRcID)
{
	//����ָ����λͼ�ļ�
	Load(hInstance, uRcID);
	m_ID = m_nNewID;
	m_nNewID++;
	m_nZOrder = 0;
}

DrawSprite::DrawSprite(HDC hDC, int nWidth, int nHeight, COLORREF crColor) {
	Create(hDC, nWidth, nHeight, crColor);
	m_ID = m_nNewID;
	m_nNewID++;
	m_nZOrder = 0;

}
//��������
DrawSprite::~DrawSprite()
{
	Release();
}


void DrawSprite::Release()
{
	if (m_hbm!=NULL)
	{
		DeleteObject(m_hbm);
		m_hbm = NULL;
	}
	if (GetDlgItem(GetParent(m_ObjecthWnd), m_hWndID) != NULL)
	{
		ShowWindow(m_ObjecthWnd, SW_HIDE);
	}
}
//use specified size and color to create bitmap
BOOL DrawSprite::Create(HDC hDC, int nWidth, int nHeight, COLORREF crColor /* = RGB(0, 0, 0) */)
{
	Release();

	m_hbm = CreateCompatibleBitmap(hDC, nWidth, nHeight);
	if (m_hbm == NULL)
	{
		return FALSE;
	}
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	//ͨ����λͼ�л���������������λͼ
	HDC hdcMem = CreateCompatibleDC(hDC);//���������豸
	HBRUSH hBrush = CreateSolidBrush(crColor);// define solidbrush 
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, m_hbm);
	RECT rc = { 0, 0, nWidth, nHeight };
	FillRect(hdcMem, &rc, hBrush);//draw fill rectangle 
	//clean temporary object, release resource 
	SelectObject(hdcMem, hOldBitmap);
	DeleteDC(hdcMem);
	DeleteObject(hBrush);

	return TRUE;
}

//load specific  bitmap file
BOOL DrawSprite::Load(HINSTANCE hInstance, LPTSTR szFileName)
{
	Release();
	m_hbm = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//set bitmap width and height by bitmap structure 
	BITMAP bm;
	GetObject(m_hbm, sizeof(BITMAP), &bm);
	m_nWidth = bm.bmWidth;
	m_nHeight = bm.bmHeight;
	return TRUE;
}

//load bitmap resource
BOOL DrawSprite::Load(HINSTANCE hInstance, UINT uRcid)
{
	Release();
	m_hbm = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(uRcid), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);	
	BITMAP bm;
	GetObject(m_hbm, sizeof(BITMAP), &bm);
	m_nWidth = bm.bmWidth;
	m_nHeight = bm.bmHeight;
	return TRUE;
}

//draw bitmap at position (x,y)designed by hDC,if bTrans is true, set crTrans as transparent color
void DrawSprite::Draw(HDC hDC, int x, int y, BOOL bTrans /* = FALSE */, COLORREF crTrans /* = RGB(0, 0, 0) */)
{
	if (m_hbm!=NULL)
	{
		HDC hdcMem = CreateCompatibleDC(hDC);
		HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, m_hbm);

		if (bTrans)
		{
			//output transparent bitmap
			TransparentBlt(hDC, x, y, m_nWidth, m_nHeight, hdcMem, 0, 0, m_nWidth, m_nHeight, crTrans);
		} 
		else
		{
			//output opaque bitmap
			BitBlt(hDC, x, y, m_nWidth, m_nHeight, hdcMem, 0, 0, SRCCOPY);
		}
		SelectObject(hdcMem, hOldBmp);
		DeleteObject(hOldBmp);
		DeleteDC(hdcMem);
	} 
}
// draw specific img in rectangle area at designed position(x,y),top left corner coordinate (nRectX,nRectY)
void DrawSprite::DrawRect(HDC hDC, int x, int y, int nRectX, int nRectY, int nRectWidth, int nRectHeight, BOOL bTrans /* = FALSE */, COLORREF crTrans /* = RGB(0, 0, 0) */)
{
	if (m_hbm!=NULL)
	{
		HDC hdcMem = CreateCompatibleDC(hDC);
		HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, m_hbm);
		if (bTrans)
		{
			TransparentBlt(hDC, x, y, nRectWidth, nRectHeight, hdcMem,
				nRectX, nRectY, nRectWidth, nRectHeight, crTrans);
		} 
		else
		{
			BitBlt(hDC, x, y, nRectWidth, nRectHeight, hdcMem, 0, 0, SRCCOPY);
		}
		SelectObject(hdcMem, hOldBmp);
		DeleteDC(hdcMem);	
	}
}

//��hDC��ָ��λ��(x,y)���͸����ΪnAlpha(0~255)�İ�͸��ͼ��
void DrawSprite::DrawAlpha(HDC hDC, int x, int y, int nAlpha)
{
	HDC hdcMem = CreateCompatibleDC(hDC);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, m_hbm);
	//����bf�ṹ
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = nAlpha;
	bf.AlphaFormat = 0x00;

	//�����͸��ͼ��
	AlphaBlend(hDC, x, y, m_nWidth, m_nHeight, hdcMem, 0, 0, GetWidth(), GetHeight(), bf);

	SelectObject(hdcMem, hOldBmp);
	DeleteDC(hdcMem);
}

//���ư�͸���ο�λͼ
void DrawSprite::DrawTransAlpha(HDC hdcBack, int nXBack, int nYBack, int nWidthBack, int nHeightBack, int nXFore, int nYFore, int nAlpha /* = 100 */,
	COLORREF crTrans /* = RGB(0, 0, 0) */)
{
	if (m_hbm!=NULL)
	{
		HDC hdcMem = CreateCompatibleDC(hdcBack);

		//����һ���뱳��ͬ����С����ʱͼ��
		RECT rBackRect = { nXBack,nYBack,nWidthBack,nHeightBack };
		HBITMAP hbmTmp = CreateCompatibleBitmap(hdcBack, nWidthBack, nHeightBack);
		HBITMAP hbmBK = (HBITMAP)SelectObject(hdcBack, hbmTmp);//�������ͼ��
		RECT rForeRect = { nXFore,nYFore,nXFore + m_nWidth,nYFore + m_nHeight };
		RECT rTransRect, rTransRect2;
//��ȡǰ�������뱳�����εĽ������粻�ཻ������Ҫ������ɫ����
		if (IntersectRect(&rTransRect,&rBackRect,&rForeRect))
		{
			BITMAP bm, bmBk;
			GetObject(m_hbm, sizeof(BITMAP), &bm);
			BYTE *px = new unsigned char[bm.bmHeight*bm.bmWidthBytes];//��������
			//ȡ��Դλͼ�����ص��RGBֵ�������px������
			GetBitmapBits(m_hbm, bm.bmHeight*bm.bmWidthBytes, px);
			GetObject(hbmBK, sizeof(BITMAP),&bmBk);

			BYTE *pxBk = new unsigned char[bmBk.bmHeight*bmBk.bmWidthBytes];
			//ȡ�ñ���λͼ�����ص��RGBֵ������px������
			GetBitmapBits(hbmBK, bmBk.bmHeight*bmBk.bmWidthBytes, pxBk);

			rTransRect2 = rTransRect;
			OffsetRect(&rTransRect2, -rForeRect.left, -rForeRect.top); //ƫ�ƾ�������
			
			int pb = bm.bmBitsPixel / 8;//��ȡÿ������ռ�ֽ���
			int pbBk = bmBk.bmBitsPixel / 8;

			//dy1Ϊ����ͼ����������dy2Ϊǰ��ͼ��������
			int dx1, dx2, dy1, dy2;
			//ѭ�������ؽ��м��㣬������ǰ������Ҫ���м�������طֱ��ڸ��Զ�Ӧ�ľ���rT��rT2�ķ�Χ��ѭ��

			for (dy1=rTransRect.top,dy2=rTransRect2.top;dy1<rTransRect.bottom;dy1++,dy2++)
			{
				for (dx1 = rTransRect.left, dx2 = rTransRect2.left;dx1 < rTransRect.right; dx1++, dx2++)
				{
					//���㱳��ͼ������ʼλ��
					int nBackRGB_B = dy1*bmBk.bmWidthBytes + dx1*pbBk;
					int nForeRGB_B = dy2*bm.bmWidthBytes + dx2*pb;
					if (RGB(px[nForeRGB_B+2],px[nForeRGB_B+1],px[nForeRGB_B])!=crTrans)
					{
						//��pxBk��Bɫ��ֵ����nAlpha ����px���
						pxBk[nBackRGB_B] = (px[nForeRGB_B] * nAlpha + pxBk[nBackRGB_B] * (255 - nAlpha)) / 255;
						//��pxBk��Gɫ��ֵ����nAlpha����px���
						pxBk[nBackRGB_B] = (px[nForeRGB_B+1] * nAlpha + pxBk[nBackRGB_B+1] * (255 - nAlpha)) / 255;
						pxBk[nBackRGB_B] = (px[nForeRGB_B+2] * nAlpha + pxBk[nBackRGB_B+2] * (255 - nAlpha)) / 255;
					}
				}
			}
			SetBitmapBits(hbmTmp, bmBk.bmHeight*bmBk.bmWidthBytes, pxBk);

			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmTmp);
			BitBlt(hdcBack, 0, 0, rBackRect.right, rBackRect.bottom, hdcMem, 0, 0, SRCCOPY);

			delete[] px;
			delete[] pxBk;
			SelectObject(hdcMem, hbmOld);
		}
		DeleteObject(hbmTmp);
		DeleteDC(hdcMem);
	} 
}

//���ƻҶ��ο�ͼ
void DrawSprite::DrawGray(HDC hDC, int x, int y, BOOL bTrans /* = FALSE */, COLORREF crTransparent /* = RGB(0, 0, 0) */)
{
	if (m_hbm!=NULL)
	{
		HDC hdcMem = CreateCompatibleDC(hDC);
		BITMAP bm;
		GetObject(m_hbm, sizeof(BITMAP), &bm);
		BYTE *px = new unsigned char[bm.bmHeight*bm.bmWidthBytes];
		GetBitmapBits(m_hbm, bm.bmHeight*bm.bmWidthBytes, px);

		int pb = bm.bmBitsPixel / 8;
		//ѭ������Ҷ�ֵ
		for (int dy=0;dy<bm.bmHeight;dy++)
		{
			for (int dx=0;dx<bm.bmWidth;dx++)
			{
				int rgb_b = dy*bm.bmWidthBytes + dx*pb;
				px[rgb_b] = (px[rgb_b] * 299 + px[rgb_b + 1] * 587 + px[rgb_b + 2] * 114) / 1000;
				px[rgb_b+1] = px[rgb_b];
				px[rgb_b + 2] = px[rgb_b];
			}
		}
		HBITMAP hbmTmp = CreateCompatibleBitmap(hDC, bm.bmWidth, bm.bmHeight);
		SetBitmapBits(hbmTmp, bm.bmHeight*bm.bmWidthBytes, px);

		HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, hbmTmp);

		if (bTrans)
		{
			//���͸��λͼ
			TransparentBlt(hDC, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, crTransparent);
		}
		else
			//�����͸��λͼ
			BitBlt(hDC, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hOldBmp);
		DeleteObject(hbmTmp);
		DeleteDC(hdcMem);
	}
}

//����͸���ο�λͼ
void DrawSprite::TransBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXSrc, int nYSrc, int nWidthSrc,
	int nHeightSrc, COLORREF crTrans /* = RGB(255,255,255) */)
{
	//��������λͼ
	HBITMAP hbmTmp = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);
	//������ɫλͼ
	HBITMAP hbmMask = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);

	HDC hdcMem = CreateCompatibleDC(hdcDest);
	HDC hdcMask = CreateCompatibleDC(hdcDest);

	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmTmp);
	HBITMAP hbmMaskOld = (HBITMAP)SelectObject(hdcMask, hbmMask);

	//��Դdc�е�λͼ���Ƶ���ʱ�豸������
	if (nWidthDest==nWidthSrc&&nHeightDest==nHeightSrc)
	{
		BitBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXSrc, nYSrc, SRCCOPY);
	}
	else
	{
		StretchBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXSrc, nYSrc, nWidthSrc, nHeightSrc, SRCCOPY);
	}
	//����͸��ɫ
	SetBkColor(hdcMem, crTrans);
	//����͸������Ϊ��ɫ����������Ϊ��ɫ���ɰ�λͼ
	BitBlt(hdcMask, 0, 0, nWidthDest, nHeightDest, hdcMem, 0, 0, SRCCOPY);
	//����͸������Ϊ��ɫ���������򱣳ֲ����λͼ
	SetBkColor(hdcMem, RGB(0, 0, 0));
	SetTextColor(hdcMem, RGB(255, 255, 255));
	BitBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcMask, 0, 0, SRCAND);
	//͸�����ֶ�Ӧ�ı������ֲ���,�������ֱ�ɺ�ɫ
	SetBkColor(hdcDest, RGB(255, 255, 255));
	SetTextColor(hdcDest, RGB(0, 0, 0));
	BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMask, 0, 0, SRCAND);
	//�����㣬��������Ч��
	BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMem, 0, 0, SRCPAINT);

	//clean
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
	SelectObject(hdcMask, hbmMaskOld);
	DeleteDC(hdcMask);
	DeleteObject(hbmTmp);
	DeleteObject(hbmMask);
}


//ʹ��nRowCount,��nColCount������֡��ʾ��ʱnFrameDelay����ʼ����������
void DrawSprite::InitAnima(int nRowCount, int nColCount, int nFrameDelay) {
	if (m_hbm != NULL)
	{
		return;
	}
	m_nRowCount = nRowCount;
	m_nColCount = nColCount;

	m_nFrameWidth = m_nWidth / nColCount; 
	m_nFrameHeight = m_nHeight / nRowCount;

	m_lNextFrameTime = nFrameDelay + timeGetTime();
	m_nFrameDelay = nFrameDelay;
	m_nCol = 0;
	m_nRow = 0;
	m_bInitAnima = TRUE;
}

//���ƶ�����������(x,y)���괦����һ������֡���棬֡�����еļ�ʱ����ѭ������ʱ�Զ�����
void DrawSprite::DrawAnima(HDC hDC, int x, int y, BOOL bTrans /* = FALSE */, COLORREF crTrans /* = RGB(0, 0, 0) */)
{
	if (!m_bVisible)
		return;
	if (m_hbm==NULL||!m_bInitAnima)
	{
		return;
	}
	if (timeGetTime()>m_lNextFrameTime)
	{
		m_lNextFrameTime = timeGetTime() + m_nFrameDelay;
		m_nCol++;
		if (m_nCol>=m_nColCount)
		{
			m_nCol = 0;
		}
	}
	DrawRowCol(hDC, x, y, m_nRow, m_nCol, bTrans, crTrans);
}

//��hDCָ��λ�û���ͼ���nRow��nCol�е�֡���棬������ο�ͼ������crTransparentΪ͸��ɫ
void DrawSprite::DrawRowCol(HDC hDC, int x, int y, int nRow, int nCol, BOOL bTrans /* = FALSE */, COLORREF crTrans /* = RGB(0, 0, 0) */) {
	if (!m_bVisible)
	{
		return;
	}
	if (m_hbm==NULL||!m_bInitAnima)
	{
		return;
	}
	HDC hdcMem = CreateCompatibleDC(hDC);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, m_hbm);

	if (bTrans)
	{
		//���͸��λͼ
		TransparentBlt(hDC, x, y, m_nFrameWidth, m_nFrameHeight, hdcMem, m_nFrameWidth*nCol, m_nFrameHeight*nRow, m_nFrameWidth, m_nFrameHeight,crTrans);
	}
	else
		//�����͸��λͼ
		BitBlt(hDC,x,y, m_nFrameWidth, m_nFrameHeight, hdcMem, m_nFrameWidth*nCol, m_nFrameHeight*nRow, SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmOld);
	DeleteDC(hdcMem);
}

//������������跽��
void DrawSprite::SetDrawAlphaInfo(int x, int y, int nAlpha /* = 255 */)
{
	m_dt = DT_ALPHA;
	m_nX = x;
	m_nY = y;
	m_nAlpha = nAlpha;
}

void DrawSprite::SetDrawInfo(int x, int y, BOOL bTrans /* = FALSE */, COLORREF crTrans /* = RGB(0, 0, 0) */)
{
	m_dt = DT_DRAW;
	m_nX = x;
	m_nY = y;
	m_bTrans = bTrans;
	m_crTrans = crTrans;
}

//��������DrawAnima������
void DrawSprite::SetDrawAnimaInfo(int x, int y, int nRow, BOOL bTrans, COLORREF crTrans /* = RGB(0, 0, 0) */)
{
	m_dt = DT_ANIMA;
	m_nX = x;
	m_nY = y;
	m_bTrans = bTrans;
	m_crTrans = crTrans;
	m_nRow = nRow;
}

void DrawSprite::SetDrawGrayInfo(int x, int y, COLORREF crTrans /* = RGB(0, 0, 0) */)
{
	m_dt = DT_GRAY;
	m_nX = x;
	m_nY = y;
	m_bTrans = TRUE;
	m_crTrans = crTrans;
}

void DrawSprite::SetDrawRectInfo(int x, int y, int nRectX, int nRectY, int nRectWidth, int nRectHeight, BOOL bTrans, COLORREF crTrans /* = RGB(0, 0, 0) */)
{
	m_dt = DT_RECT;
	m_nX = x;
	m_nY = y;
	m_nRectX = nRectX;
	m_nRectY = nRectY;
	m_nRectWidth = nRectWidth;
	m_nRectHeight = nRectHeight;
	m_bTrans = bTrans;
	m_crTrans = crTrans;
	m_crTrans = crTrans;
}

void DrawSprite::SetDrawTransAlphaInfo(int nXBack, int nYBack, int nWidthBack, int nHeightBack, int nXFore, int nYFore,
	int nAlpha /* = 255 */, COLORREF crTrans /* = RGB(0, 0, 0) */)
{
	m_dt = DT_TRANSALPHA;
	m_nX = nXFore;
	m_nY = nYFore;
	m_nXBack = nXBack;
	m_nYBack = nYBack;
	m_nWidthBack = nWidthBack;
	m_nWidthBack = nHeightBack;
	m_nAlpha = nAlpha;
	m_crTrans = crTrans;
}

//ͳһ�Ļ�ͼ�ӿ�
void DrawSprite::CDrawSprite(HDC hDC)
{
	switch (m_dt)
	{
	case DT_DRAW:
		Draw(hDC, m_nX, m_nY, m_bTrans, m_crTrans);
		break;
	case DT_ALPHA:
		DrawAlpha(hDC, m_nX, m_nY, m_nAlpha);
		break;
	case DT_GRAY:
		DrawGray(hDC, m_nX, m_nY, m_bTrans, m_crTrans);
		break;
	case DT_TRANSALPHA:
		DrawTransAlpha(hDC, m_nXBack, m_nYBack, m_nWidthBack, m_nHeightBack, m_nX, m_nY, m_nAlpha, m_crTrans);
		break;
	case DT_ANIMA:
		DrawAnima(hDC, m_nX, m_nY, m_bTrans, m_crTrans);
		break;
	case DT_RECT:
		DrawRect(hDC, m_nX, m_nY, m_nRectX, m_nRectY, m_nRectWidth, m_nRectHeight, m_bTrans, m_crTrans);
		break;
	case DT_CXIMAGE:
		DrawCxImage(hDC, m_nX, m_nY, m_nWidth, m_nHeight, m_nFrameDelay);
		break;
	case DT_CXIMAGEDIALOG:
		DrawCxImageDialog(hDC, m_dialogword,m_nFontWidth,m_nFontHeight,m_nFontWeight,m_nX, m_nY, m_nWidth, m_nHeight,m_nXFont,m_nYFont, m_nFrameDelay,m_FontColor);
	default:
		break;
	}
}




void DrawSprite::BindChildObject(HWND parenthWnd, int hWndID, DrawSprite *bmp){
	if (GetDlgItem(parenthWnd, hWndID) == NULL)
	{
		m_hWndID = hWndID;
		CString str;
		str.Format(L"%d", m_hWndID);
		m_ObjecthWnd = CreateCustomObject(str,L"", DT_CENTER, m_nX, m_nY, m_nWidth, m_nHeight, parenthWnd, hWndID, bmp);
		//SubclassCustomObject(m_ObjecthWnd);
		ShowWindow(m_ObjecthWnd, SW_SHOW);
	}
	//else if(bmp->GetVisible())
	//{
	//	m_hWndID = hWndID;
	//	CString str;
	//	str.Format(L"%d", m_hWndID);
	//	m_ObjecthWnd = CreateCustomObject(str, L"", DT_CENTER, m_nX, m_nY, m_nWidth, m_nHeight, parenthWnd, hWndID, bmp);
	//	//SubclassCustomObject(m_ObjecthWnd);
	//	ShowWindow(m_ObjecthWnd, SW_SHOW);
	//}

	//GetWindowRect(hLink, &rect);
	//MapWindowPoints(NULL, hWnd, (LPPOINT)&rect, 2);
}
void DrawSprite::MergerImage(int x1,int x2,int hp)
{
	CxImage img1, img2, img3;
	int h1, w1, h2, w2, h3, w3, bpp;
	
	switch (hp)
	{
	case 1:
		img3.Load(L"..\\Resource\\lv1.png");
		break;
	case 2:
		img3.Load(L"..\\Resource\\lv2.png");
		break;
	case 3:
		img3.Load(L"..\\Resource\\lv3.png");
		break;
	case 4:
		img3.Load(L"..\\Resource\\lv4.png");
		break;
	case 5:
		img3.Load(L"..\\Resource\\lv5.png");
		break;
	case 6:
		img3.Load(L"..\\Resource\\lv6.png");
		break;
	case 7:
		img3.Load(L"..\\Resource\\lv7.png");
		break;
	case 8:
		img3.Load(L"..\\Resource\\lv8.png");
		break;
	case 9:
		img3.Load(L"..\\Resource\\lv9.png");
		break;
	default:
		break;
	}

	img3.Resample(25,10);
	img1.Load(L"..\\Resource\\hp.png");
	img2.Load(L"..\\Resource\\mp.png");

	h1 = 10;
	w1 = x1;

	h2 = 10;
	w2 = x2;


	CxImage smallImg1;
	CxImage smallImg2;



	img1.Crop(0, 0, w1, 7, &smallImg1);
	img2.Crop(0, 0, w2, 7, &smallImg2);
	m_cxImage->Copy(*m_OriImg);
	//m_cxImage->MixFrom(smallImg1,2,13);
	m_cxImage->Mix(smallImg1, CxImage::ImageOpType::OpScreen,-2, -13);
	m_cxImage->Mix(smallImg2, CxImage::ImageOpType::OpScreen,-2, -4);
	m_cxImage->Mix(img3, CxImage::OpScreen, -2, -23);
}

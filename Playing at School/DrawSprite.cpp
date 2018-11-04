
#include "DrawSprite.h"
#include "CustomObject.h"

#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"cximagecrtu.lib")
int DrawSprite::m_nNewID = 1; //初始化绘制精灵编号

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
//以x,y为左上角
void DrawSprite::DrawCxImage(HDC hDC, int x, int y, int nWidth /* = 0 */, int nHeight /* = 0 */, int nFrameDelay /* = 100 */)
{
	if (m_cxImage == NULL)
	{
		return;
	}
	if (!m_bVisible)
		return;
	int ImaType = m_cxImage->GetType();
	//绘制GIF动画所需步骤
    if (ImaType == CXIMAGE_FORMAT_GIF&&m_PlayGif)
	{	
		if (timeGetTime() >= m_lNextFrameTime)
		{
			m_lNextFrameTime = timeGetTime() + nFrameDelay;
			long m = m_cxImage->GetNumFrames();//获取总帧数
			if (n >= m)
			{
				n = 0; //如果下一帧索引超出索引范围，则下一帧为第0帧
				m_PlayGif = FALSE;
				m_cxImage->Copy(*m_cxImage->GetFrame(0));
			}
			if (m_cxImage->GetFrame(n)&&m_PlayGif)
			{
				m_cxImage->Copy(*m_cxImage->GetFrame(n));//设置图像为下一帧
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
	textword.lfont.lfWeight = fontWeight;    //字体重量，粗细
	textword.lfont.lfItalic = 0;   
	textword.lfont.lfUnderline = 0;  //是否加下划线
	textword.fcolor = fontColor;   //字体颜色
	textword.bcolor = RGB(0, 80, 160);  
	textword.opaque = 0; //背景透明不透明
	textword.b_opacity = (float)(0) / (float)100.; //透明度
	textword.b_round = (BYTE)10; //四舍五入为背景矩形半径
	textword.smooth = (BYTE)1; //平滑选项的文本
	LPTSTR tmpword = (LPTSTR)(LPCTSTR)word;
	_stprintf(textword.text, tmpword);
	tmpimg.DrawStringEx(hDC, xFont, yFont, &textword);
	tmpimg.Draw(hDC, x, y, nWidth, nHeight);
}


//设置用于drawcximagedialog方法的参数
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


//设置用于drawcximage方法的参数
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

//用指定位图文件创建DrawSprite实例
DrawSprite::DrawSprite(HINSTANCE hInstance, LPTSTR szFileNmae)
{
	//载入指定的位图文件
	Load(hInstance, szFileNmae);
	m_ID = m_nNewID;
	m_nNewID++;
	m_nZOrder = 0;
}
//用指定位图资源创建DrawSprite实例
DrawSprite::DrawSprite(HINSTANCE hInstance, UINT uRcID)
{
	//载入指定的位图文件
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
//析构函数
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

	//通过在位图中绘制填充矩形来设置位图
	HDC hdcMem = CreateCompatibleDC(hDC);//创建兼容设备
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

//在hDC的指定位置(x,y)输出透明度为nAlpha(0~255)的半透明图像
void DrawSprite::DrawAlpha(HDC hDC, int x, int y, int nAlpha)
{
	HDC hdcMem = CreateCompatibleDC(hDC);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, m_hbm);
	//设置bf结构
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = nAlpha;
	bf.AlphaFormat = 0x00;

	//输出半透明图像
	AlphaBlend(hDC, x, y, m_nWidth, m_nHeight, hdcMem, 0, 0, GetWidth(), GetHeight(), bf);

	SelectObject(hdcMem, hOldBmp);
	DeleteDC(hdcMem);
}

//绘制半透明镂空位图
void DrawSprite::DrawTransAlpha(HDC hdcBack, int nXBack, int nYBack, int nWidthBack, int nHeightBack, int nXFore, int nYFore, int nAlpha /* = 100 */,
	COLORREF crTrans /* = RGB(0, 0, 0) */)
{
	if (m_hbm!=NULL)
	{
		HDC hdcMem = CreateCompatibleDC(hdcBack);

		//创建一个与背景同样大小的临时图像
		RECT rBackRect = { nXBack,nYBack,nWidthBack,nHeightBack };
		HBITMAP hbmTmp = CreateCompatibleBitmap(hdcBack, nWidthBack, nHeightBack);
		HBITMAP hbmBK = (HBITMAP)SelectObject(hdcBack, hbmTmp);//替出背景图像
		RECT rForeRect = { nXFore,nYFore,nXFore + m_nWidth,nYFore + m_nHeight };
		RECT rTransRect, rTransRect2;
//获取前景矩形与背景矩形的交集，如不相交，不需要进行颜色计算
		if (IntersectRect(&rTransRect,&rBackRect,&rForeRect))
		{
			BITMAP bm, bmBk;
			GetObject(m_hbm, sizeof(BITMAP), &bm);
			BYTE *px = new unsigned char[bm.bmHeight*bm.bmWidthBytes];//声明数组
			//取得源位图各像素点的RGB值并存放入px数组中
			GetBitmapBits(m_hbm, bm.bmHeight*bm.bmWidthBytes, px);
			GetObject(hbmBK, sizeof(BITMAP),&bmBk);

			BYTE *pxBk = new unsigned char[bmBk.bmHeight*bmBk.bmWidthBytes];
			//取得背景位图各像素点的RGB值并存入px数组中
			GetBitmapBits(hbmBK, bmBk.bmHeight*bmBk.bmWidthBytes, pxBk);

			rTransRect2 = rTransRect;
			OffsetRect(&rTransRect2, -rForeRect.left, -rForeRect.top); //偏移矩形坐标
			
			int pb = bm.bmBitsPixel / 8;//获取每像素所占字节数
			int pbBk = bmBk.bmBitsPixel / 8;

			//dy1为背景图像素行数，dy2为前景图像素行数
			int dx1, dx2, dy1, dy2;
			//循环对像素进行计算，背景和前景中需要进行计算的像素分别在各自对应的矩形rT和rT2的范围内循环

			for (dy1=rTransRect.top,dy2=rTransRect2.top;dy1<rTransRect.bottom;dy1++,dy2++)
			{
				for (dx1 = rTransRect.left, dx2 = rTransRect2.left;dx1 < rTransRect.right; dx1++, dx2++)
				{
					//计算背景图像素起始位置
					int nBackRGB_B = dy1*bmBk.bmWidthBytes + dx1*pbBk;
					int nForeRGB_B = dy2*bm.bmWidthBytes + dx2*pb;
					if (RGB(px[nForeRGB_B+2],px[nForeRGB_B+1],px[nForeRGB_B])!=crTrans)
					{
						//将pxBk的B色彩值乘以nAlpha 并于px相加
						pxBk[nBackRGB_B] = (px[nForeRGB_B] * nAlpha + pxBk[nBackRGB_B] * (255 - nAlpha)) / 255;
						//将pxBk的G色彩值乘以nAlpha并于px相加
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

//绘制灰度镂空图
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
		//循环计算灰度值
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
			//输出透明位图
			TransparentBlt(hDC, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, crTransparent);
		}
		else
			//输出不透明位图
			BitBlt(hDC, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hOldBmp);
		DeleteObject(hbmTmp);
		DeleteDC(hdcMem);
	}
}

//绘制透明镂空位图
void DrawSprite::TransBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXSrc, int nYSrc, int nWidthSrc,
	int nHeightSrc, COLORREF crTrans /* = RGB(255,255,255) */)
{
	//创建兼容位图
	HBITMAP hbmTmp = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);
	//创建单色位图
	HBITMAP hbmMask = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);

	HDC hdcMem = CreateCompatibleDC(hdcDest);
	HDC hdcMask = CreateCompatibleDC(hdcDest);

	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmTmp);
	HBITMAP hbmMaskOld = (HBITMAP)SelectObject(hdcMask, hbmMask);

	//将源dc中的位图复制到临时设备环境中
	if (nWidthDest==nWidthSrc&&nHeightDest==nHeightSrc)
	{
		BitBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXSrc, nYSrc, SRCCOPY);
	}
	else
	{
		StretchBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXSrc, nYSrc, nWidthSrc, nHeightSrc, SRCCOPY);
	}
	//设置透明色
	SetBkColor(hdcMem, crTrans);
	//生成透明区域为白色，其他区域为黑色的蒙板位图
	BitBlt(hdcMask, 0, 0, nWidthDest, nHeightDest, hdcMem, 0, 0, SRCCOPY);
	//生成透明区域为黑色，其他区域保持不变的位图
	SetBkColor(hdcMem, RGB(0, 0, 0));
	SetTextColor(hdcMem, RGB(255, 255, 255));
	BitBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcMask, 0, 0, SRCAND);
	//透明部分对应的背景保持不变,其他部分变成黑色
	SetBkColor(hdcDest, RGB(255, 255, 255));
	SetTextColor(hdcDest, RGB(0, 0, 0));
	BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMask, 0, 0, SRCAND);
	//或运算，生成最终效果
	BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMem, 0, 0, SRCPAINT);

	//clean
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
	SelectObject(hdcMask, hbmMaskOld);
	DeleteDC(hdcMask);
	DeleteObject(hbmTmp);
	DeleteObject(hbmMask);
}


//使用nRowCount,列nColCount总数和帧显示延时nFrameDelay来初始化动画参数
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

//绘制动画方法，在(x,y)坐标处绘制一个动画帧画面，帧画面中的计时会在循环绘制时自动更新
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

//在hDC指定位置绘制图像的nRow行nCol列的帧画面，如果是镂空图，设置crTransparent为透明色
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
		//输出透明位图
		TransparentBlt(hDC, x, y, m_nFrameWidth, m_nFrameHeight, hdcMem, m_nFrameWidth*nCol, m_nFrameHeight*nRow, m_nFrameWidth, m_nFrameHeight,crTrans);
	}
	else
		//输出不透明位图
		BitBlt(hDC,x,y, m_nFrameWidth, m_nFrameHeight, hdcMem, m_nFrameWidth*nCol, m_nFrameHeight*nRow, SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmOld);
	DeleteDC(hdcMem);
}

//精灵管理类所需方法
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

//设置用于DrawAnima方法的
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

//统一的绘图接口
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

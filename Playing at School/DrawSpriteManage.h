#pragma once
#include "DrawSprite.h"
#include <vector>
using namespace std;
class DrawSpriteManage
{
private:
	vector <DrawSprite*> m_vSprites;//vector对象，用来存储精灵指针
public:
	DrawSpriteManage();
	virtual ~DrawSpriteManage();
	BOOL AddSprite(DrawSprite *pSprite, int nZorder = 0);
	void Release(BOOL bDelSprite = FALSE);
	void DelSprite(DrawSprite *pSprite, BOOL bDelSprite = FALSE, BOOL bCompress = FALSE);
	void SetSpriteVisible(DrawSprite *pSprite, BOOL bVisible);
	BOOL FindSprite(DrawSprite *pSprite);
	void Draw(HDC hDC);
	void SetZOrder(DrawSprite *pSprite, int nZorder);
};


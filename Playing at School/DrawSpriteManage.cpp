#include "DrawSpriteManage.h"



DrawSpriteManage::DrawSpriteManage()
{
}


DrawSpriteManage::~DrawSpriteManage()
{
	Release(TRUE);
}

BOOL DrawSpriteManage::AddSprite(DrawSprite *pSprite, int nZorder /* = 0 */)
{
	if (pSprite!=NULL)
	{
		pSprite->SetZOrder(nZorder);
		if (!m_vSprites.empty())
		{
			vector<DrawSprite*>::iterator siSprite;
			for (siSprite=m_vSprites.begin();siSprite!=m_vSprites.end();siSprite++)
			{
				if (nZorder<(*siSprite)->GetZOrder())
				{
					m_vSprites.insert(siSprite, pSprite);
					return TRUE;
				}
			}
		}
		//如果精灵管理对象为空或nZOreder为最大的序号，则将精灵添加到精灵管理对象尾部
		m_vSprites.push_back(pSprite);
		return TRUE;
	}
	return FALSE;
}

//
void DrawSpriteManage::Release(BOOL bDelSprite /* = FALSE */)
{
	if (!m_vSprites.empty())
	{
		if (bDelSprite)
		{
			vector<DrawSprite*>::iterator siSprite;
			for (siSprite =m_vSprites.begin();siSprite!=m_vSprites.end();siSprite++)
			{
				delete *siSprite;
			}
		}
		m_vSprites.clear(); //删除容器中精灵对象指针
		vector<DrawSprite*>(m_vSprites).swap(m_vSprites);
	}
}
 
void DrawSpriteManage::DelSprite(DrawSprite *pSprite, BOOL bDelSprite /* = FALSE */, BOOL bCompress /* = FALSE */)
{
	vector<DrawSprite*>::iterator siSprite;
	for (siSprite=m_vSprites.begin();siSprite!=m_vSprites.end();siSprite++)
	{
		if ((*siSprite)->GetID()==pSprite->GetID()) 
		{
			if (bDelSprite)
			{
				delete pSprite;
			}
			m_vSprites.erase(siSprite);
			break;
		}
		if (bCompress)
		{
			vector<DrawSprite*>(m_vSprites).swap(m_vSprites);
		}
	}
}

BOOL DrawSpriteManage::FindSprite(DrawSprite *pSprite)
{
	if (!m_vSprites.empty())
	{
		vector<DrawSprite*>::iterator siSprite;
		for (siSprite=m_vSprites.begin();siSprite!=m_vSprites.end();siSprite++)
		{
			if ((*siSprite)->GetID()==pSprite->GetID())
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

void DrawSpriteManage::SetSpriteVisible(DrawSprite *pSprite, BOOL bVisible)
{
	pSprite->SetVisible(bVisible);
}


void DrawSpriteManage::Draw(HDC hDC)
{
	if (!m_vSprites.empty())
	{
		vector<DrawSprite*>::iterator siSprite;
		for (siSprite = m_vSprites.begin();siSprite!=m_vSprites.end();siSprite++)
		{
			(*siSprite)->CDrawSprite(hDC);  //循环调用精灵对象绘图函数
		}
	}
}

void DrawSpriteManage::SetZOrder(DrawSprite *pSprite, int nZorder)
{
	DelSprite(pSprite);
	AddSprite(pSprite, nZorder);
}

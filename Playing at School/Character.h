#pragma once
#include <windows.h>
#include <time.h>
typedef int Classes;
const Classes CL_NULL = 0,
CL_WARRIOR = 1,
CL_MAGE = 2,
CL_PRIEST = 3,
CL_MONK = 4,
SA_FIRE = 2,
SA_STUN = 1,
SA_DEFEND = 0;
class Character
{
protected:
	static int m_nNewID;
	int m_nID;
	LPTSTR m_chName;
	int m_nGender;
	int m_nHealthPointMAX;
	int m_nManaPointMAX;
	int m_nHealthPointCur;
	int m_nManaPointCur;
	int m_nExperiencePoint;
	int m_nStrength;
	int m_nDexterity;
	int m_nConstitution;
	int m_nIntelligence;
	int m_nWisdom;
	int m_nCharisma;
	int m_nCarrweight;
	int m_nRace;
	int m_nLevel;
	int m_nAttributes;
	int m_nAttackPoint;
	int m_nDefendPoint;
	int m_nActionNum;
	int m_nStatus;
	Classes m_cl;
public:
	Character(LPTSTR szName, int nRace, int nClass, int nGender, int nStrength, int nDexterity, 
		int nConstitution, int nIntelligence, int nWisdom, int nCharisma,int nlevel=1, int nAttributes=0,int nEXP = 0);
	int GetID();
	void Name(LPTSTR szName);
	LPTSTR GetName();
	void Gender(int nGender);
	int GetGender();
	void MaxHP(int nMaxHP);
	int GetMaxHP();
	void MaxMP(int nMaxHP);
	int GetMaxMP();
	void HP(int nHP);
	int GetHP();
	void MP(int nMP);
	int GetMP();
	void ExperiencePoint(int EXP);
	int GetExperiencePoint();
	void Strength(int nStr);
	int GetStrength();
	void Dexterity(int nDex);
	int GetDexterity();
	void Constitution(int nCon);
	int GetConstitution();
	void Intelligence(int Int);
	int GetIntelligence();
	void Wisdom(int Wis);
	int GetWisdom();
	void Charisma(int Cha);
	int GetCharisma();
	void CarryWeight(int Weight);
	int GetCarryWeight();
	void SetClass(int nClass);
	int GetClass();
	void Race(int nRace);
	int GetRace();
	void Level(int level);
	int GetLevel();
	void SetAttributes(int attributes);
	int GetAttributes();
	int GetAttack();
	void SetAttack(int attack);
	void SetStatus(int status);
	int GetStatus();
	
	int GetActionNum();
	void SetActionNum(int actionnum);

	int GetDefend()
	{
		return m_nDefendPoint;
	}
	void SetDefend(int defend)
	{
		m_nDefendPoint = defend;
	}
	int static RandomDx_y(int x, int y)
	{
		int m = (rand() % (y - x + 1)) + x;
		return m;
	}

	virtual~Character();
};


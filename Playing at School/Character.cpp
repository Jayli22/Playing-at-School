#include "Character.h"
int Character::m_nNewID = 1; //初始化绘制角色编号

int Character::GetID()
{
	return m_nID;
}
void Character::Name(LPTSTR szName)
{
	m_chName = szName;
}
LPTSTR Character::GetName()
{
	return m_chName;
}

void Character::Gender(int gender)
{
	m_nGender = gender;
}
int Character::GetGender()
{
	return m_nGender;
}	
void Character::MaxHP(int nHPMAX)
{
	m_nHealthPointMAX = nHPMAX;
}
int Character::GetMaxHP()
{
	return m_nHealthPointMAX;
}
void Character::MaxMP(int nMPMAX)
{
	m_nManaPointMAX = nMPMAX;
}
int Character::GetMaxMP()
{
	return m_nManaPointMAX;
}
void Character::HP(int hp)
{
	m_nHealthPointCur = hp;
}
int Character::GetHP()
{
	return m_nHealthPointCur;
}
void Character::MP(int mp)
{
	m_nManaPointCur = mp;
}
int Character::GetMP()
{
	return m_nManaPointCur;
}
void Character::ExperiencePoint(int exp)
{
	m_nExperiencePoint = exp;
}
int Character::GetExperiencePoint()
{
	return m_nExperiencePoint;
}
void Character::Strength(int str)
{
	m_nStrength = str;
}
int Character::GetStrength()
{
	return m_nStrength;
}
void Character::Dexterity(int dex)
{
	m_nDexterity = dex;
}
int Character::GetDexterity()
{
	return m_nDexterity;
}
void Character::Constitution(int con)
{
	m_nConstitution = con;
}
int Character::GetConstitution()
{
	return m_nConstitution;
}
void Character::Intelligence(int nInt) {
	m_nIntelligence = nInt;
}
int Character::GetIntelligence()
{
	return m_nIntelligence;
}
void Character::Wisdom(int wis)
{
	m_nWisdom = wis;
}
int Character::GetWisdom()
{
	return m_nWisdom;
}
void Character::Charisma(int cha)
{
	m_nCharisma = cha;
}
int Character::GetCharisma()
{
	return m_nCharisma;
}
void Character::CarryWeight(int carryweight)
{
	m_nCarrweight = carryweight;
}
int Character::GetCarryWeight()
{
	return m_nCarrweight;
}
void Character::SetClass(int classes)
{
	m_cl = classes;
}
int Character::GetClass()
{
	return m_cl;
}
void Character::Race(int race)
{
	m_nRace = race;
}
int Character::GetRace()
{
	return m_nRace;
}
void Character::Level(int level)
{
	m_nLevel = level;
}
int Character::GetLevel()
{
	return m_nLevel;
}
void Character::SetAttributes(int att)
{
	m_nAttributes = att;
}
int Character::GetAttributes()
{
	return m_nAttributes;
}
int Character::GetAttack()
{
	return m_nAttackPoint;
}
void Character::SetAttack(int attack)
{
	m_nAttackPoint = attack;
}
void Character::SetActionNum(int actionnum)
{
	m_nActionNum = RandomDx_y(1, 20) + (m_nDexterity - 10) / 2;
}
int Character::GetActionNum()
{
	return m_nActionNum;
}
void Character::SetStatus(int status)
{
	m_nStatus = status;
}
int Character::GetStatus() {
	return m_nStatus;
}
Character::Character(LPTSTR szname, int race, int nClass, int gender, int str, int dex, int con,
	int nInt, int wis, int cha,int nlevel /*=1*/,int nAttributes,int nExp)
{
	m_nID = m_nNewID;
	m_nNewID++;

	m_chName = szname;
	m_nRace = race;
	m_cl = nClass;
	m_nGender = gender;
	m_nStrength = str;
	m_nDexterity = dex;
	m_nConstitution = con;
	m_nIntelligence = nInt;
	m_nWisdom = wis;
	m_nCharisma = cha;
	m_nHealthPointMAX = (m_nConstitution - 1 ) * 3 + RandomDx_y(5,20);
	m_nManaPointMAX = (m_nIntelligence - 10) / 2 + 10;
	m_nHealthPointCur = m_nHealthPointMAX;
	m_nManaPointCur = m_nManaPointMAX;
	m_nActionNum = RandomDx_y(1, 20) + (m_nDexterity - 10) / 2;
	if (m_nRace==1)
	{
		m_nAttackPoint = (m_nStrength - 10) / 2;
	}
	if (m_nRace==2)
	{
		m_nAttackPoint = (m_nCharisma - 8) / 2;
	}
	if (m_nRace==3)
	{
		m_nAttackPoint = (m_nIntelligence - 5) / 2;
	}
	
	m_nDefendPoint = 5 + (m_nDexterity - 10) / 2;
	m_nLevel = nlevel;

	m_nAttributes = nAttributes;

	m_nExperiencePoint = nExp;

}


Character::~Character()
{
}

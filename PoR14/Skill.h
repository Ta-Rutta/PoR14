#pragma once
#include "SkillID.h"
#include "CoolTime.h"
#include "SkillValue.h"

class Skill
{
private:
	SkillType type; //攻撃・補助の区別
	SkillType preSkillID;  // コンボの起点となるスキルID [追加]
	SkillValue value;
	CoolTime coolTime;

public:
	

	Skill()
		: type(SkillType::None), preSkillID(SkillType::None),
		 value(0,0), coolTime(CoolTimeID::GCD,0.0)
	{

	}

	Skill(SkillType type, SkillType preSkillID, SkillValue value, CoolTime coolTime)
		:type(type),preSkillID(preSkillID),value(value),coolTime(coolTime)
	{

	}

	bool comboCheck(SkillType type)
	{
		if (type == preSkillID && preSkillID != SkillType::None)return true;
		else return false;
	}

	bool isReady() { return coolTime.isReady(); }

	void coolTimeSet() { coolTime.coolTimeSet(); }

	void coolTimeCount(){coolTime.coolTimeCount();}

	int returnSkillValue() { return value.returnSkillValue(); }

	int returnComboValue() { return value.returnComboValue(); }
};

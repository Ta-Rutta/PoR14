#pragma once
#include "Buff.h"
#include "SkillType.cpp"



class Skill
{
public:
	String name; //スキル名
	SkillType type; //攻撃・補助の区別
	String preSkillID;  // コンボの起点となるスキルID [追加]
	String coolTimeID; //クールタイム分け
	int value; //攻撃力
	int comboValue;     // コンボ成立時の威力 [追加]
	double cooltime; //クールタイム
	double timer = 0; //経過時間	

	bool isReady() const { return timer <= 0.0; }

	int getEffectivePower(const String& activeComboID, double comboTimer) const
	{
		// 派生なし（"null"）なら常に基本威力
		if (preSkillID == U"null")
		{
			return value;
		}

		// 派生ありの場合、条件（ID一致かつ受付時間内）を満たせばコンボ威力を返す
		if (preSkillID == activeComboID && comboTimer > 0)
		{
			return comboValue;
		}

		// 条件を満たさない（素振り）なら基本威力
		return value;
	}

};

class AttackSkill : public Skill
{
public:	

	bool isReady() const { return timer <= 0.0; }

	int getEffectivePower(const String& activeComboID, double comboTimer) const
	{
		// 派生なし（"null"）なら常に基本威力
		if (preSkillID == U"null")
		{
			return value;
		}

		// 派生ありの場合、条件（ID一致かつ受付時間内）を満たせばコンボ威力を返す
		if (preSkillID == activeComboID && comboTimer > 0)
		{
			return comboValue;
		}

		// 条件を満たさない（素振り）なら基本威力
		return value;
	}
};




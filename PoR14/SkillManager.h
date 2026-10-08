#pragma once
#include "Buff.h"
#include "Skill.h"
#include "DamageChecker.h"

struct SkillResult
{
	int damage = 0;
	bool result = false;
};


class SkillManager
{
private:
	const double GCD_TIME = 1.8;
	String activeComboID = U"";    // 現在有効なコンボ起点スキルID
	double comboTimer = 0.0;       // コンボ受付の残り時間
	const double COMBO_LIMIT = 15.0; // コンボ受付時間

public:
	
	Array<int> comboStep;
	Array<Array<Skill>> skillChain;
	Array<Array<Skill>>* skill = &skillChain;
	HashTable<SkillType, Skill> skills;
	BuffManager* manager;
	SkillType preSkill = SkillType::None;
	DamageChecker damageChecker;

	SkillManager()
	{
		init();
	}

	void init() {		
		skills[SkillType::Attack] = Skill{
			 SkillType::Attack, SkillType::None, SkillValue(10,20), CoolTime(CoolTimeID::GCD,GCD_TIME)
		};
		skills[SkillType::Attack2] = Skill{
			 SkillType::Attack2, SkillType::Attack, SkillValue(20,60), CoolTime(CoolTimeID::GCD,GCD_TIME)
		};

		comboStep.assign(skillChain.size(), 0);
	}

	SkillResult returnSkillResult(SkillType type)
	{
		SkillResult skillResult;
		if (skills[type].isReady())
		{
			skillResult.result = true;
			skills[type].coolTimeSet();
		}
		else
		{
			return skillResult;
		}
		
		if (skillResult.result && skills[type].comboCheck(preSkill))
		{
			skillResult.damage = damageChecker.returnDamage(skills[type].returnComboValue());
		}
		else
		{
			skillResult.damage = damageChecker.returnDamage(skills[type].returnSkillValue());
		}

		preSkill = type;
		return skillResult;
	}


	void update()
	{
		for (auto& [type, s] : skills)
		{
			s.coolTimeCount();
		}
	}

};


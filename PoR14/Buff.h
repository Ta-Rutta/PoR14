#pragma once

enum class BuffType
{
	Attack,//ダメージ増加
	GCD,//スキルクールタイム短縮
	Heal,//回復
	Regist,//ダメージ軽減
	Active//実行可能
};

struct Buff
{
	BuffType type;//バフのタイプ(攻撃バフ、実行可能バフなど)
	String name;//バフの名前
	double duration;//効果時間
	double value;//バフの効果値
	bool active = false;	
	
	Buff(BuffType t,String name , float dur, float val)
		: type(t),name(name), duration(dur), value(val)
	{

	}
};

class BuffManager
{
private:
	Array<Buff> buffs;
public:
	const Font font{ FontMethod::MSDF,30 };
	Buff attackBuff{ BuffType::Attack,U"AttackBuff",10,1.1 };
	Buff GCDBuff{ BuffType::GCD,U"GCDBuff",10,1.3 };
	Buff HealBuff{ BuffType::Heal,U"Healing",10,20 };
	Buff RegistBuff{ BuffType::Regist,U"RegistDamage",10,1.2 };
	Buff ActiveBuff{ BuffType::Active,U"RegistDamage",10,1.2 };

	HashTable<BuffType, Buff> myBuff{
		{BuffType::Attack,attackBuff},
		{BuffType::GCD,GCDBuff},
		{BuffType::Heal,HealBuff},
		{BuffType::Regist,RegistBuff},
		{BuffType::Active,ActiveBuff}
	};
	

	

	void update()
	{
		
	}

	
};
